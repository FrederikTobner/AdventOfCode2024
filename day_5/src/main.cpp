#include "../lib/page_ordering_rule.hpp"
#include "../lib/rules_validator.hpp"

#include <algorithm>
#include <array>
#include <execution>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>
#include <utility>

#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/line_splitter.hpp"
#include "../../shared/src/parsing_rules.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"

auto parse_input(std::string_view input) {
    constexpr auto delimiters = std::array{"\r\n\r\n", "\n\n"};
    auto split_pos =
        std::ranges::find_if(delimiters, [&](auto delim) { return input.find(delim) != std::string_view::npos; });

    if (split_pos == delimiters.end()) {
        return std::pair{input, std::string_view{}};
    }

    auto const split_at = input.find(*split_pos);
    return std::pair{input.substr(0, split_at), input.substr(split_at)};
}

auto parse_rules(std::string_view rules_str) {
    auto rules_result = aoc::splitter::linebased::split<uint8_t, std::vector, 2>(
        rules_str, aoc::parser::rules::parse_number<uint8_t>, std::execution::seq, '|');

    if (!rules_result) {
        std::println(stderr, "Failed to parse rules: {}", rules_result.error().message());
        exit(aoc::EXIT_CODE_DATA_ERROR);
    }
    return *rules_result | std::views::transform([](auto const & rule) {
        return aoc::day_5::page_ordering_rule{rule[0], rule[1]};
    }) | std::ranges::to<std::vector>();
}

auto main(int argc, char const ** argv) -> int {
    auto input = aoc::file_operations::read("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return aoc::EXIT_CODE_IO_ERROR;
    }

    auto const [rules_str, updates_str] = parse_input(*input);
    auto page_ordering_rules = parse_rules(rules_str);

    auto updates_result = aoc::splitter::linebased::split<uint8_t, std::vector>(
        updates_str, aoc::parser::rules::parse_number<uint8_t>, std::execution::seq, ',');

    auto validator = aoc::day_5::rules_validator(page_ordering_rules);

    uint64_t sum_valid = 0, sum_invalid = 0;

    for (auto & update_values : *updates_result) {
        auto update = aoc::day_5::page_update{std::move(update_values)};
        bool is_valid = validator.validate_and_fix(update);

        if (auto middle = update.getMiddleElement()) {
            if (is_valid) {
                sum_valid += *middle;
            } else {
                sum_invalid += *middle;
            }
        }
    }

    std::println("The sum of valid middle elements is: {:#}", sum_valid);
    std::println("The sum of invalid middle elements is: {:#}", sum_invalid);

    return 0;
}
