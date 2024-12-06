#include "rules_validator.hpp"

namespace aoc::day_5 {

rules_validator::rules_validator(std::vector<page_ordering_rule> rules) : rules(std::move(rules)) {
}

auto rules_validator::validate_and_fix(page_update & update) -> bool {
    bool made_changes = false;

restart:
    for (auto const & rule : rules) {
        if (auto match = update.find_rule_pages(rule)) {
            if (match->needs_swap()) {
                std::iter_swap(match->pre_it, match->post_it);
                made_changes = true;
                goto restart;
            }
        }
    }

    return !made_changes;
}

} // namespace aoc::day_5