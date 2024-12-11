#include "trails.hpp"

#include <algorithm>
#include <ranges>

#include "../../shared/src/vector2d.hpp"

namespace aoc::day_10 {

#define TRAIL_END   9
#define TRAIL_START 0

auto isTrailEnd(uint8_t const & value) -> bool {
    return value == TRAIL_END;
}

auto isTrailStart(uint8_t const & value) -> bool {
    return value == TRAIL_START;
}

auto trails::calculateUniquePaths() const -> size_t {
    return std::ranges::fold_left(nodes, size_t{0}, [](size_t acc, auto const & root_node) {
        std::unordered_set<aoc::math::vector_2d<uint8_t>> uniqueEndPositions;
        root_node.executeIf([](aoc::math::vector_3d<uint8_t> const & point) { return isTrailEnd(point.z); },
                            [&uniqueEndPositions](aoc::math::vector_3d<uint8_t> const & point) {
                                uniqueEndPositions.insert({point.x, point.y});
                            });
        return acc + uniqueEndPositions.size();
    });
}

auto trails::calculateRating() const -> size_t {
    return std::ranges::fold_left(nodes, size_t{0}, [](size_t acc, auto const & root_node) {
        size_t rating = 0;
        root_node.executeIf([](aoc::math::vector_3d<uint8_t> const & point) { return isTrailEnd(point.z); },
                            [&rating](aoc::math::vector_3d<uint8_t> const & point) { rating++; });
        return acc + rating;
    });
}

} // namespace aoc::day_10