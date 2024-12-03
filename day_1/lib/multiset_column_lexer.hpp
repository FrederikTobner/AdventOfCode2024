/**
 * @file multiset_column_lexer.hpp
 * @brief Implementation of a lexer that parses the input data into columnar multiset structures
 * @details Provides interfaces for parsing input data containing pairs of numbers.
 * Includes utilities for parsing individual lines and complete input files,
 * with error handling through std::expected.
 */

#pragma once

#include <algorithm>
#include <atomic>
#include <cstdint>
#include <execution>
#include <expected>
#include <functional>
#include <mutex>
#include <ranges>
#include <set>
#include <string>
#include <string_view>
#include <system_error>
#include <thread>
#include <tuple>
#include <utility>
#include <vector>

#include "../../shared/concurrent_context.hpp"
#include "../../shared/ranges_compatibility_layer.hpp"

/// @brief Namespace containing lexer functionality for parsing and tokenizing input
namespace aoc::lexer {

/// @brief Processing mode for input parsing - mainly used for performance testing optimizations made using parallelism
enum class ProcessingMode {
    Sequential,
    Parallel
};

/// @brief User-defined literal for creating string views of whitespace characters
/// @param str The string to convert to a string view
/// @param len The length of the string
/// @return A string view of the input string
[[nodiscard]] constexpr auto operator""_ws(char const * str, size_t len) noexcept {
    return std::string_view{str, len};
}

/// @brief String view of whitespace characters for use in parsing
inline constexpr auto WHITESPACE_CHARS = " \t\n\r"_ws;

/**
 * @brief Parses a single line containing N space-separated numbers
 * @tparam TOKEN The numeric type to parse into
 * @tparam COLUMN_AMOUNT Number of columns to parse
 * @param line String view containing the line to parse
 * @return array containing COLUMN_AMOUNT parsed numbers
 */
template <typename TOKEN, size_t COLUMN_AMOUNT>
[[nodiscard]] auto tokenizeLine(std::string_view line,
                                std::function<std::expected<TOKEN, std::error_code>(std::string_view)> tokenProducer)
    -> std::expected<std::array<TOKEN, COLUMN_AMOUNT>, std::error_code>;

/**
 * @brief Checks if a string view contains only whitespace characters
 * @param str String view to check
 * @return true if string contains only whitespace or is empty, false otherwise
 */
[[nodiscard]] constexpr auto isOnlyWhitespace(std::string_view str) -> bool {
    return str.empty() || str.find_first_not_of(WHITESPACE_CHARS) == std::string_view::npos;
}

/**
 * @brief Parses the entire input string into a tuple of two ordered multisets of numbers
 * @tparam TOKEN The numeric type to store in the multisets
 * @tparam COLUMN_AMOUNT Number of columns to parse (must be 2)
 * @param input String view containing the entire input
 * @param mode Processing mode to use for parsing
 * @return tuple of two multisets containing the parsed numbers
 */
template <typename TOKEN, size_t COLUMN_AMOUNT>
[[nodiscard]] auto tokenize(std::string_view input,
                            std::function<std::expected<TOKEN, std::error_code>(std::string_view)> tokenProducer,
                            ProcessingMode mode = ProcessingMode::Parallel)
    -> std::expected<std::array<std::multiset<TOKEN>, COLUMN_AMOUNT>, std::error_code>;

/**
 * @brief Normalizes tab characters by replacing them with two spaces
 * @param str String view to process
 * @return String with tabs replaced by two spaces
 */
[[nodiscard]] auto normalizeTabs(std::string_view str) -> std::string;

static bool isWhitespace(char c) {
    return c == ' ' || c == '\t';
}

template <typename TOKEN, size_t COLUMN_AMOUNT>
static void processLineIntoSets(std::string_view const & line,
                                std::vector<std::array<std::multiset<TOKEN>, COLUMN_AMOUNT>> & sets, size_t thread_id,
                                threads::concurrent_context<std::error_code> & context,
                                std::function<std::expected<TOKEN, std::error_code>(std::string_view)> tokenProducer) {
    if (context.hasValue()) {
        return;
    }

    auto result = tokenizeLine<TOKEN, COLUMN_AMOUNT>(line, tokenProducer);
    if (!result) {
        context.setValue(result.error());
        return;
    }

    for (size_t i = 0; i < COLUMN_AMOUNT; ++i) {
        sets[thread_id][i].insert((*result)[i]);
    }
}

template <typename TOKEN, size_t COLUMN_AMOUNT>
static auto mergeSets(std::vector<std::array<std::multiset<TOKEN>, COLUMN_AMOUNT>> const & thread_local_sets)
    -> std::array<std::multiset<TOKEN>, COLUMN_AMOUNT> {
    std::array<std::multiset<TOKEN>, COLUMN_AMOUNT> result;

    for (auto const & local_sets : thread_local_sets) {
        for (size_t i = 0; i < COLUMN_AMOUNT; ++i) {
            result[i].insert(local_sets[i].begin(), local_sets[i].end());
        }
    }
    return result;
}

template <typename TOKEN, size_t COLUMN_AMOUNT>
auto tokenizeLine(std::string_view line,
                  std::function<std::expected<TOKEN, std::error_code>(std::string_view)> tokenProducer)
    -> std::expected<std::array<TOKEN, COLUMN_AMOUNT>, std::error_code> {
    using enum std::errc;

    std::string normalized = normalizeTabs(line);
    std::vector<std::expected<TOKEN, std::error_code>> tokens =
        std::string_view{normalized} | std::views::split(' ') |
        std::views::transform([](auto && range) { return std::string_view(range.begin(), range.end()); }) |
        std::views::filter([](auto && sv) { return !isOnlyWhitespace(sv); }) | std::views::transform(tokenProducer) |
        nonstd::ranges::to<std::vector<std::expected<TOKEN, std::error_code>>>;

    if (tokens.size() != COLUMN_AMOUNT) {
        return std::unexpected(std::make_error_code(invalid_argument));
    }

    std::array<TOKEN, COLUMN_AMOUNT> result;
    for (size_t i = 0; i < COLUMN_AMOUNT; ++i) {
        if (!tokens[i]) {
            return std::unexpected(tokens[i].error());
        }
        result[i] = *tokens[i];
    }

    return result;
}

template <typename TOKEN, size_t COLUMN_AMOUNT>
auto tokenize(std::string_view input,
              std::function<std::expected<TOKEN, std::error_code>(std::string_view)> tokenProducer, ProcessingMode mode)
    -> std::expected<std::array<std::multiset<TOKEN>, COLUMN_AMOUNT>, std::error_code> {
    auto lines = input | std::views::split('\n') |
                 std::views::transform([](auto && chars) { return std::string_view(chars.begin(), chars.end()); }) |
                 std::views::filter([](auto sv) { return !isOnlyWhitespace(sv); }) |
                 nonstd::ranges::to<std::vector<std::string_view>>;

    threads::concurrent_context<std::error_code> context;
    std::vector<std::array<std::multiset<TOKEN>, COLUMN_AMOUNT>> thread_local_sets(
        mode == ProcessingMode::Parallel ? std::thread::hardware_concurrency() : 1);

    if (mode == ProcessingMode::Parallel) {
        // Execute with a parallel unsequenced policy to allow for parallel processing of the lines
        std::for_each(std::execution::par_unseq, lines.begin(), lines.end(), [&](std::string_view const & line) {
            unsigned long long thread_id =
                std::hash<std::thread::id>{}(std::this_thread::get_id()) % thread_local_sets.size();
            processLineIntoSets<TOKEN, COLUMN_AMOUNT>(line, thread_local_sets, thread_id, context, tokenProducer);
        });
    } else {
        for (auto const & line : lines) {
            processLineIntoSets<TOKEN, COLUMN_AMOUNT>(line, thread_local_sets, 0, context, tokenProducer);
        }
    }

    if (context.hasValue()) {
        return std::unexpected(context.getValue());
    }

    return mergeSets<TOKEN, COLUMN_AMOUNT>(thread_local_sets);
}

auto normalizeTabs(std::string_view str) -> std::string {
    return str | std::views::transform([](char c) { return c == '\t' ? ' ' : c; }) | nonstd::ranges::to<std::string>;
}

} // namespace aoc::lexer