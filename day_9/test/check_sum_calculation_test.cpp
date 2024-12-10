#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../lib/check_sum_calculation.hpp"

using namespace aoc::day_9;

class CheckSumCalculationTest : public ::testing::Test {
  protected:
    disk_map createSimpleDiskMap() {
        return disk_map{{
            {1, 1}, // File of length 1 with 1 free space
            {2, 0}, // File of length 2 with no free space
        }};
    }

    disk_map createComplexDiskMap() {
        return disk_map{{
            {2, 2}, // File of length 2 with 2 free spaces
            {1, 1}, // File of length 1 with 1 free space
            {3, 0}, // File of length 3 with no free space
        }};
    }
};

TEST_F(CheckSumCalculationTest, EmptyDiskMapReturnsZero) {
    // Arrange
    disk_map empty{};

    // Act
    auto aggressive_result = calculateChecksumAfterCompacting(empty);
    auto less_aggressive_result = calculateChecksumAfterCompactingLessAgressive(empty);

    // Assert
    EXPECT_EQ(aggressive_result, 0);
    EXPECT_EQ(less_aggressive_result, 0);
}

TEST_F(CheckSumCalculationTest, SingleEntryWithoutFreeSpace) {
    // Arrange
    disk_map map{{disk_map_entry{2, 0}}};

    // Act
    auto aggressive_result = calculateChecksumAfterCompacting(map);
    auto less_aggressive_result = calculateChecksumAfterCompactingLessAgressive(map);

    // Assert
    EXPECT_EQ(aggressive_result, 0);
    EXPECT_EQ(less_aggressive_result, 0);
}

TEST_F(CheckSumCalculationTest, SimpleDiskMapCompacting) {
    // Arrange
    auto map = createSimpleDiskMap();

    // Act
    auto result = calculateChecksumAfterCompacting(map);

    // Assert
    EXPECT_EQ(result, 3);
}

TEST_F(CheckSumCalculationTest, SimpleDiskMapLessAgressiveCompacting) {
    // Arrange
    auto map = createSimpleDiskMap();

    // Act
    auto result = calculateChecksumAfterCompactingLessAgressive(map);

    // Assert
    EXPECT_EQ(result, 5);
}

TEST_F(CheckSumCalculationTest, ComplexDiskMapCompacting) {
    // Arrange
    auto map = createComplexDiskMap();

    // Act
    auto result = calculateChecksumAfterCompacting(map);

    // Assert
    EXPECT_EQ(result, 24);
}

TEST_F(CheckSumCalculationTest, ComplexDiskMapLessAgressiveCompacting) {
    // Arrange
    auto map = createComplexDiskMap();

    // Act
    auto result = calculateChecksumAfterCompactingLessAgressive(map);

    // Assert
    EXPECT_EQ(result, 44); // Different from aggressive due to strategy
}

TEST_F(CheckSumCalculationTest, NoCompactionPossible) {
    // Arrange
    disk_map map{{
        {1, 1}, // Has free space but nothing to move
        {0, 0}, // Empty entry
        {0, 0}, // Empty entry
    }};

    // Act
    auto aggressive_result = calculateChecksumAfterCompacting(map);
    auto less_aggressive_result = calculateChecksumAfterCompactingLessAgressive(map);

    // Assert
    EXPECT_EQ(aggressive_result, 0);
    EXPECT_EQ(less_aggressive_result, 0);
}
