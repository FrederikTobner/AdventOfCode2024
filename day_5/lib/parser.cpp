#include "parser.hpp"

#include <algorithm>
#include <array>
#include <execution>
#include <ranges>
#include <string>

#include "../../shared/src/line_splitter.hpp"
#include "../../shared/src/parsing_rules.hpp"

auto aoc::day_5::parse_input(std::string_view input)
    -> std::expected<std::pair<std::string_view, std::string_view>, std::error_code> {
    constexpr auto delimiters = std::array{"\r\n\r\n", "\n\n"};
    auto split_pos =
        std::ranges::find_if(delimiters, [&](auto delim) { return input.find(delim) != std::string_view::npos; });

    if (split_pos == delimiters.end()) {
        return std::unexpected(std::make_error_code(std::errc::invalid_argument));
    }

    auto const split_at = input.find(*split_pos);
    return std::pair{input.substr(0, split_at), input.substr(split_at)};
}

auto aoc::day_5::parse_rules(std::string_view rules_str)
    -> std::expected<std::vector<aoc::day_5::page_ordering_rule>, std::error_code> {
    auto rules_result = aoc::splitter::linebased::split<uint8_t, std::vector, 2>(
        rules_str, aoc::parser::rules::parse_number<uint8_t>, std::execution::seq, '|');

    if (!rules_result) {
        return std::unexpected(rules_result.error());
    }

    return *rules_result | std::views::transform([](auto const & rule) {
        return aoc::day_5::page_ordering_rule{rule[0], rule[1]};
    }) | std::ranges::to<std::vector<aoc::day_5::page_ordering_rule>>();
}