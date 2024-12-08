
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../lib/map_renderer.hpp"

class MapRendererTest : public ::testing::Test {
  protected:
    void SetUp() override {
        // Reset stdout capture before each test
        testing::internal::CaptureStdout();
    }
};

TEST_F(MapRendererTest, EmptyGridRendersEmpty) {
    std::vector<std::string_view> lines;
    std::unordered_set<aoc::day_8::coordinate> antinodes;

    aoc::day_8::renderResult(lines, antinodes, 0, 0);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Found 0 antinodes\n");
}

TEST_F(MapRendererTest, SimpleGridWithoutAntinodes) {
    std::vector<std::string_view> lines = {"123", "456", "789"};
    std::unordered_set<aoc::day_8::coordinate> antinodes;

    aoc::day_8::renderResult(lines, antinodes, 3, 3);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "123\n456\n789\nFound 0 antinodes\n");
}

TEST_F(MapRendererTest, GridWithSingleAntinode) {
    std::vector<std::string_view> lines = {"123", "456", "789"};
    std::unordered_set<aoc::day_8::coordinate> antinodes{{1, 1}};

    aoc::day_8::renderResult(lines, antinodes, 3, 3);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "123\n4#6\n789\nFound 1 antinodes\n");
}

TEST_F(MapRendererTest, GridWithMultipleAntinodes) {
    std::vector<std::string_view> lines = {"123", "456", "789"};
    std::unordered_set<aoc::day_8::coordinate> antinodes{{0, 0}, {2, 2}};

    aoc::day_8::renderResult(lines, antinodes, 3, 3);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "#23\n456\n78#\nFound 2 antinodes\n");
}

TEST_F(MapRendererTest, LargeGridWithBoundaryAntinodes) {
    std::vector<std::string_view> lines = {".....", ".....", ".....", "....."};
    std::unordered_set<aoc::day_8::coordinate> antinodes{{0, 0}, {0, 4}, {3, 0}, {3, 4}};

    aoc::day_8::renderResult(lines, antinodes, 5, 4);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "#...#\n.....\n.....\n#...#\nFound 4 antinodes\n");
}