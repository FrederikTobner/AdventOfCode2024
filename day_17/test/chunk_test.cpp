#include "../lib/chunk.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;

class ChunkTest : public Test {
  protected:
    void SetUp() override {
    }
};

TEST_F(ChunkTest, Size_ReturnsCorrectNumberOfInstructions) {
    // Arrange
    aoc::day_17::chunk chunk{{aoc::day_17::opcode::ADV, static_cast<aoc::day_17::opcode>(2)}};

    // Act
    auto size = chunk.size();

    // Assert
    EXPECT_EQ(size, 2);
}

TEST_F(ChunkTest, IndexOperator_ReturnsCorrectOpcode) {
    // Arrange
    aoc::day_17::chunk chunk{{aoc::day_17::opcode::BXL, static_cast<aoc::day_17::opcode>(3)}};

    // Act
    auto op = chunk[0];

    // Assert
    EXPECT_EQ(op, aoc::day_17::opcode::BXL);
}

class ChunkToStringTest : public ChunkTest,
                          public WithParamInterface<std::tuple<std::vector<aoc::day_17::opcode>, std::string>> {};

TEST_P(ChunkToStringTest, ToString_FormatsInstructionsCorrectly) {
    // Arrange
    auto [instructions, expected] = GetParam();
    aoc::day_17::chunk chunk{instructions};

    // Act
    auto result = chunk.to_string();

    // Assert
    EXPECT_EQ(result, expected);
}

INSTANTIATE_TEST_SUITE_P(ChunkFormatting, ChunkToStringTest,
                         Values(std::make_tuple(std::vector<aoc::day_17::opcode>{aoc::day_17::opcode::ADV,
                                                                                 static_cast<aoc::day_17::opcode>(2)},
                                                "000: ADV 2\n"),
                                std::make_tuple(std::vector<aoc::day_17::opcode>{aoc::day_17::opcode::BST,
                                                                                 static_cast<aoc::day_17::opcode>(4)},
                                                "000: BST a\n")));

TEST_F(ChunkTest, ComplexInstructionSequence) {
    // Arrange
    aoc::day_17::chunk chunk{{aoc::day_17::opcode::ADV, static_cast<aoc::day_17::opcode>(2), aoc::day_17::opcode::BST,
                              static_cast<aoc::day_17::opcode>(5), aoc::day_17::opcode::CDV,
                              static_cast<aoc::day_17::opcode>(3)}};

    // Act
    auto size = chunk.size();
    auto first_op = chunk[0];
    auto last_op = chunk[4];

    // Assert
    EXPECT_EQ(size, 6);
    EXPECT_EQ(first_op, aoc::day_17::opcode::ADV);
    EXPECT_EQ(last_op, aoc::day_17::opcode::CDV);
}

TEST_F(ChunkTest, RegisterOperandFormatting) {
    // Arrange
    aoc::day_17::chunk chunk{{
        aoc::day_17::opcode::BST,
        static_cast<aoc::day_17::opcode>(4), // register a
        aoc::day_17::opcode::BST,
        static_cast<aoc::day_17::opcode>(5), // register b
        aoc::day_17::opcode::BST,
        static_cast<aoc::day_17::opcode>(6) // register c
    }};

    // Act
    auto result = chunk.to_string();

    // Assert
    EXPECT_THAT(result, AllOf(HasSubstr("BST a"), HasSubstr("BST b"), HasSubstr("BST c")));
}