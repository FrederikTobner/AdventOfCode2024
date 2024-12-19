#pragma once

#include <cstdint>
#include <optional>
#include <string_view>

#include "matcher.hpp"

namespace aoc::day_19 {

/// @brief Strategy class for counting pattern matches
struct count_processing_strategy {
    pattern_matcher * matcher; ///< Pointer to associated pattern matcher

    /// @brief Handles maximum recursion depth case
    /// @return Zero to indicate no valid combinations
    [[nodiscard]] auto handle_max_depth() const -> size_t;

    /// @brief Handles empty design case
    /// @return One to indicate one valid combination found
    [[nodiscard]] auto handle_empty() const -> size_t;

    /// @brief Checks cache for existing count
    /// @param design Design string to check
    /// @param state Current matcher state
    /// @return Optional containing cached count if available
    [[nodiscard]] auto check_cache(std::string_view design, pattern_matcher_state & state) const
        -> std::optional<size_t>;

    /// @brief Provides initial value for counting
    /// @return Initial zero count
    [[nodiscard]] auto initial_value() const -> size_t;

    /// @brief Processes a single pattern match for counting
    /// @param next_design Remaining design after current match
    /// @param next_depth Next recursion depth
    /// @param current_total Current count total
    /// @param state Current matcher state
    /// @return Updated total count
    [[nodiscard]] auto process_match(std::string_view next_design, size_t next_depth, size_t current_total,
                                     pattern_matcher_state & state) const -> size_t;

    /// @brief Determines if counting should stop
    /// @param ignored Unused size_t parameter
    /// @return Always false as all combinations need to be counted
    [[nodiscard]] auto should_break(size_t) const -> bool;

    /// @brief Updates the cache with count result
    /// @param design Design string being processed
    /// @param result Count result to cache
    /// @param state Current matcher state
    auto update_cache(std::string_view design, size_t result, pattern_matcher_state & state) -> void;
};

} // namespace aoc::day_19
