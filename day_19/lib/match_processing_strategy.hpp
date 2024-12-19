#pragma once

#include <cstdint>
#include <optional>
#include <string_view>

#include "matcher.hpp"

namespace aoc::day_19 {

/// @brief Strategy class for processing pattern matches
struct match_processing_strategy {
    pattern_matcher * matcher; ///< Pointer to associated pattern matcher

    /// @brief Handles maximum recursion depth case
    /// @return False to indicate matching failure
    [[nodiscard]] auto handle_max_depth() const -> bool;

    /// @brief Handles empty design case
    /// @return True to indicate successful match
    [[nodiscard]] auto handle_empty() const -> bool;

    /// @brief Checks cache for existing match result
    /// @param design Design string to check
    /// @param state Current matcher state
    /// @return Optional containing cached result if available
    [[nodiscard]] auto check_cache(std::string_view design, pattern_matcher_state & state) const -> std::optional<bool>;

    /// @brief Provides initial value for matching
    /// @return Initial false value
    [[nodiscard]] auto initial_value() const -> bool;

    /// @brief Processes a single pattern match
    /// @param next_design Remaining design after current match
    /// @param next_depth Next recursion depth
    /// @param ignored Currently unused boolean parameter
    /// @param state Current matcher state
    /// @return True if match is successful
    [[nodiscard]] auto process_match(std::string_view next_design, size_t next_depth, bool,
                                     pattern_matcher_state & state) const -> bool;

    /// @brief Determines if processing should stop
    /// @param result Current result
    /// @return True if processing should stop
    [[nodiscard]] auto should_break(bool result) const -> bool;

    /// @brief Updates the cache with match result
    /// @param design Design string being processed
    /// @param result Match result to cache
    /// @param state Current matcher state
    auto update_cache(std::string_view design, bool result, pattern_matcher_state & state) -> void;
};
} // namespace aoc::day_19