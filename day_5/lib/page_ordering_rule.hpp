#pragma once

#include <algorithm>
#include <concepts>
#include <ranges>
#include <vector>

namespace aoc::day_5 {

template <typename T>
concept PageContainer = std::ranges::forward_range<T> && std::same_as<std::ranges::range_value_t<T>, uint8_t>;

struct page_ordering_rule {
    uint8_t pre_page;
    uint8_t post_page;

    // Add comparison operators
    auto operator<=>(page_ordering_rule const &) const = default;

    [[nodiscard]] bool isFullfilled(PageContainer auto const & pages) const {
        if (auto [pre_it, post_it] = findPages(pages);
            pre_it != std::ranges::end(pages) && post_it != std::ranges::end(pages)) {
            return pre_it < post_it;
        }
        return true;
    }

    void fixPage(std::vector<uint8_t> & pages) const {
        // Remove const from iterators when modifying
        auto pre_it = std::ranges::find(pages, pre_page);
        auto post_it = std::ranges::find(pages, post_page);

        if (pre_it != pages.end() && post_it != pages.end() && post_it < pre_it) {
            std::iter_swap(pre_it, post_it);
        }
    }

  private:
    [[nodiscard]] auto findPages(PageContainer auto const & pages) const {
        return std::pair{std::ranges::find(pages, pre_page), std::ranges::find(pages, post_page)};
    }
};

} // namespace aoc::day_5