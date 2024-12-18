#include "../lib/opcode.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;

class OpcodeTest : public Test {
  protected:
    void SetUp() override {
    }
};

class OpcodeToStringTest : public OpcodeTest, public WithParamInterface<std::pair<aoc::day_17::opcode, std::string>> {};

TEST_P(OpcodeToStringTest, ToString_ReturnsCorrectString) {
    // Arrange
    auto [opcode, expected] = GetParam();

    // Act
    auto result = aoc::day_17::to_string(opcode);

    // Assert
    EXPECT_EQ(result, expected);
}

INSTANTIATE_TEST_SUITE_P(
    OpcodeConversions, OpcodeToStringTest,
    Values(std::make_pair(aoc::day_17::opcode::ADV, "ADV"), std::make_pair(aoc::day_17::opcode::BXL, "BXL"),
           std::make_pair(aoc::day_17::opcode::BST, "BST"), std::make_pair(aoc::day_17::opcode::JNZ, "JNZ"),
           std::make_pair(aoc::day_17::opcode::BXC, "BXC"), std::make_pair(aoc::day_17::opcode::OUT, "OUT"),
           std::make_pair(aoc::day_17::opcode::BDV, "BDV"), std::make_pair(aoc::day_17::opcode::CDV, "CDV")));

TEST_F(OpcodeTest, CastingToUnderlyingType) {
    // Arrange
    auto opcode = aoc::day_17::opcode::ADV;

    // Act
    auto value = static_cast<std::underlying_type_t<aoc::day_17::opcode>>(opcode);

    // Assert
    EXPECT_EQ(value, 0);
}

TEST_F(OpcodeTest, OpcodeValues_AreSequential) {
    // Arrange
    std::vector<aoc::day_17::opcode> opcodes{
        aoc::day_17::opcode::ADV, aoc::day_17::opcode::BXL, aoc::day_17::opcode::BST, aoc::day_17::opcode::JNZ,
        aoc::day_17::opcode::BXC, aoc::day_17::opcode::OUT, aoc::day_17::opcode::BDV, aoc::day_17::opcode::CDV};

    // Act & Assert
    for (size_t i = 0; i < opcodes.size(); ++i) {
        EXPECT_EQ(static_cast<int>(opcodes[i]), i);
    }
}