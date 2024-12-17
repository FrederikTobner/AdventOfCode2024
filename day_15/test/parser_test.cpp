#include "../lib/parser.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace aoc::day_15;
using ::testing::ElementsAre;

TEST(ParserTest, ParsesValidInput) {
    // Arrange
    std::string_view input = "...#...\n.#...#.\n\n>v<^";

    // Act
    auto result = parse_input(input);

    // Assert
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->first, "...#...\n.#...#.");
    EXPECT_EQ(result->second, "\n\n>v<^");
}

TEST(ParserTest, HandlesMissingDelimiter) {
    // Arrange
    std::string_view input = "...#...";

    // Act
    auto result = parse_input(input);

    // Assert
    EXPECT_FALSE(result.has_value());
}

TEST(WarehouseParserTest, ParsesEmptyWarehouse) {
    // Arrange
    std::string_view input = ".....\n.....\n.....";

    // Act
    auto result = parse_warehouse(input);

    // Assert
    ASSERT_EQ(result.size(), 3);
    EXPECT_THAT(result[0],
                ElementsAre(cell_type::EMPTY, cell_type::EMPTY, cell_type::EMPTY, cell_type::EMPTY, cell_type::EMPTY));
}

TEST(WarehouseParserTest, ParsesComplexWarehouse) {
    // Arrange
    std::string_view input = "#.O\n.@.\nO.#";

    // Act
    auto result = parse_warehouse(input);

    // Assert
    ASSERT_EQ(result.size(), 3);
    EXPECT_THAT(result[0], ElementsAre(cell_type::WALL, cell_type::EMPTY, cell_type::BOX));
    EXPECT_THAT(result[1], ElementsAre(cell_type::EMPTY, cell_type::ROBOT, cell_type::EMPTY));
    EXPECT_THAT(result[2], ElementsAre(cell_type::BOX, cell_type::EMPTY, cell_type::WALL));
}

class MovementParserTest
    : public ::testing::TestWithParam<std::pair<std::string_view, std::vector<aoc::math::Direction>>> {};

TEST_P(MovementParserTest, ParsesMovements) {
    // Arrange
    auto const & [input, expected] = GetParam();

    // Act
    auto result = parse_movements(input);

    // Assert
    EXPECT_EQ(result, expected);
}

INSTANTIATE_TEST_SUITE_P(
    MovementTests, MovementParserTest,
    ::testing::Values(std::make_pair("^", std::vector{aoc::math::Direction::UP}),
                      std::make_pair("v", std::vector{aoc::math::Direction::DOWN}),
                      std::make_pair("<>", std::vector{aoc::math::Direction::LEFT, aoc::math::Direction::RIGHT}),
                      std::make_pair("^v<>", std::vector{aoc::math::Direction::UP, aoc::math::Direction::DOWN,
                                                         aoc::math::Direction::LEFT, aoc::math::Direction::RIGHT})));

TEST(MovementParserTest, IgnoresInvalidCharacters) {
    // Arrange
    std::string_view input = "^x>y<z";

    // Act
    auto result = parse_movements(input);

    // Assert
    EXPECT_THAT(result, ElementsAre(aoc::math::Direction::UP, aoc::math::Direction::RIGHT, aoc::math::Direction::LEFT));
}

TEST(MovementParserTest, HandlesEmptyInput) {
    // Arrange
    std::string_view input = "";

    // Act
    auto result = parse_movements(input);

    // Assert
    EXPECT_TRUE(result.empty());
}