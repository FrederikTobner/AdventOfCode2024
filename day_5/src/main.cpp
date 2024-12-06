#include <algorithm>
#include <cstdint>
#include <execution>
#include <expected>
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

#include "../lib/page_ordering_rule.hpp"
#include "../lib/parser.hpp"
#include "../lib/result_summary.hpp"
#include "../lib/rules_validator.hpp"

auto main(int argc, char const ** argv) -> int {
    std::expected<std::string, std::error_code> input = aoc::file_operations::read("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return aoc::EXIT_CODE_IO_ERROR;
    }

    std::expected<std::pair<std::string_view, std::string_view>, std::error_code> split_input =
        aoc::day_5::parse_input(*input);
    if (!split_input) {
        std::println(stderr, "Failed to split input: {}", split_input.error().message());
        return aoc::EXIT_CODE_DATA_ERROR;
    }

    auto const & [rules_input, updates_input] = *split_input;
    std::expected<std::vector<aoc::day_5::page_ordering_rule>, std::error_code> page_ordering_rules =
        aoc::day_5::parse_rules(rules_input);
    if (!page_ordering_rules) {
        std::println(stderr, "Failed to parse rules: {}", page_ordering_rules.error().message());
        return aoc::EXIT_CODE_DATA_ERROR;
    }

    std::expected<std::vector<std::vector<uint8_t>>, std::error_code> parsed_update_input =
        aoc::splitter::linebased::split<uint8_t, std::vector>(updates_input, aoc::parser::rules::parse_number<uint8_t>,
                                                              std::execution::par_unseq, ',');

    if (!parsed_update_input) {
        std::println(stderr, "Failed to parse updates: {}", parsed_update_input.error().message());
        return aoc::EXIT_CODE_DATA_ERROR;
    }

    std::vector<aoc::day_5::page_update> updates_transformed =
        *parsed_update_input | std::views::transform([](std::vector<uint8_t> const & update) {
            return aoc::day_5::page_update{std::move(update)};
        }) |
        aoc::ranges::to<std::vector<aoc::day_5::page_update>>;

    auto validator = aoc::day_5::rules_validator(*std::move(page_ordering_rules));

    auto [sum_valid, sum_invalid] = aoc::ranges::fold_left(
        updates_transformed, aoc::day_5::result_summary{},
        [&validator](aoc::day_5::result_summary summary_accumulation, aoc::day_5::page_update & update) {
            bool is_valid = validator.validate_and_fix(update);
            uint8_t middle = update.getMiddleElement();
            summary_accumulation.add(middle, is_valid);
            return summary_accumulation;
        });

    std::println("The sum of valid middle elements is: {:#}", sum_valid);
    std::println("The sum of invalid middle elements is: {:#}", sum_invalid);

    return 0;
}
