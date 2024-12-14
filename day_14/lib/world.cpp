#include "world.hpp"

namespace aoc::day_14 {

world::world(std::vector<robot> robots, size_t x_size, size_t y_size)
    : robots(std::move(robots)), x_size(x_size), y_size(y_size) {
}

auto world::update() -> void {
    for (auto & r : robots) {
        r.update(x_size, y_size);
    }
}

[[nodiscard]] auto world::isInTopLeft(robot const & r) const -> bool {
    return r.position.x < x_size / 2 && r.position.y < y_size / 2;
}

[[nodiscard]] auto world::isInTopRight(robot const & r) const -> bool {
    return r.position.x >= x_size / 2 + 1 && r.position.y < y_size / 2;
}

[[nodiscard]] auto world::isInBottomLeft(robot const & r) const -> bool {
    return r.position.x < x_size / 2 && r.position.y >= y_size / 2 + 1;
}

[[nodiscard]] auto world::isInBottomRight(robot const & r) const -> bool {
    return r.position.x >= x_size / 2 + 1 && r.position.y >= y_size / 2 + 1;
}

auto world::safetyScore() const -> size_t {
    ptrdiff_t const top_left = std::ranges::count_if(robots, [this](auto const & r) { return isInTopLeft(r); });
    ptrdiff_t const top_right = std::ranges::count_if(robots, [this](auto const & r) { return isInTopRight(r); });
    ptrdiff_t const bottom_left = std::ranges::count_if(robots, [this](auto const & r) { return isInBottomLeft(r); });
    ptrdiff_t const bottom_right = std::ranges::count_if(robots, [this](auto const & r) { return isInBottomRight(r); });

    return top_left * top_right * bottom_left * bottom_right;
}

[[nodiscard]] auto world::formsChristmasTree() const -> bool {
    auto density = std::vector<size_t>(x_size * y_size, 0);

    for (auto const & r : robots) {
        density[r.position.y * x_size + r.position.x]++;
    }

    return std::ranges::none_of(density, [](size_t count) { return count > 1; });
}

} // namespace aoc::day_14