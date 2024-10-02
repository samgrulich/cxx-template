#include <gtest/gtest.h>
#include "lib.h"

class Initialization2x3 : public testing::Test {
    protected:
        State state;
        Initialization2x3() : state(2, 3) {
            // row 1
            state.parseInput(0, 0, 0);
            state.parseInput(0, 1, 1);
            state.parseInput(0, 2, 1);
            state.parseInput(0, 3, 0);
            state.parseInput(0, 4, 1);
            // row 2
            state.parseInput(1, 0, 1);
            state.parseInput(1, 1, 1);
            state.parseInput(1, 2, 1);
            state.parseInput(1, 3, 0);
            state.parseInput(1, 4, 1);
        }
};

TEST_F(Initialization2x3, Values) {
    ASSERT_EQ(state.values(0, 0), 0);
    ASSERT_EQ(state.values(0, 1), 1);
    ASSERT_EQ(state.values(0, 2), 1);
    ASSERT_EQ(state.values(0, 3), 0);
    ASSERT_EQ(state.values(0, 4), 1);
    ASSERT_EQ(state.values(1, 0), 1);
    ASSERT_EQ(state.values(1, 1), 1);
    ASSERT_EQ(state.values(1, 2), 1);
    ASSERT_EQ(state.values(1, 3), 0);
    ASSERT_EQ(state.values(1, 4), 1);
}

TEST_F(Initialization2x3, RowPrefixes) {

}

TEST_F(Initialization2x3, ColPrefixes) {
}

TEST_F(Initialization2x3, RowSectorPrefixes) {
}

TEST_F(Initialization2x3, ColSectorPrefixes) {
}

TEST_F(Initialization2x3, SectorPrefixes) {
}
