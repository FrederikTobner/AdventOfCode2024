#pragma once

#include <expected>
#include <string_view>
#include <system_error>
#include <utility>
#include <vector>

#include "../../shared/src/ranges_compatibility_layer.hpp"
#include "page_ordering_rule.hpp"

namespace aoc::day_5 {

/*!
 * @brief Splits input into two parts separated by double newline
 * @param input The getRawValue input string to parse
 * @return A pair of string_views representing the two parts, or an error if parsing fails
 */
auto parse_input(std::string_view input)
    -> std::expected<std::pair<std::string_view, std::string_view>, std::error_code>;

/*!
 * @brief Parses a string of rules into a vector of page_ordering_rule objects
 * @param rules_str String containing the rules in the format "number|number" per line
 * @return Vector of parsed rules, or an error if parsing fails
 */
auto parse_rules(std::string_view rules_str)
    -> std::expected<std::vector<aoc::day_5::page_ordering_rule>, std::error_code>;

} // namespace aoc::day_5