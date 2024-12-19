#pragma once

#include <algorithm>
#include <regex>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace aoc::day_19 {

/// @brief State object for pattern matching operations containing caches
struct pattern_matcher_state {
    std::unordered_map<std::string_view, bool> m_match_cache;   ///< Cache for match results
    std::unordered_map<std::string_view, size_t> m_count_cache; ///< Cache for count results
};

class count_processing_strategy;
class match_processing_strategy;

/// @brief Class for matching patterns against designs and counting possible combinations
class pattern_matcher {
    friend class count_processing_strategy;
    friend class match_processing_strategy;

  public:
    /// @brief Constructs a pattern matcher with given patterns
    /// @param patterns Vector of pattern strings to match against
    explicit pattern_matcher(std::vector<std::string> patterns);

    /// @brief Checks if a design can be constructed using the patterns
    /// @param design The design string to check
    /// @return True if the design can be constructed, false otherwise
    [[nodiscard]] bool can_construct(std::string_view design);

    /// @brief Counts unique ways to construct a design using the patterns
    /// @param design The design string to analyze
    /// @return Number of unique ways to construct the design
    [[nodiscard]] size_t count_unique_ways_to_construct(std::string_view design);

  private:
    static constexpr size_t MAX_RECURSION_DEPTH = 100; ///< Maximum recursion depth to prevent stack overflow
    std::vector<std::regex> m_patterns;                ///< Compiled regex patterns

    /// @brief Template method for processing patterns with different strategies
    /// @tparam Func Strategy type for processing
    /// @param remaining_design Remaining design to process
    /// @param depth Current recursion depth
    /// @param processing_strategy Strategy object for processing
    /// @param state Current matcher state
    /// @return Result of processing based on strategy type
    template <typename Func>
    [[nodiscard]] auto process_patterns(std::string_view remaining_design, size_t depth, Func && processing_strategy,
                                        pattern_matcher_state & state) {
        if (depth >= MAX_RECURSION_DEPTH) {
            return processing_strategy.handle_max_depth();
        }
        if (remaining_design.empty()) {
            return processing_strategy.handle_empty();
        }

        if (auto cached = processing_strategy.check_cache(remaining_design, state)) {
            return *cached;
        }

        auto result = processing_strategy.initial_value();
        for (auto const & pattern : m_patterns) {
            std::match_results<std::string_view::const_iterator> match;
            if (std::regex_search(remaining_design.begin(), remaining_design.end(), match, pattern,
                                  std::regex_constants::match_continuous)) {
                result = processing_strategy.process_match(remaining_design.substr(match.length()), depth + 1, result,
                                                           state);
                if (processing_strategy.should_break(result)) {
                    break;
                }
            }
        }

        processing_strategy.update_cache(remaining_design, result, state);
        return result;
    }

    /// @brief Recursive counting implementation
    [[nodiscard]] size_t count_recursive(std::string_view remaining_design, size_t depth,
                                         pattern_matcher_state & state);

    /// @brief Recursive matching implementation
    [[nodiscard]] bool match_recursive(std::string_view remaining_design, size_t depth, pattern_matcher_state & state);
};

} // namespace aoc::day_19