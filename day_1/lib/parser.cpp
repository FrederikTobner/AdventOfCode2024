/**
 * @file parser.cpp
 * @brief Implementation of input parsing functionality
 * @details Contains the implementation of parsing functions declared in parser.hpp.
 * Handles the conversion of string input into numerical data structures with
 * proper error handling.
 */

#include "parser.hpp"
#include "../../shared/ranges_compatibility_layer.hpp"
#include "concurrent_context.hpp"

#include <algorithm>
#include <atomic>
#include <execution>
#include <mutex>
#include <ranges>
#include <string>
#include <thread>
#include <vector>

namespace parser {

static bool isWhitespace(char c) {
    return c == ' ' || c == '\t';
}

static void processLineIntoSets(std::string_view const & line,
                                std::vector<std::pair<std::multiset<int64_t>, std::multiset<int64_t>>> & sets,
                                size_t thread_id, threads::concurrent_context<std::error_code> & context) {
    if (context.hasValue()) {
        return;
    }

    auto result = parseLine(line);
    if (!result) {
        context.setValue(result.error());
        return;
    }

    auto & [left, right] = sets[thread_id];
    left.insert(result->first);
    right.insert(result->second);
}

static auto mergeSets(std::vector<std::pair<std::multiset<int64_t>, std::multiset<int64_t>>> const & thread_local_sets)
    -> std::pair<std::multiset<int64_t>, std::multiset<int64_t>> {
    std::multiset<int64_t> left, right;
    for (auto const & [local_left, local_right] : thread_local_sets) {
        left.insert(local_left.begin(), local_left.end());
        right.insert(local_right.begin(), local_right.end());
    }
    return {std::move(left), std::move(right)};
}

auto parseLine(std::string_view line) -> std::expected<std::pair<int64_t, int64_t>, std::error_code> {
    using enum std::errc;

    std::vector<std::expected<int64_t, std::error_code>> tokens = nonstd::ranges::to_vector(
        line | std::views::split(' ') |
        std::views::transform([](auto && range) { return std::string_view(range.begin(), range.end()); }) |
        std::views::filter([](auto && sv) { return !isOnlyWhitespace(sv); }) |
        std::views::transform([](auto && sv) -> std::expected<int64_t, std::error_code> {
            try {
                return std::stoll(std::string(sv));
            } catch (...) {
                return std::unexpected(std::make_error_code(invalid_argument));
            }
        }));

    if (tokens.size() != 2 || !tokens[0] || !tokens[1]) {
        return std::unexpected(std::make_error_code(invalid_argument));
    }

    return std::pair{*tokens[0], *tokens[1]};
}

auto parseInput(std::string_view input, ProcessingMode mode)
    -> std::expected<std::pair<std::multiset<int64_t>, std::multiset<int64_t>>, std::error_code> {
    auto lines = nonstd::ranges::to_vector(input | std::views::split('\n') | std::views::transform([](auto && chars) {
                                               return std::string_view(chars.begin(), chars.end());
                                           }) |
                                           std::views::filter([](auto sv) { return !isOnlyWhitespace(sv); }));

    threads::concurrent_context<std::error_code> context;
    std::vector<std::pair<std::multiset<int64_t>, std::multiset<int64_t>>> thread_local_sets(
        mode == ProcessingMode::Parallel ? std::thread::hardware_concurrency() : 1);

    if (mode == ProcessingMode::Parallel) {
        // Execute with a parallel unsequenced policy to allow for parallel processing of the lines
        std::for_each(std::execution::par_unseq, lines.begin(), lines.end(), [&](std::string_view const & line) {
            unsigned long long thread_id =
                std::hash<std::thread::id>{}(std::this_thread::get_id()) % thread_local_sets.size();
            processLineIntoSets(line, thread_local_sets, thread_id, context);
        });
    } else {
        for (auto const & line : lines) {
            processLineIntoSets(line, thread_local_sets, 0, context);
        }
    }

    if (context.hasValue()) {
        return std::unexpected(context.getValue());
    }

    return mergeSets(thread_local_sets);
}

} // namespace parser