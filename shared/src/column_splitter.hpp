/**
 * @file column_splitter.hpp
 * @brief Implementation of a lexer that parses the input data into columnar container structures
 * @details Provides interfaces for parsing input data containing columns of numbers.
 * Includes utilities for parsing individual lines and complete input files,
 * with error handling through std::expected and configurable container types.
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

#include "concurrent_context.hpp"
#include "container_traits.hpp"
#include "execution_policy_traits.hpp"
#include "ranges_compatibility_layer.hpp"
#include "splitter.hpp"

/// @brief Namespace containing splitter functionality for splitting input into columns
namespace aoc::splitter::columnbased {

/**
 * @brief Parses the entire input string into columns of numbers using specified container type
 * @tparam TOKEN The numeric type to store in the containers
 * @tparam COLUMN_AMOUNT Number of columns to parse
 * @tparam CONTAINER Container type to store the values (defaults to std::vector)
 * @tparam EXECUTION_POLICY The execution policy to use for parallel processing
 * @param input String view containing the entire input
 * @param tokenProducer Function to convert string tokens into the desired type
 * @param policy Execution policy to use
 * @param delimiter Character to split tokens on
 * @return Array of containers containing the parsed numbers
 */
template <typename TOKEN, size_t COLUMN_AMOUNT, template <typename...> typename CONTAINER = std::vector,
          typename EXECUTION_POLICY>
    requires std::is_execution_policy_v<std::remove_cvref_t<EXECUTION_POLICY>>
[[nodiscard]] auto split(std::string_view input,
                         std::function<std::expected<TOKEN, std::error_code>(std::string_view)> tokenProducer,
                         EXECUTION_POLICY && policy, char delimiter = ' ')
    -> std::expected<std::array<CONTAINER<TOKEN>, COLUMN_AMOUNT>, std::error_code>;

/// @brief Parses the entire input string into columns of numbers using specified container type
/// @tparam TOKEN The numeric type to store in the containers
/// @tparam COLUMN_AMOUNT Number of columns to parse
/// @tparam CONTAINER Container type to store the values (defaults to std::multiset)
/// @param input String view containing the entire input
/// @param tokenProducer Function to convert string tokens into the desired type
/// @param delimiter Character to split tokens on
/// @return Array of containers containing the parsed numbers
template <typename TOKEN, size_t COLUMN_AMOUNT, template <typename...> typename CONTAINER = std::multiset>
auto split(std::string_view input, std::function<std::expected<TOKEN, std::error_code>(std::string_view)> tokenProducer,
           char delimiter = ' ') -> std::expected<std::array<CONTAINER<TOKEN>, COLUMN_AMOUNT>, std::error_code>;

/**
 * @brief Parses a single line containing N space-separated numbers
 * @tparam TOKEN The numeric type to parse into
 * @tparam COLUMN_AMOUNT Number of columns to parse
 * @param line String view containing the line to parse
 * @return array containing COLUMN_AMOUNT parsed numbers
 */
template <typename TOKEN, size_t COLUMN_AMOUNT>
[[nodiscard]] static auto
tokenizeLine(std::string_view line,
             std::function<std::expected<TOKEN, std::error_code>(std::string_view)> tokenProducer, char delimiter)
    -> std::expected<std::array<TOKEN, COLUMN_AMOUNT>, std::error_code>;

/// @brief Merges thread-local token sets into a single result array
/// @tparam TOKEN The type of tokens to merge
/// @tparam COLUMN_AMOUNT Number of columns to merge
/// @param thread_local_sets Vector of thread-local token sets to merge
/// @return Combined array of all token sets
template <typename TOKEN, size_t COLUMN_AMOUNT, template <typename...> typename CONTAINER>
static auto mergeSets(std::vector<std::array<CONTAINER<TOKEN>, COLUMN_AMOUNT>> const & thread_local_sets)
    -> std::array<CONTAINER<TOKEN>, COLUMN_AMOUNT>;

/// @brief Processes a single line of input into tokens for a specific thread
/// @tparam TOKEN The type to store in the multisets
/// @tparam COLUMN_AMOUNT Number of columns to parse
/// @param line String view containing the line to parse
/// @param sets Vector of thread-local token sets to merge
/// @param thread_id ID of the current thread
/// @param context Concurrent context for error handling
/// @param tokenProducer Function to convert string tokens into the desired type
/// @param delimite Character to split tokens on
template <typename TOKEN, size_t COLUMN_AMOUNT, template <typename...> typename CONTAINER = std::multiset>
static void processLineIntoSets(std::string_view const & line,
                                std::vector<std::array<CONTAINER<TOKEN>, COLUMN_AMOUNT>> & sets, size_t thread_id,
                                threads::concurrent_context<std::error_code> & context,
                                std::function<std::expected<TOKEN, std::error_code>(std::string_view)> tokenProducer,
                                char delimiter);

template <typename TOKEN, size_t COLUMN_AMOUNT, template <typename...> typename CONTAINER, typename EXECUTION_POLICY>
    requires std::is_execution_policy_v<std::remove_cvref_t<EXECUTION_POLICY>>
