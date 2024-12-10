#include "trails.hpp"

#include "../../shared/src/vector2d.hpp"

namespace aoc::day_10 {

#define TRAIL_END   9
#define TRAIL_START 0

bool isTrailEnd(uint8_t value) {
    return value == TRAIL_END;
}

bool isTrailStart(uint8_t value) {
    return value == TRAIL_START;
}

size_t trails::calculateUniquePaths() const {
    size_t uniquePathsCounter = 0;
    for (auto const & root_node : nodes) {
        std::unordered_set<aoc::math::vector_2d<uint8_t>> uniqueEndPositions;
        root_node.executeOnFullFillingCondition(
            [](aoc::math::vector_3d<uint8_t> const & point) { return isTrailEnd(point.z); },
            [&uniqueEndPositions](aoc::math::vector_3d<uint8_t> const & point) {
                uniqueEndPositions.insert({point.x, point.y});
            });
        uniquePathsCounter += uniqueEndPositions.size();
    }
    return uniquePathsCounter;
}

size_t trails::calculateRating() const {
    size_t ratingCounter = 0;
    for (auto const & root_node : nodes) {
        ratingCounter += root_node.countFullFillingCondition(
            [](aoc::math::vector_3d<uint8_t> const & point) { return isTrailEnd(point.z); });
    }
    return ratingCounter;
}

} // namespace aoc::day_10