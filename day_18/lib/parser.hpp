#pragma once

#include <cstdint>
#include <execution>
#include <expected>
#include <string_view>
#include <system_error>
#include <vector>

#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/line_splitter.hpp"
#include "../../shared/src/parsing_rules.hpp"

namespace aoc::day_18 {

auto parseInput(std::string_view filename) -> std::expected<std::vector<std::vector<int16_t>>, std::error_code> {
    auto input = aoc::file_operations::read(filename);
    if (!input) {
        return std::unexpected(input.error());
    }

    return aoc::splitter::linebased::split<int16_t, std::vector>(*input, aoc::parser::rules::parse_number<int16_t>,
                                                                 std::execution::seq, ',');
}

} // namespace aoc::day_18