auto split(std::string_view input, std::function<std::expected<TOKEN, std::error_code>(std::string_view)> tokenProducer,
           EXECUTION_POLICY && policy, char delimiter)
    -> std::expected<std::array<CONTAINER<TOKEN>, COLUMN_AMOUNT>, std::error_code> {
    auto lines = input | std::views::split('\n') |
                 std::views::transform([](auto && chars) { return std::string_view(chars.begin(), chars.end()); }) |
                 std::views::filter([](auto sv) { return !isOnlyWhitespace(sv); }) |
                 aoc::ranges::to<std::vector<std::string_view>>;

    threads::concurrent_context<std::error_code> context;
    std::vector<std::array<CONTAINER<TOKEN>, COLUMN_AMOUNT>> thread_local_sets(
        aoc::execution_policy_traits::is_parallel_policy_v<EXECUTION_POLICY> ? std::thread::hardware_concurrency() : 1);

    std::for_each(std::forward<EXECUTION_POLICY>(policy), lines.begin(), lines.end(),
                  [&](std::string_view const & line) {
                      unsigned long long thread_id =
                          std::hash<std::thread::id>{}(std::this_thread::get_id()) % thread_local_sets.size();
                      processLineIntoSets<TOKEN, COLUMN_AMOUNT, CONTAINER>(line, thread_local_sets, thread_id, context,
                                                                           tokenProducer, delimiter);
                  });

    if (context.hasValue()) {
        return std::unexpected(context.getValue());
    }

    return mergeSets<TOKEN, COLUMN_AMOUNT, CONTAINER>(thread_local_sets);
}

template <typename TOKEN, size_t COLUMN_AMOUNT, template <typename...> typename CONTAINER>
auto split(std::string_view input,
           std::function<std::expected<TOKEN, std::error_code>(std::string_view)> tokenProducery, char delimiter)
    -> std::expected<std::array<CONTAINER<TOKEN>, COLUMN_AMOUNT>, std::error_code> {
    return split<TOKEN, COLUMN_AMOUNT, CONTAINER>(input, tokenProducery, std::execution::unseq, delimiter);
}

template <typename TOKEN, size_t COLUMN_AMOUNT, template <typename...> typename CONTAINER>
static auto mergeSets(std::vector<std::array<CONTAINER<TOKEN>, COLUMN_AMOUNT>> const & thread_local_sets)
    -> std::array<CONTAINER<TOKEN>, COLUMN_AMOUNT> {
    std::array<CONTAINER<TOKEN>, COLUMN_AMOUNT> result;

    for (auto const & local_sets : thread_local_sets) {
        for (size_t i = 0; i < COLUMN_AMOUNT; ++i) {
            for (auto const & value : local_sets[i]) {
                aoc::container::container_traits<CONTAINER<TOKEN>>::insert(result[i], value);
            }
        }
    }
    return result;
}

template <typename TOKEN, size_t COLUMN_AMOUNT, template <typename...> typename CONTAINER>
static void processLineIntoSets(std::string_view const & line,
                                std::vector<std::array<CONTAINER<TOKEN>, COLUMN_AMOUNT>> & sets, size_t thread_id,
                                threads::concurrent_context<std::error_code> & context,
                                std::function<std::expected<TOKEN, std::error_code>(std::string_view)> tokenProducer,
                                char delimiter) {
    if (context.hasValue()) {
        return;
    }

    auto result = tokenizeLine<TOKEN, COLUMN_AMOUNT>(line, tokenProducer, delimiter);
    if (!result) {
        context.setValue(result.error());
        return;
    }

    for (size_t i = 0; i < COLUMN_AMOUNT; ++i) {
        aoc::container::container_traits<CONTAINER<TOKEN>>::insert(sets[thread_id][i], (*result)[i]);
    }
}

template <typename TOKEN, size_t COLUMN_AMOUNT>
static auto tokenizeLine(std::string_view line,
                         std::function<std::expected<TOKEN, std::error_code>(std::string_view)> tokenProducer,
                         char delimiter) -> std::expected<std::array<TOKEN, COLUMN_AMOUNT>, std::error_code> {
    using enum std::errc;

    std::string normalized = normalizeTabs(line);
    std::vector<std::expected<TOKEN, std::error_code>> tokens =
        std::string_view{normalized} | std::views::split(delimiter) | std::views::transform([](auto && chars) {
            auto sv = std::string_view(chars.begin(), chars.end());
            auto start = sv.find_first_not_of(WHITESPACE_CHARS);
            if (start == std::string_view::npos) {
                return std::string_view{};
            }
            auto end = sv.find_last_not_of(WHITESPACE_CHARS);
            return sv.substr(start, end - start + 1);
        }) |
        std::views::filter([](auto && sv) { return !isOnlyWhitespace(sv); }) | std::views::transform(tokenProducer) |
        aoc::ranges::to<std::vector<std::expected<TOKEN, std::error_code>>>;

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

} // namespace aoc::splitter::columnbased