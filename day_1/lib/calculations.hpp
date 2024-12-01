/**
 * @file calculations.hpp
 * @brief Numerical calculations interface
 * @details Declares functions for performing various numerical calculations
 * on sets of numbers, including distance and similarity calculations.
 */

#pragma once
#include <cstdint>
#include <set>

/**
 * @brief Calculates the total distance between corresponding elements in two lists
 * @param leftList First multiset of numbers
 * @param rightList Second multiset of numbers
 * @return Sum of absolute differences between corresponding elements
 */
[[nodiscard]] auto calculateTotalDistance(std::multiset<int64_t> const & leftList,
                                          std::multiset<int64_t> const & rightList) -> uint64_t;

/**
 * @brief Calculates a similarity score between two lists of numbers
 * @param leftList First multiset of numbers
 * @param rightList Second multiset of numbers
 * @return Similarity score based on common elements
 */
[[nodiscard]] auto calculateSimilarityScore(std::multiset<int64_t> const & leftList,
                                            std::multiset<int64_t> const & rightList) -> uint64_t;