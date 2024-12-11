#pragma once

#include "parser.hpp"

#include "../../shared/src/line_splitter.hpp"
#include "../../shared/src/parsing_rules.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"

namespace aoc::day_11 {

auto parseNumbers(std::string_view input) -> std::expected<std::vector<size_t>, std::error_code> {
    auto parsed_numbers =
        aoc::splitter::linebased::split<size_t, std::vector>(input, aoc::parser::rules::parse_number<size_t>, ' ');

    if (!parsed_numbers) {
        return std::unexpected(std::make_error_code(ParsingError::GenericError));
    }
    if (parsed_numbers->empty()) {
        return std::unexpected(std::make_error_code(ParsingError::NoInput));
    }
    if (parsed_numbers->size() > 1) {
        return std::unexpected(std::make_error_code(ParsingError::TooMuchInput));
    }

    auto numbers = (*parsed_numbers)[0];
    return numbers;
}

} // namespace aoc::day_11