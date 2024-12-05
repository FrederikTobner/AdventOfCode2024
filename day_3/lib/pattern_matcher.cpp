#include "pattern_matcher.hpp"
#include <charconv>
#include <expected>
#include <regex>
#include <string>

namespace aoc::day_3 {

enum class match_type {
    MULTIPLICATION,
    DISABLE_PROCESSING,
    ENABLE_PROCESSING
};

struct parsed_match {
    match_type type;
    std::pair<uint16_t, uint16_t> numbers{0, 0};
};

[[nodiscard]] std::expected<parsed_match, std::string> parseMatch(std::smatch const & match) {
    if (match[4].matched) {
        return parsed_match{match_type::DISABLE_PROCESSING};
    }
    if (match[5].matched) {
        return parsed_match{match_type::ENABLE_PROCESSING};
    }
    if (match[1].matched) {
        uint16_t num1{}, num2{};
        std::string_view num1_str{match[2].first, match[2].second};
        std::string_view num2_str{match[3].first, match[3].second};

        auto [ptr1, ec1] = std::from_chars(num1_str.data(), num1_str.data() + num1_str.size(), num1);
        auto [ptr2, ec2] = std::from_chars(num2_str.data(), num2_str.data() + num2_str.size(), num2);

        if (ec1 == std::errc{} && ec2 == std::errc{}) {
            return parsed_match{match_type::MULTIPLICATION, {num1, num2}};
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
#ifdef _MSC_VER
            switch (parsed->type) {
            case match_type::DISABLE_PROCESSING:
                process_matches = false;
                break;
            case match_type::ENABLE_PROCESSING:
                process_matches = true;
                break;
            case match_type::MULTIPLICATION:
                if (process_matches) {
                    matches.push_back(parsed->numbers);
                }
                break;
            }
#else // Using computed goto under GCC/Clang
            static void * dispatch_table[] = {&&multiplication_label, &&disable_label, &&enable_label};
            goto * dispatch_table[static_cast<int>(parsed->type)];

        multiplication_label:
            if (process_matches) {
                matches.push_back(parsed->numbers);
            }
            goto continue_label;
        disable_label:
            process_matches = false;
            goto continue_label;
        enable_label:
            process_matches = true;
        continue_label:
#endif
        }
    }
    return matches;
}

} // namespace aoc::day_3