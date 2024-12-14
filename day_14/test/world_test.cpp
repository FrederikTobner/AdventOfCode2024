#include "../lib/world.hpp"

#include <gtest/gtest.h>

namespace aoc::day_14::test {

TEST(WorldTest, Construction) {
    // Arrange
    std::vector<robot> robots = {robot{{0, 0}, {1, 1}}, robot{{5, 5}, {-1, -1}}};

    // Act
    world w(robots, 10, 10);

    // Assert
    EXPECT_EQ(w.safetyScore(), 0); // All robots in top-left quadrant initially
}

TEST(WorldTest, SafetyScore) {
    // Arrange
    std::vector<robot> robots = {
        robot{{2, 2}, {0, 0}}, // top-left
        robot{{7, 2}, {0, 0}}, // top-right
        robot{{2, 7}, {0, 0}}, // bottom-left
        robot{{7, 7}, {0, 0}}  // bottom-right
    };

    // Act
    world w(robots, 10, 10);
    auto score = w.safetyScore();

    // Assert
    EXPECT_EQ(score, 1); // 1 robot in each quadrant = 1*1*1*1
}

TEST(WorldTest, Update) {
    // Arrange
    std::vector<robot> robots = {robot{{0, 0}, {1, 1}}};
    world w(robots, 10, 10);

    // Act
    w.update();

    // Assert
    EXPECT_EQ(w.safetyScore(), 0); // Robot should have moved to (1,1)
}

TEST(WorldTest, ChristmasTreeFormationWithoutOverlap) {
    // Arrange
    std::vector<robot> robots = {robot{{1, 1}, {0, 0}}, robot{{3, 3}, {0, 0}}, robot{{5, 5}, {0, 0}}};
    world w(robots, 10, 10);

    // Act
    auto result = w.formsChristmasTree();

    // Assert
    EXPECT_TRUE(result);
}

TEST(WorldTest, ChristmasTreeFormationWithOverlap) {
    // Arrange
    std::vector<robot> robots = {robot{{1, 1}, {0, 0}}, robot{{1, 1}, {0, 0}}, // Same position as first robot
                                 robot{{5, 5}, {0, 0}}};
    world w(robots, 10, 10);

    // Act
    auto result = w.formsChristmasTree();

    // Assert
    EXPECT_FALSE(result);
}

TEST(WorldTest, SafetyScoreWithMultipleRobotsPerQuadrant) {
    // Arrange
    std::vector<robot> robots = {
        robot{{2, 2}, {0, 0}}, // top-left
        robot{{1, 1}, {0, 0}}, // top-left
        robot{{7, 2}, {0, 0}}, // top-right
        robot{{8, 1}, {0, 0}}, // top-right
        robot{{2, 7}, {0, 0}}, // bottom-left
        robot{{7, 7}, {0, 0}}  // bottom-right
    };
    world w(robots, 10, 10);

    // Act
    auto score = w.safetyScore();

    // Assert
    EXPECT_EQ(score, 4); // 2*2*1*1 = 4
}

} // namespace aoc::day_14::test