#include "../lib/page_ordering_rule.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::ElementsAre;

class PageOrderingRuleTest : public ::testing::Test {
  protected:
    // Simple rule where 1 must come before 2
    aoc::day_5::page_ordering_rule basic_rule{1, 2};
};

TEST_F(PageOrderingRuleTest, RuleIsFullfilledWhenPrePageNotPresent) {
    std::vector<uint8_t> pages{2, 3, 4};
    EXPECT_TRUE(basic_rule.isFullfilled(pages));
}

TEST_F(PageOrderingRuleTest, RuleIsFullfilledWhenPostPageNotPresent) {
    std::vector<uint8_t> pages{1, 3, 4};
    EXPECT_TRUE(basic_rule.isFullfilled(pages));
}

TEST_F(PageOrderingRuleTest, RuleIsFullfilledWhenOrderIsCorrect) {
    std::vector<uint8_t> pages{1, 3, 2};
    EXPECT_TRUE(basic_rule.isFullfilled(pages));
}

TEST_F(PageOrderingRuleTest, RuleIsNotFullfilledWhenOrderIsIncorrect) {
    std::vector<uint8_t> pages{2, 3, 1};
    EXPECT_FALSE(basic_rule.isFullfilled(pages));
}

TEST_F(PageOrderingRuleTest, FixPageSwapsElementsWhenBothPresent) {
    std::vector<uint8_t> pages{2, 3, 1};
    basic_rule.fixPage(pages);
    EXPECT_THAT(pages, ElementsAre(1, 3, 2));
}

TEST_F(PageOrderingRuleTest, FixPageDoesNothingWhenPrePageMissing) {
    std::vector<uint8_t> pages{2, 3, 4};
    auto original = pages;
    basic_rule.fixPage(pages);
    EXPECT_THAT(pages, ElementsAre(2, 3, 4));
}

TEST_F(PageOrderingRuleTest, FixPageDoesNothingWhenPostPageMissing) {
    std::vector<uint8_t> pages{1, 3, 4};
    auto original = pages;
    basic_rule.fixPage(pages);
    EXPECT_THAT(pages, ElementsAre(1, 3, 4));
}

TEST_F(PageOrderingRuleTest, HandlesEmptyVector) {
    std::vector<uint8_t> empty;
    EXPECT_TRUE(basic_rule.isFullfilled(empty));
    basic_rule.fixPage(empty);
    EXPECT_TRUE(empty.empty());
}

TEST_F(PageOrderingRuleTest, HandlesVectorWithSingleElement) {
    std::vector<uint8_t> single{1};
    EXPECT_TRUE(basic_rule.isFullfilled(single));
    basic_rule.fixPage(single);
    EXPECT_EQ(single.size(), 1);
    EXPECT_EQ(single[0], 1);
}

TEST_F(PageOrderingRuleTest, HandlesElementsAtEdges) {
    std::vector<uint8_t> pages{2, 3, 4, 5, 1}; // 1 at end, 2 at start
    EXPECT_FALSE(basic_rule.isFullfilled(pages));
    basic_rule.fixPage(pages);
    EXPECT_THAT(pages, ElementsAre(1, 3, 4, 5, 2));
}
