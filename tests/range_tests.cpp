/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include "pluto/range.hpp"

#include <gtest/gtest.h>

class RangeTests : public testing::Test
{
public:
    const pluto::IntRange intRange1{ 0, 0 };
    const pluto::IntRange intRange2{ 0, 0 };
    const pluto::IntRange intRange3{ 1, 6 };
    const pluto::IntRange intRange4{ 2, 8 };
    const pluto::IntRange intRange5{ 6, 9 };

protected:
    RangeTests() {}
    ~RangeTests() {}
};

TEST_F(RangeTests, TestRangeSanity)
{
    pluto::IntRange intRange{ 1, 2 };

    ASSERT_EQ(intRange.begin, 1);
    ASSERT_EQ(intRange.end, 2);

    ASSERT_EQ(intRange.size(), 1);

    intRange.begin = 2;
    intRange.end = 4;

    ASSERT_EQ(intRange.size(), 2);
}

TEST_F(RangeTests, TestRangeCopyConstructor)
{
    pluto::IntRange intRange{ 1, 2 };

    ASSERT_EQ(intRange.begin, 1);
    ASSERT_EQ(intRange.end, 2);

    ASSERT_EQ(intRange.size(), 1);

    pluto::IntRange intRange2{ intRange };

    ASSERT_EQ(intRange2.begin, 1);
    ASSERT_EQ(intRange2.end, 2);

    ASSERT_EQ(intRange2.size(), 1);
}

TEST_F(RangeTests, TestRangeIsEqual)
{
    ASSERT_TRUE(intRange1.isEqual(intRange2));
    ASSERT_TRUE(intRange2.isEqual(intRange1));
    ASSERT_FALSE(intRange3.isEqual(intRange4));
    ASSERT_FALSE(intRange4.isEqual(intRange3));
    ASSERT_FALSE(intRange3.isEqual(intRange5));
    ASSERT_FALSE(intRange5.isEqual(intRange3));

    ASSERT_TRUE(intRange1 == intRange2);
    ASSERT_TRUE(intRange2 == intRange1);
    ASSERT_FALSE(intRange3 == intRange4);
    ASSERT_FALSE(intRange4 == intRange3);
    ASSERT_FALSE(intRange3 == intRange5);
    ASSERT_FALSE(intRange5 == intRange3);
}

TEST_F(RangeTests, TestRangeIsNotEqual)
{
    ASSERT_FALSE(intRange1 != intRange2);
    ASSERT_FALSE(intRange2 != intRange1);
    ASSERT_TRUE(intRange3 != intRange4);
    ASSERT_TRUE(intRange4 != intRange3);
    ASSERT_TRUE(intRange3 != intRange5);
    ASSERT_TRUE(intRange5 != intRange3);
}

TEST_F(RangeTests, TestRangeIsLess)
{
    ASSERT_FALSE(intRange1.isLess(intRange2));
    ASSERT_FALSE(intRange2.isLess(intRange1));
    ASSERT_TRUE(intRange3.isLess(intRange4));
    ASSERT_FALSE(intRange4.isLess(intRange3));
    ASSERT_TRUE(intRange3.isLess(intRange5));
    ASSERT_FALSE(intRange5.isLess(intRange3));

    ASSERT_FALSE(intRange1 < intRange2);
    ASSERT_FALSE(intRange2 < intRange1);
    ASSERT_TRUE(intRange3 < intRange4);
    ASSERT_FALSE(intRange4 < intRange3);
    ASSERT_TRUE(intRange3 < intRange5);
    ASSERT_FALSE(intRange5 < intRange3);
}

TEST_F(RangeTests, TestRangeIsGreater)
{
    ASSERT_FALSE(intRange1 > intRange2);
    ASSERT_FALSE(intRange2 > intRange1);
    ASSERT_FALSE(intRange3 > intRange4);
    ASSERT_TRUE(intRange4 > intRange3);
    ASSERT_FALSE(intRange3 > intRange5);
    ASSERT_TRUE(intRange5 > intRange3);
}

TEST_F(RangeTests, TestRangeIsLessEqual)
{
    ASSERT_TRUE(intRange1 <= intRange2);
    ASSERT_TRUE(intRange2 <= intRange1);
    ASSERT_TRUE(intRange3 <= intRange4);
    ASSERT_FALSE(intRange4 <= intRange3);
    ASSERT_TRUE(intRange3 <= intRange5);
    ASSERT_FALSE(intRange5 <= intRange3);
}

TEST_F(RangeTests, TestRangeIsGreaterEqual)
{
    ASSERT_TRUE(intRange1 >= intRange2);
    ASSERT_TRUE(intRange2 >= intRange1);
    ASSERT_FALSE(intRange3 >= intRange4);
    ASSERT_TRUE(intRange4 >= intRange3);
    ASSERT_FALSE(intRange3 >= intRange5);
    ASSERT_TRUE(intRange5 >= intRange3);
}

TEST_F(RangeTests, TestRangeIsOverlapping)
{
    ASSERT_FALSE(intRange1.isOverlapping(intRange2));
    ASSERT_FALSE(intRange2.isOverlapping(intRange1));
    ASSERT_TRUE(intRange3.isOverlapping(intRange4));
    ASSERT_TRUE(intRange4.isOverlapping(intRange3));
    ASSERT_FALSE(intRange3.isOverlapping(intRange5));
    ASSERT_FALSE(intRange5.isOverlapping(intRange3));
}

TEST_F(RangeTests, TestRangeIsLessNoOverlap)
{
    ASSERT_TRUE(intRange1.isLessNoOverlap(intRange2));
    ASSERT_TRUE(intRange2.isLessNoOverlap(intRange1));
    ASSERT_FALSE(intRange3.isLessNoOverlap(intRange4));
    ASSERT_FALSE(intRange4.isLessNoOverlap(intRange3));
    ASSERT_TRUE(intRange3.isLessNoOverlap(intRange5));
    ASSERT_FALSE(intRange5.isLessNoOverlap(intRange3));
}
