#include "../lib/grid_processor.hpp"

#include <gtest/gtest.h>

class GridProcessorTest : public ::testing::Test {
  protected:
    const std::string normal_input = "abc\ndef\nghi";
    const std::string input_with_cr = "abc\r\ndef\r\nghi";
    const std::string empty_input = "";
    const std::string single_line = "abc";
};

TEST_F(GridProcessorTest, ProcessLinesNormalInput) {
    auto result = aoc::day_4::processLines(normal_input);
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "abc");
    EXPECT_EQ(result[1], "def");
    EXPECT_EQ(result[2], "ghi");
}

TEST_F(GridProcessorTest, ProcessLinesWithCarriageReturn) {
    auto result = aoc::day_4::processLines(input_with_cr);
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "abc");
    EXPECT_EQ(result[1], "def");
    EXPECT_EQ(result[2], "ghi");
}

TEST_F(GridProcessorTest, ProcessLinesSingleLine) {
    auto result = aoc::day_4::processLines(single_line);
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "abc");
}

TEST_F(GridProcessorTest, ValidateGridValid) {
    std::vector<std::string_view> grid = {"abc", "def", "ghi"};
    EXPECT_TRUE(aoc::day_4::validateGrid(grid));
}

TEST_F(GridProcessorTest, ValidateGridInvalid) {
    std::vector<std::string_view> grid = {"abc", "de", "ghi"};
    EXPECT_FALSE(aoc::day_4::validateGrid(grid));
}

TEST_F(GridProcessorTest, ValidateGridEmpty) {
    std::vector<std::string_view> grid;
    EXPECT_TRUE(aoc::day_4::validateGrid(grid));
}

TEST_F(GridProcessorTest, ValidateGridSingleLine) {
    std::vector<std::string_view> grid = {"abc"};
    EXPECT_TRUE(aoc::day_4::validateGrid(grid));
}
