#pragma once
#include <cstdint>
#include <utility>

namespace aoc::day_5 {

/*!
 * @class result_summary
 * @brief Maintains running totals of valid and invalid values
 */
struct result_summary {
    uint64_t valid_{0};
    uint64_t invalid_{0};

    result_summary() = default;

    /*!
     * @brief Adds a value to either the valid or invalid total
     * @param value The value to add
     * @param isValid If true, adds to valid total; if false, adds to invalid total
     */
    auto add(uint64_t value, bool isValid) -> void;
};

} // namespace aoc::day_5
