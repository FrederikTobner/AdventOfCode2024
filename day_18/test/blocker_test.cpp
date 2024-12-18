#include "../lib/blocker.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace aoc::day_18;

class BlockerTest : public ::testing::Test {
  protected:
    void SetUp() override {
        // Simple maze setup where coordinate at index 5 is critical
        base_coordinates = {
            {1, 0},
            {1, 1},
            {0, 2}, // Critical wall that blocks the path
            {3, 3}, // Additional non-critical wall
        };
    }

    std::vector<std::vector<int16_t>> base_coordinates;
};

TEST_F(BlockerTest, FindsCriticalWallInSimpleMaze) {
    // Arrange - using base_coordinates from fixture

    // Act
    auto [critical_x, critical_y] = findCriticalWall(base_coordinates, 0);

    // Assert
    EXPECT_EQ(critical_x, 0);
    EXPECT_EQ(critical_y, 2);
}

TEST_F(BlockerTest, ValidatePathWorksForBlockedMaze) {
    // Arrange
    auto maze = buildMaze(base_coordinates, base_coordinates.size());

    // Act
    bool is_blocked = validatePath(maze, scoringFun);

    // Assert
    EXPECT_TRUE(is_blocked);
}