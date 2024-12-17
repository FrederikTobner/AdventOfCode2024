#include "../lib/warehouse_transformer.hpp"
#include <gtest/gtest.h>

using namespace aoc::day_15;

class WarehouseTransformerTest : public ::testing::Test {
  protected:
    void SetUp() override {
    }
};

TEST_F(WarehouseTransformerTest, TransformEmptyCell) {
    // Arrange
    std::vector<std::vector<cell_type>> warehouse = {{cell_type::EMPTY}};

    // Act
    auto transformed = transformWarehouse(warehouse);

    // Assert
    ASSERT_EQ(transformed.size(), 1);
    ASSERT_EQ(transformed[0].size(), 2);
    EXPECT_EQ(transformed[0][0], cell_type::EMPTY);
    EXPECT_EQ(transformed[0][1], cell_type::EMPTY);
}

TEST_F(WarehouseTransformerTest, TransformWallCell) {
    // Arrange
    std::vector<std::vector<cell_type>> warehouse = {{cell_type::WALL}};

    // Act
    auto transformed = transformWarehouse(warehouse);

    // Assert
    ASSERT_EQ(transformed.size(), 1);
    ASSERT_EQ(transformed[0].size(), 2);
    EXPECT_EQ(transformed[0][0], cell_type::WALL);
    EXPECT_EQ(transformed[0][1], cell_type::WALL);
}

TEST_F(WarehouseTransformerTest, TransformBoxCell) {
    // Arrange
    std::vector<std::vector<cell_type>> warehouse = {{cell_type::BOX}};

    // Act
    auto transformed = transformWarehouse(warehouse);

    // Assert
    ASSERT_EQ(transformed.size(), 1);
    ASSERT_EQ(transformed[0].size(), 2);
    EXPECT_EQ(transformed[0][0], cell_type::BOX_PART_LEFT);
    EXPECT_EQ(transformed[0][1], cell_type::BOX_PART_RIGHT);
}

TEST_F(WarehouseTransformerTest, TransformRobotCell) {
    // Arrange
    std::vector<std::vector<cell_type>> warehouse = {{cell_type::ROBOT}};

    // Act
    auto transformed = transformWarehouse(warehouse);

    // Assert
    ASSERT_EQ(transformed.size(), 1);
    ASSERT_EQ(transformed[0].size(), 2);
    EXPECT_EQ(transformed[0][0], cell_type::ROBOT);
    EXPECT_EQ(transformed[0][1], cell_type::EMPTY);
}

TEST_F(WarehouseTransformerTest, TransformCompleteWarehouse) {
    // Arrange
    std::vector<std::vector<cell_type>> warehouse = {{cell_type::WALL, cell_type::EMPTY, cell_type::BOX},
                                                     {cell_type::ROBOT, cell_type::EMPTY, cell_type::WALL}};

    // Act
    auto transformed = transformWarehouse(warehouse);

    // Assert
    ASSERT_EQ(transformed.size(), 2);
    ASSERT_EQ(transformed[0].size(), 6);

    // First row
    EXPECT_EQ(transformed[0][0], cell_type::WALL);
    EXPECT_EQ(transformed[0][1], cell_type::WALL);
    EXPECT_EQ(transformed[0][2], cell_type::EMPTY);
    EXPECT_EQ(transformed[0][3], cell_type::EMPTY);
    EXPECT_EQ(transformed[0][4], cell_type::BOX_PART_LEFT);
    EXPECT_EQ(transformed[0][5], cell_type::BOX_PART_RIGHT);

    // Second row
    EXPECT_EQ(transformed[1][0], cell_type::ROBOT);
    EXPECT_EQ(transformed[1][1], cell_type::EMPTY);
    EXPECT_EQ(transformed[1][2], cell_type::EMPTY);
    EXPECT_EQ(transformed[1][3], cell_type::EMPTY);
    EXPECT_EQ(transformed[1][4], cell_type::WALL);
    EXPECT_EQ(transformed[1][5], cell_type::WALL);
}