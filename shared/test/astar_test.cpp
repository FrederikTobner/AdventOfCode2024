#include "../src/astar.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace aoc::path_finding;
using ::testing::ElementsAre;

int scoreFunction(Node const & a, Node const & b) {
    return a.direction == b.direction ? 1 : 1001;
}

TEST(AStarTest, FindsSimplePath) {
    // Arrange
    std::vector<std::vector<maze_cell>> maze = {{maze_cell::START, maze_cell::EMPTY, maze_cell::END},
                                                {maze_cell::EMPTY, maze_cell::EMPTY, maze_cell::EMPTY},
                                                {maze_cell::EMPTY, maze_cell::EMPTY, maze_cell::EMPTY}};
    MazeSolver solver(maze, scoreFunction);

    // Act
    auto result = solver.findPath();

    // Assert
    ASSERT_GT(result.path.size(), 0);
    EXPECT_EQ(result.path.front().pos, (aoc::math::vector_2d<int16_t>{0, 0}));
    EXPECT_EQ(result.path.back().pos, (aoc::math::vector_2d<int16_t>{2, 0}));
}

TEST(AStarTest, HandlesBlockedPath) {
    // Arrange
    std::vector<std::vector<maze_cell>> maze = {{maze_cell::START, maze_cell::WALL, maze_cell::END},
                                                {maze_cell::WALL, maze_cell::WALL, maze_cell::WALL},
                                                {maze_cell::EMPTY, maze_cell::EMPTY, maze_cell::EMPTY}};
    MazeSolver solver(maze, scoreFunction);

    // Act
    auto result = solver.findPath();

    // Assert
    EXPECT_EQ(result.cost, -1);
    EXPECT_TRUE(result.path.empty());
}

TEST(AStarTest, FindsPathAroundObstacles) {
    // Arrange
    std::vector<std::vector<maze_cell>> maze = {{maze_cell::START, maze_cell::WALL, maze_cell::END},
                                                {maze_cell::EMPTY, maze_cell::WALL, maze_cell::EMPTY},
                                                {maze_cell::EMPTY, maze_cell::EMPTY, maze_cell::EMPTY}};
    MazeSolver solver(maze, scoreFunction);

    // Act
    auto result = solver.findPath();

    // Assert
    ASSERT_GT(result.path.size(), 0);
    EXPECT_EQ(result.path.front().pos, (aoc::math::vector_2d<int16_t>{0, 0}));
    EXPECT_EQ(result.path.back().pos, (aoc::math::vector_2d<int16_t>{2, 0}));
}

TEST(AStarTest, FindsMultiplePaths) {
    // Arrange
    std::vector<std::vector<maze_cell>> maze = {{maze_cell::START, maze_cell::EMPTY, maze_cell::END},
                                                {maze_cell::EMPTY, maze_cell::EMPTY, maze_cell::EMPTY},
                                                {maze_cell::EMPTY, maze_cell::EMPTY, maze_cell::EMPTY}};
    MazeSolver solver(maze, scoreFunction);

    // Act
    auto results = solver.findPaths();

    // Assert
    EXPECT_GT(results.size(), 0);
    for (auto const & path : results) {
        EXPECT_GT(path.path.size(), 0);
        EXPECT_EQ(path.path.front().pos, (aoc::math::vector_2d<int16_t>{0, 0}));
        EXPECT_EQ(path.path.back().pos, (aoc::math::vector_2d<int16_t>{2, 0}));
    }
}

class DirectionCostTest : public ::testing::TestWithParam<std::pair<aoc::math::Direction, aoc::math::Direction>> {};

TEST_P(DirectionCostTest, DirectionChangeCosts) {
    // Arrange
    std::vector<std::vector<maze_cell>> maze = {{maze_cell::START, maze_cell::EMPTY, maze_cell::END},
                                                {maze_cell::EMPTY, maze_cell::EMPTY, maze_cell::EMPTY}};
    MazeSolver solver(maze, scoreFunction);
    auto [start_dir, end_dir] = GetParam();

    // Act
    auto result = solver.findPath();

    // Assert
    EXPECT_GT(result.cost, 0);
}

INSTANTIATE_TEST_SUITE_P(DirectionTests, DirectionCostTest,
                         ::testing::Values(std::make_pair(aoc::math::Direction::RIGHT, aoc::math::Direction::DOWN),
                                           std::make_pair(aoc::math::Direction::DOWN, aoc::math::Direction::RIGHT),
                                           std::make_pair(aoc::math::Direction::RIGHT, aoc::math::Direction::RIGHT)));