#include <gtest/gtest.h>
#include "lib.h"

class Initialization2x5 : public testing::Test {
    protected:
        State state_;
        Initialization2x5() : state_(2, 5) {
            uint data[] = {
                0, 1, 1, 0, 1,
                1, 1, 1, 0, 1
            };
            state_.parseInputs(data);
        }
};

class Sectors5x5 : public testing::Test {
    protected:
        State state_;
        Sectors5x5() : state_(5, 5) {
            uint data[] = {
                1, 1, 0, 0, 0,
                0, 1, 0, 0, 0,
                0, 1, 1, 1, 1,
                1, 1, 0, 1, 1,
                1, 1, 1, 1, 0
            };
            state_.parseInputs(data);
        }

};

class HalfSectors5x5 : public testing::Test {
    protected:
        State state_;
        int sectorCount_ = 4;
        HalfSectors5x5() : state_(5, 5) {
            uint data[] = {
                1, 1, 1, 1, 1,
                1, 0, 1, 0, 1,
                1, 1, 1, 1, 1,
                1, 0, 1, 0, 1,
                1, 1, 1, 1, 1
            };
            state_.parseInputs(data);
        }
};

TEST_F(Initialization2x5, Values) {
    uint data[] = {
        0, 1, 1, 0, 1, 
        1, 1, 1, 0, 1
    };
    Matrix expected(2, 5, data);
    ASSERT_EQ(state_.values, expected) << "expected: \n" << expected.toString() << "actual: \n" << state_.values.toString();
}

TEST_F(Initialization2x5, RowPrefixes) {
    uint data[] = {
        0, 1, 2, 2, 3, 
        1, 2, 3, 3, 4
    };
    Matrix expected(2, 5, data);
    ASSERT_EQ(state_.rowPrefixes, expected) << "expected: \n" << expected.toString() << "actual: \n" << state_.rowPrefixes.toString();
}

TEST_F(Initialization2x5, ColPrefixes) {
    uint data[] = {
        0, 1, 1, 0, 1, 
        1, 2, 2, 0, 2
    };
    Matrix expected(2, 5, data);
    ASSERT_EQ(state_.colPrefixes, expected) << "expected: \n" << expected.toString() << "actual: \n" << state_.colPrefixes.toString();
}

TEST_F(Initialization2x5, RowSectorPrefixes) {
    uint data[] = {
        1, 1, 1, 2, 2, 
        0, 0, 0, 1, 1
    };
    Matrix expected(2, 5, data);
    ASSERT_EQ(state_.rowSectorPrefixes, expected) << "expected: \n" << expected.toString() << "actual: \n" << state_.rowSectorPrefixes.toString();
}

TEST_F(Initialization2x5, ColSectorPrefixes) {
    uint data[] = {
        1, 0, 0, 1, 0, 
        1, 0, 0, 2, 0
    };
    Matrix expected(2, 5, data);
    ASSERT_EQ(state_.colSectorPrefixes, expected) << "expected: \n" << expected.toString() << "actual: \n" << state_.colSectorPrefixes.toString();
}

TEST_F(Initialization2x5, SectorPrefixes) {
    uint data[] = {
        1, 1, 1, 2, 2, 
        1, 1, 1, 2, 2
    };
    Matrix expected(2, 5, data);
    ASSERT_EQ(state_.sectorPrefixes, expected) << "expected: \n" << expected.toString() << "actual: \n" << state_.sectorPrefixes.toString();
}

TEST_F(Sectors5x5, PrefixSumation) {
    uint data[] = {
        0, 0, 1, 1, 1,
        1, 1, 2, 2, 2,
        1, 1, 2, 2, 2,
        1, 1, 3, 3, 3,
        1, 1, 3, 3, 4
    };
    Matrix expected(5, 5, data);
    ASSERT_EQ(state_.sectorPrefixes, expected) << "expected: " << expected.toString() << "actual: " << state_.sectorPrefixes.toString() << "input: " << state_.values.toString();
}

TEST_F(HalfSectors5x5, ContainsHalfOfAllSectors) {
    EXPECT_TRUE(state_.containsHalfOfAllSectors(0, 0, 4, 2, sectorCount_));
    EXPECT_FALSE(state_.containsHalfOfAllSectors(0, 0, 4, 4, sectorCount_));
}

TEST_F(HalfSectors5x5, ContainsRowEdgeSector) {
    EXPECT_TRUE(state_.containsRowEdgeSector(0, 4, 1));
    EXPECT_FALSE(state_.containsRowEdgeSector(0, 4, 2));
}

TEST_F(HalfSectors5x5, ContainsColEdgeSector) {
    EXPECT_TRUE(state_.containsColEdgeSector(0, 4, 1));
    EXPECT_FALSE(state_.containsColEdgeSector(0, 4, 2));
}

TEST_F(HalfSectors5x5, ContainsAnyEdgeSector) {
    EXPECT_TRUE(state_.containsAnyEdgeSector(1, 1, 3, 3));
    EXPECT_FALSE(state_.containsAnyEdgeSector(0, 0, 4, 4));
}

TEST_F(HalfSectors5x5, GetBorderSum) {
    EXPECT_EQ(state_.getBorderSum(0, 0, 4, 4), 16) << "input: " << state_.values.toString() << std::endl 
        << "sum on border (0,0) (4,4) should be 16 but is " << state_.getBorderSum(0, 0, 4, 4);
    EXPECT_EQ(state_.getBorderSum(1, 1, 3, 3), 4) << "input: " << state_.values.toString() << std::endl 
        << "sum on border (1,1) (3,3) should be 4 but is " << state_.getBorderSum(1, 1, 3, 3);
}
