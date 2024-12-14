#include "robots.hpp"

namespace aoc::day_14 {

auto robot::update(size_t x_size, size_t y_size) -> void {
    position += velocity;
    if (position.x < 0) {
        position.x += x_size;
    }
    if (position.y < 0) {
        position.y += y_size;
    }
    if (position.x >= x_size) {
        position.x -= x_size;
    }
    if (position.y >= y_size) {
        position.y -= y_size;
    }
}

struct robot_components {
    std::string_view position;
    std::string_view velocity;
};

[[nodiscard]] auto split_robot_components(std::string_view line) -> std::expected<robot_components, std::error_code> {
    constexpr auto pos_prefix = std::string_view{"p="};
    constexpr auto vel_prefix = std::string_view{" v="};

    if (!line.starts_with(pos_prefix)) {
        return std::unexpected(std::make_error_code(std::errc::invalid_argument));
    }

    auto vel_start = line.find(vel_prefix);
    if (vel_start == std::string_view::npos) {
        return std::unexpected(std::make_error_code(std::errc::invalid_argument));
    }

    return robot_components{.position = line.substr(pos_prefix.length(), vel_start - pos_prefix.length()),
                            .velocity = line.substr(vel_start + vel_prefix.length())};
}

auto parseCoordinate(std::string_view line) -> std::expected<aoc::math::vector_2d<int16_t>, std::error_code> {
    auto delimiter = line.find(',');
    auto x = aoc::parser::rules::parse_number<int16_t>(line.substr(0, delimiter));
    auto y = aoc::parser::rules::parse_number<int16_t>(line.substr(delimiter + 1));
    if (!x || !y) {
        return std::unexpected(x.error() ? x.error() : y.error());
    }
    return aoc::math::vector_2d<int16_t>{*x, *y};
}

auto parseRobot(std::string_view line) -> std::expected<robot, std::error_code> {
    auto components = split_robot_components(line);
    if (!components) {
        return std::unexpected(components.error());
    }

    auto position = parseCoordinate(components->position);
    if (!position) {
        return std::unexpected(position.error());
    }

    auto velocity = parseCoordinate(components->velocity);
    if (!velocity) {
        return std::unexpected(velocity.error());
    }

    return robot{.position = *position, .velocity = *velocity};
}

} // namespace aoc::day_14