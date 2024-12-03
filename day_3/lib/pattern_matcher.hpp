#pragma once

#include <charconv>
#include <regex>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace aoc::pattern_matcher {

[[nodiscard]] std::vector<std::pair<uint16_t, uint16_t>> findMultiplicationPairs(std::string_view text);

[[nodiscard]] std::vector<std::pair<uint16_t, uint16_t>> findMultiplicationPairsWithToggle(std::string_view text);

[[nodiscard]] std::vector<std::pair<uint16_t, uint16_t>> findMultiplicationPairs(std::string_view text) {
    std::vector<std::pair<uint16_t, uint16_t>> matches;
    std::smatch match;
    std::regex pattern(R"(mul\((\d+),(\d+)\))");
    std::string textCopy{text};
    while (std::regex_search(textCopy, match, pattern)) {
        matches.emplace_back(std::stoi(match.str(1)), std::stoi(match.str(2)));
        textCopy = match.suffix();
    }
    return matches;
}

[[nodiscard]] std::vector<std::pair<uint16_t, uint16_t>> findMultiplicationPairsWithToggle(std::string_view text) {
    std::vector<std::pair<uint16_t, uint16_t>> matches;
    matches.reserve(32);

    static const std::regex pattern{R"((mul\((\d+),(\d+)\))|(don't\(\))|(do\(\)))"};
    std::string text_copy{text};

    bool process_matches = true;
    uint16_t num1{}, num2{};

    for (auto it = std::sregex_iterator{text_copy.begin(), text_copy.end(), pattern}; it != std::sregex_iterator{};
         ++it) {
        auto const & match = *it;

        if (match[4].matched) {
            process_matches = false;
        } else if (match[5].matched) {
            process_matches = true;
        } else if (process_matches && match[1].matched) {
            std::string_view num1_str{match[2].first, match[2].second};
            std::string_view num2_str{match[3].first, match[3].second};

            std::from_chars(num1_str.data(), num1_str.data() + num1_str.size(), num1);
            std::from_chars(num2_str.data(), num2_str.data() + num2_str.size(), num2);

            matches.emplace_back(num1, num2);
        }
    }

    return matches;
}
} // namespace aoc::pattern_matcher