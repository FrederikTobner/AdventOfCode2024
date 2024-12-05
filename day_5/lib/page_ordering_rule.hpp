#pragma once

#include <concepts>
#include <ranges>
#include <vector>

namespace aoc::day_5 {

/*!
 * @brief Concept defining requirements for a container of page numbers
 * @tparam T The container type to check
 */
template <typename T>
concept PageContainer = std::ranges::forward_range<T> && std::same_as<std::ranges::range_value_t<T>, uint8_t>;

/*!
 * @struct page_ordering_rule
 * @brief Represents a rule that defines the required order between two pages
 */
struct page_ordering_rule {
    //! The page that should appear before the post_page
    uint8_t pre_page;
    //! The page that should appear after the pre_page
    uint8_t post_page;

    //! Default comparison operator
    auto operator<=>(page_ordering_rule const &) const = default;

    /*!
     * @brief Checks if the rule is fulfilled in the given page container
     * @tparam T Container type that satisfies PageContainer concept
     * @param pages Container of page numbers to check
     * @return true if the rule is fulfilled or pages are not found, false otherwise
     */
    [[nodiscard]] bool isFullfilled(PageContainer auto const & pages) const {
        if (auto [pre_it, post_it] = findPages(pages);
            pre_it != std::ranges::end(pages) && post_it != std::ranges::end(pages)) {
            return pre_it < post_it;
        }
        return true;
    }

    /*!
     * @brief Fixes the page order by swapping pages if they violate the rule
     * @param pages Vector of page numbers to fix
     */
    void fixPage(std::vector<uint8_t> & pages) const;

  private:
    /*!
     * @brief Finds the positions of both pages in the container
     * @tparam T Container type that satisfies PageContainer concept
     * @param pages Container to search in
     * @return Pair of iterators to pre_page and post_page positions
     */
    [[nodiscard]] auto findPages(PageContainer auto const & pages) const {
        return std::pair{std::ranges::find(pages, pre_page), std::ranges::find(pages, post_page)};
    }
};

} // namespace aoc::day_5