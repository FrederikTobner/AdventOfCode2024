#include "../lib/maze.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>


using namespace aoc::day_16;
using ::testing::ElementsAre;

TEST(MazeTest, ParsesEmptyMaze) {
    // Arrange
    std::vector<std::string_view> input = {"...", "...", "..."};

    // Act
    auto maze = parseMaze(input);

    // Assert
    ASSERT_EQ(maze.size(), 3);
    ASSERT_EQ(maze[0].size(), 3);
    EXPECT_THAT(maze[0], ElementsAre(maze_cell::EMPTY, maze_cell::EMPTY, maze_cell::EMPTY));
}

TEST(MazeTest, ParsesMazeWithWalls) {
    // Arrange
    std::vector<std::string_view> input = {"#.#", ".#.", "#.#"};

    // Act
    auto maze = parseMaze(input);

    // Assert
    ASSERT_EQ(maze.size(), 3);
    EXPECT_THAT(maze[0], ElementsAre(maze_cell::WALL, maze_cell::EMPTY, maze_cell::WALL));
    EXPECT_THAT(maze[1], ElementsAre(maze_cell::EMPTY, maze_cell::WALL, maze_cell::EMPTY));
}

TEST(MazeTest, ParsesMazeWithStartAndEnd) {
    // Arrange
    std::vector<std::string_view> input = {"S..", "...", "..E"};

    // Act
    auto maze = parseMaze(input);

    // Assert
    EXPECT_EQ(maze[0][0], maze_cell::START);
    EXPECT_EQ(maze[2][2], maze_cell::END);
}

TEST(MazeTest, ThrowsOnInvalidCharacter) {
    // Arrange
    std::vector<std::string_view> input = {"..X", // Invalid character 'X'
                                           "...", "..."};

    // Act & Assert
    EXPECT_THROW(parseMaze(input), std::invalid_argument);
}

class MazeParameterizedTest
    : public ::testing::TestWithParam<std::tuple<std::vector<std::string_view>, size_t, size_t>> {};

TEST_P(MazeParameterizedTest, ValidatesMazeDimensions) {
    // Arrange
    auto const & [input, expected_rows, expected_cols] = GetParam();

    // Act
    auto maze = parseMaze(input);

    // Assert
    EXPECT_EQ(maze.size(), expected_rows);
    EXPECT_EQ(maze[0].size(), expected_cols);
}

INSTANTIATE_TEST_SUITE_P(MazeSizes, MazeParameterizedTest,
                         ::testing::Values(std::make_tuple(std::vector<std::string_view>{"..."}, 1, 3),
                                           std::make_tuple(std::vector<std::string_view>{"...", "..."}, 2, 3),
                                           std::make_tuple(std::vector<std::string_view>{".....", "....."}, 2, 5)));
