#include "../lib/virtual_machine.hpp"

#include <gtest/gtest.h>

#include <vector>

class VirtualMachineTest : public ::testing::Test {
  protected:
    void SetUp() override {
    }
    int64_t const & registerA() const {
        return m_vm.m_register_a;
    }
    int64_t const & registerB() const {
        return m_vm.m_register_b;
    }

    int64_t const & registerC() const {
        return m_vm.m_register_c;
    }

    void execute(aoc::day_17::program const & prog) {
        m_vm.execute(prog);
    }

    void assertOutputIs(std::vector<int64_t> const & expected) {
        ASSERT_EQ(m_output, expected);
    }

  private:
    aoc::day_17::virtual_machine m_vm{
        [this](std::string_view output) { m_output.push_back(std::stoll(std::string{output})); }};
    std::vector<int64_t> m_output;
};

class VirtualMachineOutputTest : public VirtualMachineTest,
                                 public ::testing::WithParamInterface<std::pair<int64_t, int64_t>> {};

TEST_F(VirtualMachineTest, ADV_DividesRegisterA) {
    // Arrange
    aoc::day_17::program prog{
        std::vector<aoc::day_17::opcode>{aoc::day_17::opcode::ADV, static_cast<aoc::day_17::opcode>(2)}, 16, 0, 0};

    // Act
    execute(prog);

    // Assert
    EXPECT_EQ(registerA(), 4);
}

TEST_F(VirtualMachineTest, BXL_XorsRegisterBWithLiteral) {
    // Arrange
    aoc::day_17::program prog{
        std::vector<aoc::day_17::opcode>{aoc::day_17::opcode::BXL, static_cast<aoc::day_17::opcode>(5)}, 0, 3, 0};

    execute(prog);

    // Assert
    EXPECT_EQ(registerB(), 6);
}

TEST_F(VirtualMachineTest, BST_SetsRegisterBWithModulo) {
    // Arrange
    aoc::day_17::program prog{
        std::vector<aoc::day_17::opcode>{aoc::day_17::opcode::BST, static_cast<aoc::day_17::opcode>(10)}, 0, 0, 0};

    // Act
    execute(prog);

    // Assert
    EXPECT_EQ(registerB(), 2); // 10 % 8 = 2
}

TEST_F(VirtualMachineTest, JNZ_JumpsWhenRegisterANonZero) {
    // Arrange
    aoc::day_17::program prog{
        std::vector<aoc::day_17::opcode>{aoc::day_17::opcode::BST, static_cast<aoc::day_17::opcode>(3),
                                         aoc::day_17::opcode::JNZ, static_cast<aoc::day_17::opcode>(4),
                                         aoc::day_17::opcode::BST, static_cast<aoc::day_17::opcode>(5),
                                         aoc::day_17::opcode::BST, static_cast<aoc::day_17::opcode>(2)},
        1, 0, 0};

    // Act
    execute(prog);

    // Assert
    EXPECT_EQ(registerB(), 2);
}

TEST_F(VirtualMachineTest, BXC_XorsRegisterBWithRegisterC) {
    // Arrange
    aoc::day_17::program prog{
        std::vector<aoc::day_17::opcode>{aoc::day_17::opcode::BXC, static_cast<aoc::day_17::opcode>(0)}, 0, 3, 5};

    // Act
    execute(prog);

    // Assert
    EXPECT_EQ(registerB(), 6);
}

TEST_P(VirtualMachineOutputTest, OUT_OutputsCorrectValue) {
    // Arrange
    auto [input, expected] = GetParam();
    aoc::day_17::program prog{
        std::vector<aoc::day_17::opcode>{aoc::day_17::opcode::OUT, static_cast<aoc::day_17::opcode>(input)}, 0, 0, 0};

    // Act
    execute(prog);

    // Assert
    assertOutputIs({expected});
}

INSTANTIATE_TEST_SUITE_P(OutputTests, VirtualMachineOutputTest,
                         ::testing::Values(std::make_pair(3, 3), std::make_pair(8, 0), std::make_pair(15, 7)));

TEST_F(VirtualMachineTest, BDV_DividesRegisterAIntoRegisterB) {
    // Arrange
    aoc::day_17::program prog{
        std::vector<aoc::day_17::opcode>{aoc::day_17::opcode::BDV, static_cast<aoc::day_17::opcode>(2)}, 16, 0, 0};

    // Act
    execute(prog);

    // Assert
    EXPECT_EQ(registerB(), 4);
}

TEST_F(VirtualMachineTest, CDV_DividesRegisterAIntoRegisterC) {
    // Arrange
    aoc::day_17::program prog{
        std::vector<aoc::day_17::opcode>{aoc::day_17::opcode::CDV, static_cast<aoc::day_17::opcode>(3)}, 16, 0, 0};

    // Act
    execute(prog);

    // Assert
    EXPECT_EQ(registerC(), 2);
}

TEST_F(VirtualMachineTest, ComplexProgram) {
    // Arrange
    aoc::day_17::program prog{
        std::vector<aoc::day_17::opcode>{aoc::day_17::opcode::BST, static_cast<aoc::day_17::opcode>(3),
                                         aoc::day_17::opcode::BXL, static_cast<aoc::day_17::opcode>(2),
                                         aoc::day_17::opcode::OUT, static_cast<aoc::day_17::opcode>(5)},
        0, 0, 0};

    // Act
    execute(prog);

    // Assert
    EXPECT_EQ(registerB(), 1);
    assertOutputIs({1});
}
