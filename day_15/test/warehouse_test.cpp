#include "../lib/warehouse.hpp"
#include <gtest/gtest.h>
#include <vector>

using namespace aoc::day_15;
using Direction = aoc::math::Direction;

class WarehouseTest : public ::testing::Test {
  protected:
    void SetUp() override {
        // Empty setup for now
    }
};

TEST_F(WarehouseTest, RobotSimpleMove) {
    // Arrange
    std::vector<std::vector<cell_type>> warehouse = {{cell_type::WALL, cell_type::WALL, cell_type::WALL},
                                                     {cell_type::WALL, cell_type::ROBOT, cell_type::WALL},
                                                     {cell_type::WALL, cell_type::EMPTY, cell_type::WALL},
                                                     {cell_type::WALL, cell_type::WALL, cell_type::WALL}};
    std::vector<Direction> moves = {Direction::DOWN};

    // Act
    executeMoves(warehouse, moves);

    // Assert
    EXPECT_EQ(warehouse[1][1], cell_type::EMPTY);
    EXPECT_EQ(warehouse[2][1], cell_type::ROBOT);
}

TEST_F(WarehouseTest, RobotBlockedByWall) {
    // Arrange
    std::vector<std::vector<cell_type>> warehouse = {{cell_type::WALL, cell_type::WALL, cell_type::WALL},
                                                     {cell_type::WALL, cell_type::ROBOT, cell_type::WALL},
                                                     {cell_type::WALL, cell_type::WALL, cell_type::WALL}};
    std::vector<Direction> moves = {Direction::DOWN};

    // Act
    executeMoves(warehouse, moves);

    // Assert
    EXPECT_EQ(warehouse[1][1], cell_type::ROBOT);
}

TEST_F(WarehouseTest, PushSingleBox) {
    // Arrange
    std::vector<std::vector<cell_type>> warehouse = {
        {cell_type::WALL, cell_type::WALL, cell_type::WALL, cell_type::WALL},
        {cell_type::WALL, cell_type::ROBOT, cell_type::BOX, cell_type::EMPTY},
        {cell_type::WALL, cell_type::EMPTY, cell_type::EMPTY, cell_type::WALL},
        {cell_type::WALL, cell_type::WALL, cell_type::WALL, cell_type::WALL}};
    std::vector<Direction> moves = {Direction::RIGHT};

    // Act
    executeMoves(warehouse, moves);

    // Assert
    EXPECT_EQ(warehouse[1][1], cell_type::EMPTY);
    EXPECT_EQ(warehouse[1][2], cell_type::ROBOT);
    EXPECT_EQ(warehouse[1][3], cell_type::BOX);
}

TEST_F(WarehouseTest, PushBoxPair) {
    // Arrange
    std::vector<std::vector<cell_type>> warehouse = {
        {cell_type::WALL, cell_type::WALL, cell_type::WALL, cell_type::WALL, cell_type::WALL},
        {cell_type::WALL, cell_type::ROBOT, cell_type::BOX_PART_LEFT, cell_type::BOX_PART_RIGHT, cell_type::EMPTY},
        {cell_type::WALL, cell_type::EMPTY, cell_type::EMPTY, cell_type::EMPTY, cell_type::WALL},
        {cell_type::WALL, cell_type::WALL, cell_type::WALL, cell_type::WALL, cell_type::WALL}};
    std::vector<Direction> moves = {Direction::RIGHT};

    // Act
    executeMoves(warehouse, moves);

    // Assert
    EXPECT_EQ(warehouse[1][1], cell_type::EMPTY);
    EXPECT_EQ(warehouse[1][2], cell_type::ROBOT);
    EXPECT_EQ(warehouse[1][3], cell_type::BOX_PART_LEFT);
    EXPECT_EQ(warehouse[1][4], cell_type::BOX_PART_RIGHT);
}

class WarehouseDirectionTest : public testing::TestWithParam<std::pair<Direction, std::pair<int, int>>> {
  protected:
    std::vector<std::vector<cell_type>> createBasicWarehouse() {
        return std::vector<std::vector<cell_type>>(5, std::vector<cell_type>(5, cell_type::EMPTY));
    }
};

TEST_P(WarehouseDirectionTest, RobotMovesInAllDirections) {
    // Arrange
    auto warehouse = createBasicWarehouse();
    auto [direction, expected] = GetParam();
    warehouse[2][2] = cell_type::ROBOT;

    // Act
    executeMoves(warehouse, {direction});

    // Assert
    EXPECT_EQ(warehouse[2][2], cell_type::EMPTY);
    EXPECT_EQ(warehouse[2 + expected.second][2 + expected.first], cell_type::ROBOT);
}

INSTANTIATE_TEST_SUITE_P(DirectionTests, WarehouseDirectionTest,
                         testing::Values(std::make_pair(Direction::UP, std::make_pair(0, -1)),
                                         std::make_pair(Direction::DOWN, std::make_pair(0, 1)),
                                         std::make_pair(Direction::LEFT, std::make_pair(-1, 0)),
                                         std::make_pair(Direction::RIGHT, std::make_pair(1, 0))));