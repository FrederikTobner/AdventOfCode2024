
#include "pattern_matcher.hpp"
#include <charconv>
#include <expected>
#include <regex>
#include <string>

namespace aoc::pattern_matcher {

enum class MatchType {
    Multiplication,
    DisableProcessing,
    EnableProcessing
};

struct ParsedMatch {
    MatchType type;
    std::pair<uint16_t, uint16_t> numbers{0, 0};
};

[[nodiscard]] std::expected<ParsedMatch, std::string> parseMatch(std::smatch const & match) {
    if (match[4].matched) {
        return ParsedMatch{MatchType::DisableProcessing};
    }
    if (match[5].matched) {
        return ParsedMatch{MatchType::EnableProcessing};
    }
    if (match[1].matched) {
        uint16_t num1{}, num2{};
        std::string_view num1_str{match[2].first, match[2].second};
        std::string_view num2_str{match[3].first, match[3].second};

        auto [ptr1, ec1] = std::from_chars(num1_str.data(), num1_str.data() + num1_str.size(), num1);
        auto [ptr2, ec2] = std::from_chars(num2_str.data(), num2_str.data() + num2_str.size(), num2);

        if (ec1 == std::errc{} && ec2 == std::errc{}) {
            return ParsedMatch{MatchType::Multiplication, {num1, num2}};
        }
        return std::unexpected("Failed to parse numbers");
    }
    return std::unexpected("Invalid match pattern");
}
std::vector<std::pair<uint16_t, uint16_t>> findMultiplicationPairs(std::string_view text) {
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

std::vector<std::pair<uint16_t, uint16_t>> findMultiplicationPairsWithToggle(std::string_view text) {
    std::vector<std::pair<uint16_t, uint16_t>> matches;
    static const std::regex pattern{R"((mul\((\d+),(\d+)\))|(don't\(\))|(do\(\)))"};
    std::string text_copy{text};

    bool process_matches = true;

    for (auto it = std::sregex_iterator{text_copy.begin(), text_copy.end(), pattern}; it != std::sregex_iterator{};
         ++it) {

        if (auto parsed = parseMatch(*it)) {
            switch (parsed->type) {
            case MatchType::DisableProcessing:
                process_matches = false;
                break;
            case MatchType::EnableProcessing:
                process_matches = true;
                break;
            case MatchType::Multiplication:
                if (process_matches) {
                    matches.push_back(parsed->numbers);
                }
                break;
            }
        }
    }
    return matches;
}

} // namespace aoc::pattern_matcher