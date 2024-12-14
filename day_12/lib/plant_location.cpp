#include "plant_location.hpp"

#include <algorithm>
#include <expected>
#include <map>
#include <ranges>
#include <set>
#include <string>
#include <string_view>
#include <system_error>
#include <unordered_map>

#include "../../shared/src/ranges_compatibility_layer.hpp"

#include "direction.hpp"

namespace aoc::day_12 {

static auto countBorderLines(std::unordered_set<aoc::math::vector_2d<int16_t>> const & locations) -> size_t;

auto splitIntoConnectedLocations(std::unordered_set<aoc::math::vector_2d<int16_t>> const & locations)
    -> std::vector<std::unordered_set<aoc::math::vector_2d<int16_t>>> {
    std::vector<std::unordered_set<aoc::math::vector_2d<int16_t>>> result;
    for (auto const & location : locations) {
        bool found = false;
        for (auto & group : result) {
            if (std::ranges::any_of(group, [&location](auto const & groupLocation) {
                    return std::abs(location.x - groupLocation.x) + std::abs(location.y - groupLocation.y) == 1;
                })) {
                group.insert(location);
                found = true;
                break;
            }
        }
        if (!found) {
            result.push_back({location});
        }
    }

    bool changed = true;
    while (changed) {
        changed = false;
        for (size_t i = 0; i < result.size(); ++i) {
            for (size_t j = i + 1; j < result.size(); ++j) {
                if (std::ranges::any_of(result[i], [&result, j](auto const & location) {
                        return std::ranges::any_of(result[j], [&location](auto const & otherLocation) {
                            return std::abs(location.x - otherLocation.x) + std::abs(location.y - otherLocation.y) == 1;
                        });
                    })) {
                    std::ranges::copy(result[j], std::inserter(result[i], result[i].end()));
                    result.erase(result.begin() + j);
                    changed = true;
                    break;
                }
            }
            if (changed) {
                break;
            }
        }
    }

    return result;
}

auto calculateFencePrice(std::unordered_set<aoc::math::vector_2d<int16_t>> const & locations) -> size_t {
    size_t fenceElementCount = 0;
    auto directions = getDirections();
    for (auto const & location : locations) {
        for (auto const & direction : directions) {
            if (!locations.contains(location + getDirectionVector(direction))) {
                ++fenceElementCount;
            }
        }
    }
    return fenceElementCount * locations.size();
}

auto calculateFencePrice2(std::unordered_set<aoc::math::vector_2d<int16_t>> const & locations) -> size_t {
    auto borderLines = countBorderLines(locations);
    return borderLines * locations.size();
}

static auto countBorderLines(std::unordered_set<aoc::math::vector_2d<int16_t>> const & locations) -> size_t {
    if (locations.empty()) {
        return 0;
    }

    auto [min_x, max_x] = std::ranges::minmax_element(locations, {}, [](auto const & p) { return p.x; });
    auto [min_y, max_y] = std::ranges::minmax_element(locations, {}, [](auto const & p) { return p.y; });

    std::vector<std::vector<bool>> grid(max_x->x - min_x->x + 3, std::vector<bool>(max_y->y - min_y->y + 3, false));

    std::vector<std::vector<bool>> bordersTop(max_x->x - min_x->x + 3,
                                              std::vector<bool>(max_y->y - min_y->y + 3, false));
    std::vector<std::vector<bool>> bordersBottom(max_x->x - min_x->x + 3,
                                                 std::vector<bool>(max_y->y - min_y->y + 3, false));
    std::vector<std::vector<bool>> bordersLeft(max_x->x - min_x->x + 3,
                                               std::vector<bool>(max_y->y - min_y->y + 3, false));

    std::vector<std::vector<bool>> bordersRight(max_x->x - min_x->x + 3,
                                                std::vector<bool>(max_y->y - min_y->y + 3, false));

    for (auto const & pos : locations) {
        grid[pos.x - min_x->x + 1][pos.y - min_y->y + 1] = true;
    }

    auto directions = aoc::day_12::getDirections();

    for (int x = 1; x < grid.size() - 1; ++x) {
        for (int y = 1; y < grid[0].size() - 1; ++y) {
            if (!grid[x][y]) {
                continue;
            }
            for (auto dir : directions) {
                auto vec = getDirectionVector(dir);

                if (!grid[x + vec.x][y + vec.y]) {
                    switch (dir) {
                    case aoc::day_12::Direction::UP:
                        bordersTop[x][y] = true;
                        break;
                    case aoc::day_12::Direction::DOWN:
                        bordersBottom[x][y] = true;
                        break;
                    case aoc::day_12::Direction::LEFT:
                        bordersLeft[x][y] = true;
                        break;
                    case aoc::day_12::Direction::RIGHT:
                        bordersRight[x][y] = true;
                        break;
                    }
                }
            }
        }
    }

    size_t sides = 0;

    // Top border
    for (int x = 1; x < grid.size() - 1; ++x) {
        for (int y = 1; y < grid[0].size() - 1; ++y) {
            if (bordersTop[x][y] && !bordersTop[x - 1][y]) {
                ++sides;
            }
        }
    }

    // Bottom border
    for (int x = 1; x < grid.size() - 1; ++x) {
        for (int y = 1; y < grid[0].size() - 1; ++y) {
            if (bordersBottom[x][y] && !bordersBottom[x - 1][y]) {
                ++sides;
            }
        }
    }

    // Left border
    for (int y = 1; y < grid[0].size() - 1; ++y) {
        for (int x = 1; x < grid.size() - 1; ++x) {
            if (bordersLeft[x][y] && !bordersLeft[x][y - 1]) {
                ++sides;
            }
        }
    }

    // Right border
    for (int y = 1; y < grid[0].size() - 1; ++y) {
        for (int x = 1; x < grid.size() - 1; ++x) {
            if (bordersRight[x][y] && !bordersRight[x][y - 1]) {
                ++sides;
            }
        }
    }

    return sides;
}

} // namespace aoc::day_12
