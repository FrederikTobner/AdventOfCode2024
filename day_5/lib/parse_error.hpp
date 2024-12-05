
#pragma once

#include <string>
#include <system_error>

namespace aoc::day_5 {

enum class parse_error {
    invalid_format,
    split_error
};

} // namespace aoc::day_5