#pragma once

#include "page_ordering_rule.hpp"
#include "page_update.hpp"
#include <algorithm>
#include <ranges>

namespace aoc::day_5 {
class rules_validator {
    std::vector<page_ordering_rule> rules;

  public:
    explicit rules_validator(std::vector<page_ordering_rule> rules) : rules(std::move(rules)) {
    }

    [[nodiscard]] bool validate_and_fix(page_update & update) {
        bool made_changes = false;

    restart:
        for (auto const & rule : rules) {
            if (!rule.isFullfilled(update.updateValues)) {
                rule.fixPage(update.updateValues);
                made_changes = true;
                goto restart;
            }
        }

        return !made_changes;
    }
};
} // namespace aoc::day_5