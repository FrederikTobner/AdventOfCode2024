#include "../src/grid_processor.hpp"

#include <gtest/gtest.h>

class GridProcessorTest : public ::testing::Test {
  protected:
    const std::string normal_input = "abc\ndef\nghi";
    const std::string input_with_cr = "abc\r\ndef\r\nghi";
    const std::string empty_input = "";
    const std::string single_line = "abc";
};

TEST_F(GridProcessorTest, ProcessLinesNormalInput) {
    // Act
    auto result = aoc::grid_processor::processLines(normal_input);

    // Assert
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "abc");
    EXPECT_EQ(result[1], "def");
    EXPECT_EQ(result[2], "ghi");
}

TEST_F(GridProcessorTest, ProcessLinesWithCarriageReturn) {
    // Act
    auto result = aoc::grid_processor::processLines(input_with_cr);

    // Assert
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "abc");
    EXPECT_EQ(result[1], "def");
    EXPECT_EQ(result[2], "ghi");
}

TEST_F(GridProcessorTest, ProcessLinesSingleLine) {
    // Act
    auto result = aoc::grid_processor::processLines(single_line);

    // Assert
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "abc");
}

TEST_F(GridProcessorTest, ValidateGridValid) {
    // Arrange
    std::vector<std::string_view> grid = {"abc", "def", "ghi"};

    // Act
    auto result = aoc::grid_processor::validateGrid(grid);

    // Assert
    EXPECT_TRUE(result);
}

TEST_F(GridProcessorTest, ValidateGridInvalid) {
    // Arrange
    std::vector<std::string_view> grid = {"abc", "de", "ghi"};

    // Act
    auto result = aoc::grid_processor::validateGrid(grid);

    // Assert
    EXPECT_FALSE(result);
}

TEST_F(GridProcessorTest, ValidateGridEmpty) {
    // Arrange
    std::vector<std::string_view> grid;

    // Act
    auto result = aoc::grid_processor::validateGrid(grid);

    // Assert
    EXPECT_TRUE(result);
}

TEST_F(GridProcessorTest, ValidateGridSingleLine) {
    // Arrange
    std::vector<std::string_view> grid = {"abc"};

    // Act
    auto result = aoc::grid_processor::validateGrid(grid);

    // Assert
    EXPECT_TRUE(result);
}
