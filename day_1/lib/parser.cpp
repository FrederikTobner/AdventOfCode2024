/**
 * @file parser.cpp
 * @brief Implementation of input parsing functionality
 * @details Contains the implementation of parsing functions declared in parser.hpp.
 * Handles the conversion of string input into numerical data structures with
 * proper error handling.
 */

#include "parser.hpp"
#include "../../shared/ranges_compatibility_layer.hpp"

#include <algorithm>
#include <atomic>
#include <execution>
#include <mutex>
#include <ranges>
#include <string>
#include <thread>
#include <vector>

namespace parser {

static auto processLinesInParallel(std::span<std::string_view const> lines)
    -> std::expected<std::pair<std::multiset<int64_t>, std::multiset<int64_t>>, std::error_code>;

static auto processLinesSequential(std::span<std::string_view const> lines)
    -> std::expected<std::pair<std::multiset<int64_t>, std::multiset<int64_t>>, std::error_code>;

auto parseLine(std::string_view line) -> std::expected<std::pair<int64_t, int64_t>, std::error_code> {
    using enum std::errc;

    std::vector<std::expected<int64_t, std::error_code>> results =
        nonstd::ranges::to_vector(line | std::views::split(' ') |
                                  std::views::filter([](auto && range) { return !std::string_view(range).empty(); }) |
                                  std::views::transform([](auto && range) -> std::expected<int64_t, std::error_code> {
                                      try {
                                          return std::stoll(std::string(range.begin(), range.end()));
                                      } catch (...) {
                                          return std::unexpected(std::make_error_code(invalid_argument));
                                      }
                                  }));

    if (results.size() != 2 || !results[0] || !results[1]) {
        return std::unexpected(std::make_error_code(invalid_argument));
    }

    return std::pair{*results[0], *results[1]};
}

auto parseInput(std::string_view input, ProcessingMode mode)
    -> std::expected<std::pair<std::multiset<int64_t>, std::multiset<int64_t>>, std::error_code> {
    auto lines = nonstd::ranges::to_vector(input | std::views::split('\n') | std::views::transform([](auto && chars) {
                                               return std::string_view(chars.begin(), chars.end());
                                           }) |
                                           std::views::filter([](auto sv) { return !isOnlyWhitespace(sv); }));

    return mode == ProcessingMode::Parallel ? processLinesInParallel(lines) : processLinesSequential(lines);
}

static auto processLinesInParallel(std::span<std::string_view const> lines)
    -> std::expected<std::pair<std::multiset<int64_t>, std::multiset<int64_t>>, std::error_code> {
    std::vector<std::pair<std::multiset<int64_t>, std::multiset<int64_t>>> thread_local_sets;
    thread_local_sets.resize(std::thread::hardware_concurrency());

    std::atomic<bool> error_occurred{false};
    std::mutex error_mutex;
    std::error_code first_error;

    std::for_each(std::execution::par_unseq, lines.begin(), lines.end(), [&](std::string_view const & line) {
        if (error_occurred.load(std::memory_order_relaxed)) {
            return;
        }

        std::expected<std::pair<int64_t, int64_t>, std::error_code> result = parseLine(line);
        if (!result) {
            if (!error_occurred.exchange(true, std::memory_order_relaxed)) {
                std::scoped_lock lock(error_mutex);
                first_error = result.error();
            }
            return;
        }

        unsigned long long thread_id =
            std::hash<std::thread::id>{}(std::this_thread::get_id()) % thread_local_sets.size();
        std::pair<std::multiset<int64_t>, std::multiset<int64_t>> & local_sets = thread_local_sets[thread_id];
        local_sets.first.insert(result->first);
        local_sets.second.insert(result->second);
    });

    if (error_occurred) {
        return std::unexpected(first_error);
    }

    std::multiset<int64_t> set1, set2;
    for (std::pair<std::multiset<int64_t>, std::multiset<int64_t>> const & local_sets : thread_local_sets) {
        set1.insert(local_sets.first.begin(), local_sets.first.end());
        set2.insert(local_sets.second.begin(), local_sets.second.end());
    }

    return std::pair{std::move(set1), std::move(set2)};
}

static auto processLinesSequential(std::span<std::string_view const> lines)
    -> std::expected<std::pair<std::multiset<int64_t>, std::multiset<int64_t>>, std::error_code> {
    std::multiset<int64_t> set1, set2;

    for (auto const & line : lines) {
        auto result = parseLine(line);
        if (!result) {
            return std::unexpected(result.error());
        }
        set1.insert(result->first);
        set2.insert(result->second);
    }

    return std::pair{std::move(set1), std::move(set2)};
}

} // namespace parser