#pragma once

#include <algorithm>
#include <regex>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace aoc::day_19 {

class count_processing_strategy;
class match_processing_strategy;

class pattern_matcher {
    friend class count_processing_strategy;
    friend class match_processing_strategy;

  public:
    explicit pattern_matcher(std::vector<std::string> patterns);

    [[nodiscard]] bool can_construct(std::string_view design);

    [[nodiscard]] size_t count_unique_ways_to_construct(std::string_view design);

  private:
    static constexpr size_t MAX_RECURSION_DEPTH = 100;
    std::vector<std::regex> m_patterns;
    std::unordered_map<std::string_view, bool> m_match_cache;
    std::unordered_map<std::string_view, size_t> m_count_cache;

    template <typename Func>
    [[nodiscard]] auto process_patterns(std::string_view remaining_design, size_t depth, Func && processing_strategy) {
        if (depth >= MAX_RECURSION_DEPTH) {
            return processing_strategy.handle_max_depth();
        }
        if (remaining_design.empty()) {
            return processing_strategy.handle_empty();
        }

        if (auto cached = processing_strategy.check_cache(remaining_design)) {
            return *cached;
        }

        auto result = processing_strategy.initial_value();
        for (auto const & pattern : m_patterns) {
            std::match_results<std::string_view::const_iterator> match;
            if (std::regex_search(remaining_design.begin(), remaining_design.end(), match, pattern,
                                  std::regex_constants::match_continuous)) {
                result = processing_strategy.process_match(remaining_design.substr(match.length()), depth + 1, result);
                if (processing_strategy.should_break(result)) {
                    break;
                }
            }
        }

        processing_strategy.update_cache(remaining_design, result);
        return result;
    }

    [[nodiscard]] size_t count_recursive(std::string_view remaining_design, size_t depth);

    [[nodiscard]] bool match_recursive(std::string_view remaining_design, size_t depth);
};

} // namespace aoc::day_19