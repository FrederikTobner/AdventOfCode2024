#pragma once

#include <cstdint>
#include <span>
#include <vector>

namespace safety_check {

/**
 * @brief Checks if a sequence of numbers follows safety rules
 * @details The rules are:
 *          1. Adjacent numbers must not be equal
 *          2. Difference between adjacent numbers must not exceed 3
 *          3. No local maxima or minima are allowed in sequences of 3 numbers
 * @param input Span of numbers to check
 * @return true if the sequence follows all safety rules, false otherwise
 */
bool isSafe(std::span<uint8_t const> input);

/**
 * @brief Checks if sequence can be made safe by removing one number
 * @details Attempts to remove each number in sequence once and checks if
 *          the resulting sequence is safe according to isSafe rules
 * @param input Span of numbers to check
 * @return true if removing one number can make the sequence safe, false otherwise
 */
bool canBeMadeSafe(std::span<uint8_t const> input);

} // namespace safety_check