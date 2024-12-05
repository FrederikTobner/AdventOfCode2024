#pragma once

#include <cstdint>
#include <optional>
#include <stdexcept>
#include <vector>

/*!
 * @namespace aoc::day_5
 * @brief Namespace containing solutions for Advent of Code 2024 Day 5
 *        Implementation focuses on page ordering and validation systems
 */
namespace aoc::day_5 {

/*!
 * @struct page_update
 * @brief Represents a collection of page values that can be updated
 */
struct page_update {
    //! The collection of page values to be updated
    std::vector<uint8_t> updateValues;

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

  private:
    void validate_size() const {
        if (updateValues.size() % 2 == 0) {
            throw std::invalid_argument("Update values must have an odd number of elements");
        }
    }

  public:
    /*!
     * @brief Gets the middle element from the update values
     * @return The middle element
     */
    [[nodiscard]] uint8_t getMiddleElement() const;
};
} // namespace aoc::day_5
