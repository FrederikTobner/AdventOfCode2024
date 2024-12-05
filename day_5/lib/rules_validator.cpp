
#include "rules_validator.hpp"

namespace aoc::day_5 {

rules_validator::rules_validator(std::vector<page_ordering_rule> rules) : rules(std::move(rules)) {
}

bool rules_validator::validate_and_fix(page_update & update) {
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

} // namespace aoc::day_5