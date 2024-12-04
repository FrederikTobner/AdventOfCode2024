/**
 * @file Lexer.hpp
 * @brief This file contains the implementation of a lexer for tokenizing input text in lines
 * @details The processing mode can be set to either Sequential or Parallel, with the latter being
 * out of order but potentially faster for large inputs
 */

#pragma once

#include <algorithm>
#include <charconv>
#include <cstdint>
#include <execution>
#include <expected>
#include <functional>
#include <ranges>
#include <string>
#include <string_view>
#include <system_error>
#include <thread>
#include <vector>

#include "concurrent_context.hpp"
#include "execution_policy_traits.hpp"
#include "lexer.hpp"
#include "ranges_compatibility_layer.hpp"

/**
 * @brief Namespace containing lexer functionality for parsing and tokenizing input
 * @details Provides utilities for converting text input into tokens, with support for
 *          both sequential and parallel processing modes
 */
namespace aoc::lexer::linebased {

/**
 * @brief Tokenizes input text into vectors of strongly-typed tokens
 * @tparam TOKEN_TYPE The type to convert each token into
 * @tparam EXPECTED_SIZE Expected number of tokens per line (0 for variable length)
 * @param input The input text to tokenize
 * @param tokenProducer Function to convert string tokens into the desired type
 * @param policy Execution policy to use for parallel processing
 * @param delimiter Character to split tokens on
 * @return Expected vector of vector of tokens, or error code on failure
 */
template <typename TOKEN_TYPE, size_t EXPECTED_SIZE = 0, typename EXECUTION_POLICY>
    requires std::is_execution_policy_v<std::remove_cvref_t<EXECUTION_POLICY>>
auto tokenize(std::string_view input,
              std::function<std::expected<TOKEN_TYPE, std::error_code>(std::string_view)> tokenProducer,
              EXECUTION_POLICY && policy, char delimiter = ' ')
    -> std::expected<std::vector<std::vector<TOKEN_TYPE>>, std::error_code>;

/// @brief Tokenizes input text into vectors of strongly-typed tokens
/// @tparam TOKEN_TYPE The type to convert each token into
/// @param input The input text to tokenize
/// @param tokenProducer Function to convert string tokens into the desired type
/// @param delimiter Character to split tokens on
/// @return Expected vector of vector of tokens, or error code on failure
template <typename TOKEN_TYPE, size_t EXPECTED_SIZE = 0>
auto tokenize(std::string_view input,
              std::function<std::expected<TOKEN_TYPE, std::error_code>(std::string_view)> tokenProducer,
              char delimiter = ' ') -> std::expected<std::vector<std::vector<TOKEN_TYPE>>, std::error_code>;

/**
 * @brief Processes a single line of input into tokens for a specific thread
 * @tparam TOKEN_TYPE The type to convert each token into
 * @tparam EXPECTED_SIZE Expected number of tokens in the line
 * @param line The input line to process
 * @param tokens Thread-local storage for token results
 * @param thread_id ID of the current thread
 * @param context Concurrent context for error handling
 * @param tokenProducer Function to convert string tokens into the desired type
 */
template <typename TOKEN_TYPE, size_t EXPECTED_SIZE>
static void
processLineIntoSets(std::string_view const & line, std::vector<std::vector<std::vector<TOKEN_TYPE>>> & tokens,
                    size_t thread_id, threads::concurrent_context<std::error_code> & context,
                    std::function<std::expected<TOKEN_TYPE, std::error_code>(std::string_view)> tokenProducer,
                    char delimiter);

/**
 * @brief Merges thread-local token sets into a single result vector
 * @tparam TOKEN_TYPE The type of tokens to merge
 * @param thread_local_vectors Vector of thread-local token sets to merge
 * @return Combined vector of all token sets
 */
template <typename TOKEN_TYPE>
static auto mergeVectors(std::vector<std::vector<std::vector<TOKEN_TYPE>>> const & thread_local_vectors)
    -> std::vector<std::vector<TOKEN_TYPE>>;

/**
 * @brief Tokenizes a single line of input into strongly-typed tokens
 * @tparam TOKEN_TYPE The type to convert each token into
 * @tparam EXPECTED_SIZE Expected number of tokens in the line
 * @param line The input line to tokenize
 * @param tokenProducer Function to convert string tokens into the desired type
 * @return Expected vector of tokens, or error code on failure
 */
template <typename TOKEN_TYPE, size_t EXPECTED_SIZE>
static auto tokenizeLine(std::string_view line,
                         std::function<std::expected<TOKEN_TYPE, std::error_code>(std::string_view)> tokenProducer,
                         char delimiter) -> std::expected<std::vector<TOKEN_TYPE>, std::error_code>;

template <typename TOKEN_TYPE, size_t EXPECTED_SIZE, typename EXECUTION_POLICY>
    requires std::is_execution_policy_v<std::remove_cvref_t<EXECUTION_POLICY>>
auto tokenize(std::string_view input,
              std::function<std::expected<TOKEN_TYPE, std::error_code>(std::string_view)> tokenProducer,
              EXECUTION_POLICY && policy, char delimiter)
    -> std::expected<std::vector<std::vector<TOKEN_TYPE>>, std::error_code> {

    auto lines = input | std::views::split('\n') |
                 std::views::transform([](auto && chars) { return std::string_view(chars.begin(), chars.end()); }) |
                 std::views::filter([](std::string_view sv) { return !isOnlyWhitespace(sv); });

    size_t line_count = std::ranges::distance(lines);

    const size_t thread_count =
        aoc::execution_policy_traits::is_parallel_policy_v<EXECUTION_POLICY> ? std::thread::hardware_concurrency() : 1;
    std::vector<std::vector<std::vector<TOKEN_TYPE>>> thread_local_vectors(thread_count);

    for (auto & local_vector : thread_local_vectors) {
        local_vector.reserve(line_count / thread_count + 1);
    }

    threads::concurrent_context<std::error_code> context;

    std::for_each(std::forward<EXECUTION_POLICY>(policy), lines.begin(), lines.end(),
                  [&](std::string_view const & line) {
                      size_t thread_id = std::hash<std::thread::id>{}(std::this_thread::get_id()) % thread_count;
                      processLineIntoSets<TOKEN_TYPE, EXPECTED_SIZE>(line, thread_local_vectors, thread_id, context,
                                                                     tokenProducer, delimiter);
                  });

    if (context.hasValue()) {
        return std::unexpected(context.getValue());
    }

    size_t total_size = 0;
    for (auto const & local_vector : thread_local_vectors) {
        total_size += local_vector.size();
    }

    std::vector<std::vector<TOKEN_TYPE>> result;
    result.reserve(total_size);

    return mergeVectors<TOKEN_TYPE>(thread_local_vectors);
}

template <typename TOKEN_TYPE, size_t EXPECTED_SIZE>
static void
processLineIntoSets(std::string_view const & line, std::vector<std::vector<std::vector<TOKEN_TYPE>>> & tokens,
                    size_t thread_id, threads::concurrent_context<std::error_code> & context,
                    std::function<std::expected<TOKEN_TYPE, std::error_code>(std::string_view)> tokenProducer,
                    char delimiter) {
    if (context.hasValue()) {
        return;
    }

    auto result = tokenizeLine<TOKEN_TYPE, EXPECTED_SIZE>(line, tokenProducer, delimiter);
    if (!result) {
        context.setValue(result.error());
        return;
    }

    static std::mutex mutex;
    std::lock_guard<std::mutex> lock(mutex);
    tokens[thread_id].push_back(std::move(*result));
}

template <typename TOKEN_TYPE, size_t EXPECTED_SIZE>
static auto tokenizeLine(std::string_view line,
                         std::function<std::expected<TOKEN_TYPE, std::error_code>(std::string_view)> tokenProducer,
                         char delimiter) -> std::expected<std::vector<TOKEN_TYPE>, std::error_code> {
    std::string normalized = normalizeTabs(line);
    auto tokens = std::string_view{normalized} | std::views::split(delimiter) |
                  std::views::transform([](auto && chars) { return std::string_view(chars.begin(), chars.end()); }) |
                  std::views::filter([](std::string_view sv) { return !isOnlyWhitespace(sv); });

    std::vector<TOKEN_TYPE> result;
    if (EXPECTED_SIZE > 0 && std::ranges::distance(tokens) != EXPECTED_SIZE) {
        return std::unexpected(std::make_error_code(std::errc::invalid_argument));
    }

    for (auto const & token : tokens) {
        auto parsed = tokenProducer(token);
        if (!parsed) {
            return std::unexpected(parsed.error());
        }
        result.push_back(*parsed);
    }

    return result;
}

template <typename TOKEN_TYPE>
static auto mergeVectors(std::vector<std::vector<std::vector<TOKEN_TYPE>>> const & thread_local_vectors)
    -> std::vector<std::vector<TOKEN_TYPE>> {
    std::vector<std::vector<TOKEN_TYPE>> result;

    for (auto const & local_vector : thread_local_vectors) {
        result.insert(result.end(), local_vector.begin(), local_vector.end());
    }
    return result;
}

template <typename TOKEN_TYPE, size_t EXPECTED_SIZE>
auto tokenize(std::string_view input,
              std::function<std::expected<TOKEN_TYPE, std::error_code>(std::string_view)> tokenProducer, char delimiter)
    -> std::expected<std::vector<std::vector<TOKEN_TYPE>>, std::error_code> {
    return tokenize<TOKEN_TYPE, EXPECTED_SIZE>(input, tokenProducer, std::execution::par_unseq, delimiter);
}

} // namespace aoc::lexer::linebased