#include "../lib/calculations.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../shared/src/vector2d.hpp"

using namespace aoc::day_15;
using ::testing::ElementsAre;

TEST(GpsCalculationTest, CalculatesSimpleCoordinate) {
    // Arrange
    aoc::math::vector_2d<size_t> position{5, 2};

    // Act
    auto result = calculate_gps_coordinate(position);

    // Assert
    EXPECT_EQ(result, 205); // 2 * 100 + 5
}

TEST(GpsCalculationTest, CalculatesZeroCoordinate) {
    // Arrange
    aoc::math::vector_2d<size_t> position{0, 0};

    // Act
    auto result = calculate_gps_coordinate(position);

    // Assert
    EXPECT_EQ(result, 0);
}

class GpsCalculationParameterizedTest : public ::testing::TestWithParam<std::tuple<size_t, size_t, size_t>> {};

TEST_P(GpsCalculationParameterizedTest, CalculatesCorrectCoordinates) {
    // Arrange
    auto const [x, y, expected] = GetParam();
    aoc::math::vector_2d<size_t> position{x, y};

    // Act
    auto result = calculate_gps_coordinate(position);

    // Assert
    EXPECT_EQ(result, expected);
}

INSTANTIATE_TEST_SUITE_P(CoordinateTests, GpsCalculationParameterizedTest,
                         ::testing::Values(std::make_tuple(1, 1, 101), std::make_tuple(10, 2, 210),
                                           std::make_tuple(99, 99, 9999)));

TEST(WarehouseSumTest, CalculatesEmptyWarehouse) {
    // Arrange
    std::vector<std::vector<cell_type>> warehouse{{cell_type::EMPTY, cell_type::EMPTY},
                                                  {cell_type::EMPTY, cell_type::EMPTY}};

    // Act
    auto result = calculate_gps_sum(warehouse);

    // Assert
    EXPECT_EQ(result, 0);
}

TEST(WarehouseSumTest, CalculatesSingleBox) {
    // Arrange
    std::vector<std::vector<cell_type>> warehouse{{cell_type::BOX, cell_type::EMPTY},
                                                  {cell_type::EMPTY, cell_type::EMPTY}};

    // Act
    auto result = calculate_gps_sum(warehouse);

    // Assert
    EXPECT_EQ(result, 0); // box at (0,0) = 0*100 + 0
}

TEST(WarehouseSumTest, CalculatesMultipleBoxes) {
    // Arrange
    std::vector<std::vector<cell_type>> warehouse{{cell_type::BOX, cell_type::EMPTY, cell_type::BOX},
                                                  {cell_type::EMPTY, cell_type::BOX, cell_type::EMPTY},
                                                  {cell_type::BOX, cell_type::EMPTY, cell_type::BOX}};

    // Act
    auto result = calculate_gps_sum(warehouse);

    // Assert
    // Boxes at: (0,0)=0, (2,0)=2, (1,1)=101, (0,2)=200, (2,2)=202
    EXPECT_EQ(result, 505);
}

TEST(WarehouseSumTest, HandlesPartialBoxes) {
    // Arrange
    std::vector<std::vector<cell_type>> warehouse{{cell_type::BOX_PART_LEFT, cell_type::EMPTY},
                                                  {cell_type::EMPTY, cell_type::BOX}};

    // Act
    auto result = calculate_gps_sum(warehouse);

    // Assert
    EXPECT_EQ(result, 101); // Left part at (0,0)=0, full box at (1,1)=101
}