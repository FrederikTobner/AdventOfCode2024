
#pragma once
#include <ranges>
#include <vector>

namespace compat {
template <typename Container, typename Range> [[nodiscard]] auto to_container(Range && rng) -> Container {
    Container result;
    for (auto && element : rng) {
        result.insert(result.end(), std::forward<decltype(element)>(element));
    }
    return result;
}

template <typename Range> [[nodiscard]] auto to_vector(Range && rng) {
    return to_container<std::vector<std::ranges::range_value_t<Range>>>(std::forward<Range>(rng));
}
} // namespace compat