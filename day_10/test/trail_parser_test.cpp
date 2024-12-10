#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../lib/trail_parser.hpp"

using namespace aoc::day_10;
using namespace aoc::math;

class TrailParserTest : public ::testing::Test {
  protected:
    std::vector<std::vector<uint8_t>> createSimpleMap() {
        return {{0, 1, 2, 3}, {1, 2, 3, 4}, {2, 3, 4, 5}};
    }
    auto getResults(trails const & result) -> std::vector<aoc::tree::tree_node<topography>> {
        return result.nodes;
    }

    void assertTreeStructures(std::vector<aoc::tree::tree_node<topography>> const & actualStructure,
                              std::vector<std::pair<uint8_t, uint8_t>> const & expectedConnections) {
        for (size_t i = 0; i < actualStructure.size(); i++) {
            auto node = actualStructure[i];
            EXPECT_EQ(node.value.value, expectedConnections[i].first);
            for (size_t j = 0; j < node.children.size(); j++) {
                auto child = node.children[j];
                EXPECT_EQ(child.value.value, expectedConnections[i].second);
            }
        }
    }
};

class DirectionTest : public testing::TestWithParam<std::tuple<Direction, vector_2d<uint8_t>>> {};

TEST_P(DirectionTest, CalculateNewPositionParameterized) {
    // Arrange
    vector_2d<uint8_t> start_pos{1, 1};
    auto [direction, expected] = GetParam();

    // Act
    auto result = calculateNewPosition(start_pos, direction);

    // Assert
    EXPECT_EQ(result, expected);
}

INSTANTIATE_TEST_SUITE_P(Directions, DirectionTest,
                         testing::Values(std::make_tuple(Direction::UP, vector_2d<uint8_t>(0, 1)),
                                         std::make_tuple(Direction::RIGHT, vector_2d<uint8_t>(1, 2)),
                                         std::make_tuple(Direction::DOWN, vector_2d<uint8_t>(2, 1)),
                                         std::make_tuple(Direction::LEFT, vector_2d<uint8_t>(1, 0))));

class PositionValidationTest : public testing::TestWithParam<std::tuple<vector_2d<uint8_t>, bool>> {};

TEST_P(PositionValidationTest, IsValidPositionParameterized) {
    // Arrange
    std::vector<std::vector<uint8_t>> map = {{0, 1, 2, 9}, {0, 1, 9, 0}, {9, 2, 3, 9}};
    auto [position, expected] = GetParam();

    // Act
    auto result = isValidPosition(position, map);

    // Assert
    EXPECT_EQ(result, expected);
}

INSTANTIATE_TEST_SUITE_P(Positions, PositionValidationTest,
                         testing::Values(std::make_tuple(vector_2d<uint8_t>(0, 0), true),
                                         std::make_tuple(vector_2d<uint8_t>(2, 3), true),
                                         std::make_tuple(vector_2d<uint8_t>(3, 0), false),
                                         std::make_tuple(vector_2d<uint8_t>(0, 4), false)));

TEST_F(TrailParserTest, ConvertToTrailsBasicTest) {
    // Arrange
    std::vector<std::vector<uint8_t>> simpleMap = {{0, 1, 2, 3}, {1, 2, 3, 9}};
    auto expectedConnections =
        std::vector<std::pair<uint8_t, uint8_t>>{{0, 1}, {1, 2}, {2, 3}, {3, 9}, {1, 2}, {2, 3}, {3, 9}};

    // Act
    trails result = convertToTrails(simpleMap);

    // Assert
    assertTreeStructures(getResults(result), expectedConnections);
}

TEST_F(TrailParserTest, ConvertToTrailsComplexTest) {
    // Arrange
    auto map = createSimpleMap();
    auto expectedConnections = std::vector<std::pair<uint8_t, uint8_t>>{{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {1, 2},
                                                                        {2, 3}, {3, 4}, {4, 5}, {2, 3}, {3, 4}, {4, 5}};
    // Act
    trails result = convertToTrails(map);

    // Assert
    assertTreeStructures(getResults(result), expectedConnections);
}

TEST_F(TrailParserTest, InvalidDirectionTest) {
    // Arrange
    vector_2d<uint8_t> pos{1, 1};

    // Act & Assert
    EXPECT_THROW(calculateNewPosition(pos, static_cast<Direction>(99)), std::invalid_argument);
}

TEST_F(TrailParserTest, MultipleStartPointsTest) {
    // Arrange
    std::vector<std::vector<uint8_t>> multiStartMap = {{0, 1}, {0, 1}};
    auto expectedConnections = std::vector<std::pair<uint8_t, uint8_t>>{{0, 1}, {0, 1}};

    // Act
    trails result = convertToTrails(multiStartMap);

    // Assert
    assertTreeStructures(getResults(result), expectedConnections);
}