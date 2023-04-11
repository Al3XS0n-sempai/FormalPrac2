#include <gtest/gtest.h>
#include <vector>
#include "Grammar_t.h"

class Rule_t_Test : public ::testing::Test {
protected:
    virtual void SetUp() {
        construct1 = Grammar_t::Rule_t('S', "sSs");
        construct2 = Grammar_t::Rule_t(construct1);

        equal_left = Grammar_t::Rule_t('A', "pDp");
        equal_right = Grammar_t::Rule_t(equal_left);
    }

    Grammar_t::Rule_t construct1;
    Grammar_t::Rule_t construct2;
    Grammar_t::Rule_t equal_left;
    Grammar_t::Rule_t equal_right;
};

TEST_F(Rule_t_Test, ConstructFromCharAndString) {
    EXPECT_EQ(construct1.from(), 'S');
    EXPECT_EQ(construct1.to(), "sSs");
}

TEST_F(Rule_t_Test, ConstructFromOtherRule) {
    EXPECT_EQ(construct2.from(), 'S');
    EXPECT_EQ(construct2.to(), "sSs");
}

TEST_F(Rule_t_Test, EqualToAnotherRule) {
    EXPECT_TRUE(equal_left == equal_right);
}

TEST_F(Rule_t_Test, NotEqualToAnotherRule) {
    EXPECT_FALSE(construct1 == Grammar_t::Rule_t('B', "sSs"));
    EXPECT_FALSE(construct1 == Grammar_t::Rule_t('S', "Ss"));
}

class Grammar_t_Test : public ::testing::Test {
protected:
    virtual void SetUp() {
        grammar = Grammar_t("test_grammar.txt");

        oneRule = Grammar_t();
        twoRule = Grammar_t();
        oneRule.addRule(Grammar_t::Rule_t('B', "b"));
        twoRule.addRule("S->SS|a");
    }

    Grammar_t grammar;
    Grammar_t oneRule;
    Grammar_t twoRule;
};

TEST_F(Grammar_t_Test, ConstructFromFile) {
    EXPECT_EQ(grammar.getRules('S').size(), 3);
}

TEST_F(Grammar_t_Test, AddRuleByRule_t) {
    EXPECT_EQ(oneRule.getRules('B').size(), 1);
}

TEST_F(Grammar_t_Test, AddRuleByString) {
    EXPECT_EQ(twoRule.getRules('S').size(), 2);
}

TEST_F(Grammar_t_Test, StartNotTerminal) {
    EXPECT_EQ(grammar.startNotTerminal(), 'S');
}

TEST_F(Grammar_t_Test, IsTerminal) {
    EXPECT_TRUE(Grammar_t::isTerminal('a'));
    EXPECT_FALSE(Grammar_t::isNotTerminal('a'));
}

TEST_F(Grammar_t_Test, IsNotTerminal) {
    EXPECT_TRUE(Grammar_t::isNotTerminal('A'));
    EXPECT_FALSE(Grammar_t::isTerminal('A'));
}