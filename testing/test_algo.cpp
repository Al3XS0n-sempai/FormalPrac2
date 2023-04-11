#include <gtest/gtest.h>
#include "Algo.h"
#include "Grammar_t.h"

class Situation_t_Test : public ::testing::Test {
protected:
    virtual void SetUp() {
        Grammar_t::Rule_t rule('S', "aSS");
        construct1 = Situation_t(rule, 0, 0);

        construct2 = Situation_t(construct1);

        construct3 = Situation_t(rule, 1, 0);

        construct4 = construct3.move();
    }

    Situation_t construct1;
    Situation_t construct2;
    Situation_t construct3;
    Situation_t construct4;
};

TEST_F(Situation_t_Test, ConstructFromRule) {
    EXPECT_EQ(construct1.getRule(), Grammar_t::Rule_t('S', "aSS"));
    EXPECT_EQ(construct1.getIndex(), 0);
    EXPECT_EQ(construct1.getNext(), 'a');
}

TEST_F(Situation_t_Test, ConstructFromAnother) {
    EXPECT_EQ(construct1.getRule(), construct2.getRule());
    EXPECT_EQ(construct1.getIndex(), construct2.getIndex());
    EXPECT_EQ(construct1.getNext(), construct2.getNext());
}

TEST_F(Situation_t_Test, OperatorIsEqual) {
    EXPECT_TRUE(construct2 == construct1);
    EXPECT_FALSE(construct2 == construct3);
}

TEST_F(Situation_t_Test, Move) {
    EXPECT_TRUE(construct2.move() == construct3);
}

TEST_F(Situation_t_Test, IsDotLast) {
    EXPECT_FALSE(construct4.isDotLast());
    EXPECT_TRUE(construct4.move().isDotLast());
}

class Algo_Test : public ::testing::Test {
protected:
    virtual void SetUp() {
        algo = Algo("test_grammar.txt");
        algo1 = Algo("test_algo.txt");
    }

    Algo algo;
    Algo algo1;
};

TEST_F(Algo_Test, ConstructTest) {
    EXPECT_EQ(algo.getGrammar().getRules('S').size(), 3);
    EXPECT_EQ(algo.getGrammar().startNotTerminal(), 'S');
}

TEST_F(Algo_Test, Predict_True1) {
    EXPECT_TRUE(algo.predict("aab"));
}

TEST_F(Algo_Test, Predict_True2) {
    EXPECT_TRUE(algo.predict("abb"));
}

TEST_F(Algo_Test, Predict_True3) {
    EXPECT_TRUE(algo.predict("aaabb"));
}

TEST_F(Algo_Test, Predict_True4) {
    EXPECT_TRUE(algo.predict("aabbb"));
}

TEST_F(Algo_Test, Predict_True5) {
    EXPECT_TRUE(algo1.predict("()"));
}

TEST_F(Algo_Test, Predict_True6) {
    EXPECT_TRUE(algo1.predict(""));
}

TEST_F(Algo_Test, Predict_True7) {
    EXPECT_TRUE(algo1.predict("()(()())"));
}

TEST_F(Algo_Test, Predict_False1) {
    EXPECT_FALSE(algo.predict("ab"));
}

TEST_F(Algo_Test, Predict_False2) {
    EXPECT_FALSE(algo.predict("aa"));
}

TEST_F(Algo_Test, Predict_False3) {
    EXPECT_FALSE(algo.predict("aaaabbbbbbbbbb"));
}

TEST_F(Algo_Test, Predict_False4) {
    EXPECT_FALSE(algo1.predict("(a)"));
}

TEST_F(Algo_Test, Predict_False5) {
    EXPECT_FALSE(algo1.predict("((()"));
}

TEST_F(Algo_Test, Predict_False6) {
    EXPECT_FALSE(algo1.predict("("));
}

TEST_F(Algo_Test, Predict_False7) {
    EXPECT_FALSE(algo1.predict("basd"));
}