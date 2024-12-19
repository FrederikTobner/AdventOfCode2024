#include "matcher.hpp"

#include <algorithm>
#include <regex>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "count_callback.hpp"
#include "match_callback.hpp"

namespace aoc::day_19 {

pattern_matcher::pattern_matcher(std::vector<std::string> patterns) {
    std::ranges::sort(patterns, std::ranges::greater{}, [](auto const & p) { return p.length(); });

    for (auto const & p : patterns) {
        m_patterns.emplace_back(p, std::regex_constants::optimize);
    }
}

[[nodiscard]] bool pattern_matcher::can_construct(std::string_view design) {
    m_match_cache.clear();
    return match_recursive(design, 0);
}

[[nodiscard]] size_t pattern_matcher::count_unique_ways_to_construct(std::string_view design) {
    m_count_cache.clear();
    return count_recursive(design, 0);
}

[[nodiscard]] bool pattern_matcher::match_recursive(std::string_view remaining_design, size_t depth) {
    return process_patterns(remaining_design, depth, match_callback{this});
}

[[nodiscard]] size_t pattern_matcher::count_recursive(std::string_view remaining_design, size_t depth) {
    return process_patterns(remaining_design, depth, count_callback{this});
}

} // namespace aoc::day_19