#pragma once

#include <algorithm>
#include <cstdint>
#include <optional>
#include <stdexcept>
#include <vector>

#include "page_ordering_rule.hpp"
#include "rule_match.hpp"

/*!
 * @namespace aoc::day_5
 * @brief Namespace containing solutions for Advent of Code 2024 Day 5
 *        Implementation focuses on page ordering and validation systems
 */
namespace aoc::day_5 {

/*!
 * @brief Concept defining requirements for a container of page numbers
 * @tparam T The container type to check
 */
template <typename T>
concept PageContainer = std::ranges::forward_range<T> && std::same_as<std::ranges::range_value_t<T>, uint8_t>;

/**
 * @struct page_update
 * @brief Represents a collection of page values that can be updated
 */
struct page_update {

    page_update() = delete;

    explicit page_update(std::vector<uint8_t> && values) : updateValues(std::move(values)) {
        validate_size();
    }

    explicit page_update(std::vector<uint8_t> const & values) : updateValues(values) {
        validate_size();
    }

    page_update(page_update const &) = delete;
    page_update & operator=(page_update const &) = delete;
    page_update(page_update &&) = default;
    page_update & operator=(page_update &&) = default;

    /// @brief Gets the middle element from the update values
    /// @return The middle element
    [[nodiscard]] auto getMiddleElement() const -> uint8_t;

    /**
     * @brief Checks if the rule is fulfilled in the given page container
     * @tparam T Container type that satisfies PageContainer concept
     * @param pages Container of page numbers to check
     * @return true if the rule is fulfilled or pages are not found, false otherwise
     */
    [[nodiscard]] auto find_rule_pages(page_ordering_rule const & rule) -> std::optional<rule_match> {
        auto pre_it = std::ranges::find(updateValues, rule.pre_page);
        auto post_it = std::ranges::find(updateValues, rule.post_page);

        if (pre_it != std::ranges::end(updateValues) && post_it != std::ranges::end(updateValues)) {
            return rule_match{pre_it, post_it};
        }
        return std::nullopt;
    }

    static auto fix(rule_match const & match) -> void {
        std::iter_swap(match.pre_it, match.post_it);
    }

    /// @brief Gets a const iterator to the beginning of the update values
    /// @return Const iterator to the beginning
    [[nodiscard]] auto cbegin() const -> std::vector<uint8_t>::const_iterator;

    /// @brief The collection of page values to be updated
  private:
    std::vector<uint8_t> updateValues;

    void validate_size() const {
        if (updateValues.size() % 2 == 0) {
            throw std::invalid_argument("Update values must have an odd number of elements");
        }
    }
};
} // namespace aoc::day_5
