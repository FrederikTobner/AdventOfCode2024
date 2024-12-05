
#include "page_ordering_rule.hpp"
#include <algorithm>

namespace aoc::day_5 {

void page_ordering_rule::fixPage(std::vector<uint8_t> & pages) const {
    auto pre_it = std::ranges::find(pages, pre_page);
    auto post_it = std::ranges::find(pages, post_page);

    if (pre_it != pages.end() && post_it != pages.end() && post_it < pre_it) {
        std::iter_swap(pre_it, post_it);
    }
}

} // namespace aoc::day_5