#pragma once

#include "page_ordering_rule.hpp"
#include "page_update.hpp"
#include <algorithm>
#include <ranges>

namespace aoc::day_5 {

/*!
 * @class rules_validator
 * @brief Validates and fixes page ordering rules on a set of pages
 */
class rules_validator {
    std::vector<page_ordering_rule> rules;

  public:
    /*!
     * @brief Constructs a rules validator with a set of ordering rules
     * @param rules Vector of page ordering rules to validate against
     */
    explicit rules_validator(std::vector<page_ordering_rule> rules);

    /*!
     * @brief Validates and fixes page ordering according to the rules
     * @param update The page update to validate and potentially modify
     * @return true if no changes were needed (valid ordering), false if changes were made
     * @note This method will continue fixing the ordering until all rules are satisfied
     */
    [[nodiscard]] auto validate_and_fix(page_update & update) -> bool;
};
} // namespace aoc::day_5