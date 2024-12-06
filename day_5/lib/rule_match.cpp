#include "rule_match.hpp"

namespace aoc::day_5 {

auto rule_match::needs_swap() const -> bool {
    return post_it < pre_it;
}

} // namespace aoc::day_5