#include "../lib/page_ordering_rule.hpp"
#include "../lib/rules_validator.hpp"
#include <algorithm>
#include <array>
#include <execution>
#include <expected>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>
#include <system_error>
#include <utility>

#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/line_splitter.hpp"
#include "../../shared/src/parsing_rules.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"
#include "../../shared/src/ranges_compatibility_layer.hpp"

auto parse_input(std::string_view input)
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

auto parse_rules(std::string_view rules_str)
    -> std::expected<std::vector<aoc::day_5::page_ordering_rule>, std::error_code> {
    auto rules_result = aoc::splitter::linebased::split<uint8_t, std::vector, 2>(
        rules_str, aoc::parser::rules::parse_number<uint8_t>, std::execution::seq, '|');

    if (!rules_result) {
        return std::unexpected(rules_result.error());
    }

    return *rules_result | std::views::transform([](auto const & rule) {
        return aoc::day_5::page_ordering_rule{rule[0], rule[1]};
    }) | aoc::ranges::to<std::vector<aoc::day_5::page_ordering_rule>>;
}

struct sum_result {
    uint64_t valid = 0;
    uint64_t invalid = 0;
};

auto main(int argc, char const ** argv) -> int {
    auto input = aoc::file_operations::read("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return aoc::EXIT_CODE_IO_ERROR;
    }

    auto split_input = parse_input(*input);
    if (!split_input) {
        std::println(stderr, "Failed to split input: {}", split_input.error().message());
        return aoc::EXIT_CODE_DATA_ERROR;
    }

    auto const & [rules_input, updates_input] = *split_input;
    auto page_ordering_rules = parse_rules(rules_input);
    if (!page_ordering_rules) {
        std::println(stderr, "Failed to parse rules: {}", page_ordering_rules.error().message());
        return aoc::EXIT_CODE_DATA_ERROR;
    }

    auto updates_result = aoc::splitter::linebased::split<uint8_t, std::vector>(
        updates_input, aoc::parser::rules::parse_number<uint8_t>, std::execution::seq, ',');

    if (!updates_result) {
        std::println(stderr, "Failed to parse updates: {}", updates_result.error().message());
        return aoc::EXIT_CODE_DATA_ERROR;
    }

    auto validator = aoc::day_5::rules_validator(*std::move(page_ordering_rules));

    auto [sum_valid, sum_invalid] =
        aoc::ranges::fold_left(*updates_result, sum_result{}, [&validator](sum_result acc, auto & update_values) {
            auto update = aoc::day_5::page_update{std::move(update_values)};
            bool is_valid = validator.validate_and_fix(update);
            auto middle = update.getMiddleElement();
            if (is_valid) {
                acc.valid += middle;
            } else {
                acc.invalid += middle;
            }
            return acc;
        });

    std::println("The sum of valid middle elements is: {:#}", sum_valid);
    std::println("The sum of invalid middle elements is: {:#}", sum_invalid);

    return 0;
}
