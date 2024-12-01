/**
 * @file calculations.cpp
 * @brief Implementation of numerical calculations
 * @details Implements the calculation functions declared in calculations.hpp,
 * utilizing parallel algorithms where possible for better performance.
 */

#include "calculations.hpp"
#include "../../shared/ranges_compatibility_layer.hpp"
#include <algorithm>
#include <execution>
#include <numeric>
#include <ranges>

auto calculateTotalDistance(std::multiset<int64_t> const & leftList, std::multiset<int64_t> const & rightList)
    -> uint64_t {
    auto distances =
        compat::to_vector(std::ranges::zip_view(leftList, rightList) | std::views::transform([](auto pair) {
                              auto [a, b] = pair;
                              return std::abs(a - b);
                          }));

    return std::reduce(std::execution::par, distances.begin(), distances.end(), std::uint64_t{0});
}

auto calculateSimilarityScore(std::multiset<int64_t> const & leftList, std::multiset<int64_t> const & rightList)
    -> uint64_t {
    auto similarities = compat::to_vector(
        leftList | std::views::transform([&rightList](auto const & num) { return rightList.count(num) * num; }));

    return std::reduce(std::execution::par, similarities.begin(), similarities.end(), std::uint64_t{0});
}