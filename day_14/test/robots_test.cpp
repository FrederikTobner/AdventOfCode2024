#include "../lib/robots.hpp"

#include <gtest/gtest.h>

namespace aoc::day_14::test {

TEST(RobotTest, ParseValidRobot) {
    // Arrange
    auto const input = "p=74,51 v=36,-94";

    // Act
    auto result = parseRobot(input);

    // Assert
    ASSERT_TRUE(result.has_value());
    auto const & robot = *result;
    EXPECT_EQ(robot.position.x, 74);
    EXPECT_EQ(robot.position.y, 51);
    EXPECT_EQ(robot.velocity.x, 36);
    EXPECT_EQ(robot.velocity.y, -94);
}

TEST(RobotTest, ParseInvalidFormat) {
    // Arrange
    auto const input = "invalid_format";

    // Act
    auto result = parseRobot(input);

    // Assert
    ASSERT_FALSE(result.has_value());
}

TEST(RobotTest, ParseMissingVelocity) {
    // Arrange
    auto const input = "p=74,51";

    // Act
    auto result = parseRobot(input);

    // Assert
    ASSERT_FALSE(result.has_value());
}

TEST(RobotTest, UpdatePosition) {
    // Arrange
    robot r{.position = {5, 5}, .velocity = {2, -1}};

    // Act
    r.update(10, 10);

    // Assert
    EXPECT_EQ(r.position.x, 7);
    EXPECT_EQ(r.position.y, 4);
}

TEST(RobotTest, WrapAroundRightEdge) {
    // Arrange
    robot r{.position = {8, 5}, .velocity = {3, 0}};

    // Act
    r.update(10, 10);

    // Assert
    EXPECT_EQ(r.position.x, 1);
    EXPECT_EQ(r.position.y, 5);
}

TEST(RobotTest, WrapAroundLeftEdge) {
    // Arrange
    robot r{.position = {1, 5}, .velocity = {-3, 0}};

    // Act
    r.update(10, 10);

    // Assert
    EXPECT_EQ(r.position.x, 8);
    EXPECT_EQ(r.position.y, 5);
}

TEST(RobotTest, WrapAroundBottomEdge) {
    // Arrange
    robot r{.position = {5, 8}, .velocity = {0, 3}};

    // Act
    r.update(10, 10);

    // Assert
    EXPECT_EQ(r.position.x, 5);
    EXPECT_EQ(r.position.y, 1);
}

TEST(RobotTest, WrapAroundTopEdge) {
    // Arrange
    robot r{.position = {5, 1}, .velocity = {0, -3}};

    // Act
    r.update(10, 10);

    // Assert
    EXPECT_EQ(r.position.x, 5);
    EXPECT_EQ(r.position.y, 8);
}

TEST(RobotTest, ParseNegativeCoordinates) {
    // Arrange
    auto const input = "p=-2,-3 v=-1,4";

    // Act
    auto result = parseRobot(input);

    // Assert
    ASSERT_TRUE(result.has_value());
    auto const & robot = *result;
    EXPECT_EQ(robot.position.x, -2);
    EXPECT_EQ(robot.position.y, -3);
    EXPECT_EQ(robot.velocity.x, -1);
    EXPECT_EQ(robot.velocity.y, 4);
}

} // namespace aoc::day_14::test