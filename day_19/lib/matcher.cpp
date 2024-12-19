#include "matcher.hpp"

#include <algorithm>
#include <regex>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "count_processing_strategy.hpp"
#include "match_processing_strategy.hpp"

namespace aoc::day_19 {

pattern_matcher::pattern_matcher(std::vector<std::string> patterns) {
    std::ranges::sort(patterns, std::ranges::greater{}, [](auto const & p) { return p.length(); });

    for (auto const & p : patterns) {
        m_patterns.emplace_back(p, std::regex_constants::optimize);
    }
}

[[nodiscard]] bool pattern_matcher::can_construct(std::string_view design) {
    pattern_matcher_state state;
    return match_recursive(design, 0, state);
}

[[nodiscard]] size_t pattern_matcher::count_unique_ways_to_construct(std::string_view design) {
    pattern_matcher_state state;
    return count_recursive(design, 0, state);
}

[[nodiscard]] bool pattern_matcher::match_recursive(std::string_view remaining_design, size_t depth,
                                                    pattern_matcher_state & state) {
    return process_patterns(remaining_design, depth, match_processing_strategy{this}, state);
}

[[nodiscard]] size_t pattern_matcher::count_recursive(std::string_view remaining_design, size_t depth,
                                                      pattern_matcher_state & state) {
    return process_patterns(remaining_design, depth, count_processing_strategy{this}, state);
}

} // namespace aoc::day_19