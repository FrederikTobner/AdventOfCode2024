#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../lib/disk_map_parser.hpp"

using namespace aoc::day_9;

TEST(DiskMapParserTest, ValidInputParsing) {
    // Arrange
    auto input = "1122";

    // Act
    auto result = parseDiskMap(input);

    // Assert
    ASSERT_TRUE(result.has_value());
    auto & entries = result->entries;
    EXPECT_EQ(entries.size(), 2);
    EXPECT_EQ(entries[0].file_length, 1);
    EXPECT_EQ(entries[0].free_space, 1);
    EXPECT_EQ(entries[1].file_length, 2);
    EXPECT_EQ(entries[1].free_space, 2);
}

TEST(DiskMapParserTest, SingleDigitInput) {
    // Arrange
    auto input = "1";

    // Act
    auto result = parseDiskMap(input);

    // Assert
    ASSERT_TRUE(result.has_value());
    auto & entries = result->entries;
    EXPECT_EQ(entries.size(), 1);
    EXPECT_EQ(entries[0].file_length, 1);
    EXPECT_EQ(entries[0].free_space, 0);
}

TEST(DiskMapParserTest, EmptyInput) {
    // Arrange
    auto input = "";

    // Act
    auto result = parseDiskMap(input);

    // Assert
    ASSERT_TRUE(result.has_value());
    EXPECT_TRUE(result->entries.empty());
}

TEST(DiskMapParserTest, InvalidCharacter) {
    // Arrange
    auto input = "11a2";

    // Act
    auto result = parseDiskMap(input);

    // Assert
    ASSERT_FALSE(result.has_value());
}

TEST(DiskMapParserTest, LargeValidInput) {
    // Arrange
    auto input = "112233445566";

    // Act
    auto result = parseDiskMap(input);

    // Assert
    ASSERT_TRUE(result.has_value());
    auto & entries = result->entries;
    EXPECT_EQ(entries.size(), 6);
    for (size_t i = 0; i < 6; ++i) {
        EXPECT_EQ(entries[i].file_length, i + 1);
        EXPECT_EQ(entries[i].free_space, i + 1);
    }
}