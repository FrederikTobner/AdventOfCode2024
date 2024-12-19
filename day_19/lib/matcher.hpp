#pragma once

#include <algorithm>
#include <regex>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace aoc::day_19 {

class pattern_matcher {
  private:
    static constexpr size_t MAX_RECURSION_DEPTH = 100;
    std::vector<std::regex> m_patterns;
    std::unordered_map<std::string_view, bool> m_match_cache;
    std::unordered_map<std::string_view, size_t> m_count_cache;

    size_t count_recursive(std::string_view remaining_design, size_t depth) {
        if (depth >= MAX_RECURSION_DEPTH) {
            return 0;
        }
        if (remaining_design.empty()) {
            return 1;
        }

        if (auto it = m_count_cache.find(remaining_design); it != m_count_cache.end()) {
            return it->second;
        }

        size_t total = 0;
        for (auto const & pattern : m_patterns) {
            std::match_results<std::string_view::const_iterator> match;
            if (std::regex_search(remaining_design.begin(), remaining_design.end(), match, pattern,
                                  std::regex_constants::match_continuous)) {
                size_t len = match.length();
                total += count_recursive(remaining_design.substr(len), depth + 1);
            }
        }

        m_count_cache[remaining_design] = total;
        return total;
    }

    bool match_recursive(std::string_view remaining_design, size_t depth) {
        if (depth >= MAX_RECURSION_DEPTH) {
            return false;
        }
        if (remaining_design.empty()) {
            return true;
        }

        if (auto it = m_match_cache.find(remaining_design); it != m_match_cache.end()) {
            return it->second;
        }

        for (auto const & pattern : m_patterns) {
            std::match_results<std::string_view::const_iterator> match;
            if (std::regex_search(remaining_design.begin(), remaining_design.end(), match, pattern,
                                  std::regex_constants::match_continuous)) {
                size_t len = match.length();
                if (match_recursive(remaining_design.substr(len), depth + 1)) {
                    m_match_cache[remaining_design] = true;
                    return true;
                }
            }
        }

        m_match_cache[remaining_design] = false;
        return false;
    }

  public:
    explicit pattern_matcher(std::vector<std::string> patterns) {
        std::ranges::sort(patterns, std::ranges::greater{}, [](auto const & p) { return p.length(); });

        for (auto const & p : patterns) {
            m_patterns.emplace_back(p, std::regex_constants::optimize);
        }
    }

    bool can_construct(std::string_view design) {
        m_match_cache.clear();
        return match_recursive(design, 0);
    }

    size_t count_unique_ways_to_construct(std::string_view design) {
        m_count_cache.clear();
        return count_recursive(design, 0);
    }
};

} // namespace aoc::day_19