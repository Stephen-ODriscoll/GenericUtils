/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#include "generic/container_utils.hpp"

#include <gtest/gtest.h>

class ContainerUtilsTests : public testing::Test
{
public:
    const std::vector<int> empty            { };
    const std::vector<int> zero             { 0 };
    const std::vector<int> one              { 1 };
    const std::vector<int> three            { 3 };
    const std::vector<int> four             { 4 };
    const std::vector<int> five             { 5 };
    const std::vector<int> oneToThree       { 1, 2, 3 };
    const std::vector<int> fourZeroOne      { 4, 0, 1 };
    const std::vector<int> zeroToThree      { 0, 1, 2, 3 };
    const std::vector<int> oneToFour        { 1, 2, 3, 4 };
    const std::vector<int> zeroToFour       { 0, 1, 2, 3, 4 };
    const std::vector<int> zeroToFour2      { 0, 1, 2, 3, 4 };
    const std::vector<int> fiveToNine       { 5, 6, 7, 8, 9 };
    const std::vector<int> zeroToFourTwice  { 0, 1, 2, 3, 4, 0, 1, 2, 3, 4 };
    const std::vector<int> zeroToFourTwice2 { 0, 1, 2, 3, 4, 0, 1, 2, 3, 4 };

protected:
    ContainerUtilsTests() {}
    ~ContainerUtilsTests() {}
};

TEST_F(ContainerUtilsTests, TestEqualsReturnsTrue)
{
    ASSERT_TRUE(Generic::equals(empty, empty));

    ASSERT_TRUE(Generic::equals(zeroToFour, zeroToFour));
    ASSERT_TRUE(Generic::equals(zeroToFour, zeroToFour2));
}

TEST_F(ContainerUtilsTests, TestEqualsReturnsFalse)
{
    ASSERT_FALSE(Generic::equals(zeroToFour, fiveToNine));
    ASSERT_FALSE(Generic::equals(zeroToFour, zeroToThree));
    ASSERT_FALSE(Generic::equals(zeroToFour, oneToFour));

    ASSERT_FALSE(Generic::equals(fiveToNine, zeroToFour));
    ASSERT_FALSE(Generic::equals(fiveToNine, zeroToThree));
    ASSERT_FALSE(Generic::equals(fiveToNine, oneToFour));

    ASSERT_FALSE(Generic::equals(zeroToThree, zeroToFour));
    ASSERT_FALSE(Generic::equals(zeroToThree, fiveToNine));
    ASSERT_FALSE(Generic::equals(zeroToThree, oneToFour));

    ASSERT_FALSE(Generic::equals(oneToFour, zeroToFour));
    ASSERT_FALSE(Generic::equals(oneToFour, fiveToNine));
    ASSERT_FALSE(Generic::equals(oneToFour, zeroToThree));
}

TEST_F(ContainerUtilsTests, TestBeginsWithReturnsTrue)
{
    ASSERT_TRUE(Generic::begins_with(empty, empty));

    ASSERT_TRUE(Generic::begins_with(zeroToFour, zeroToFour));
    ASSERT_TRUE(Generic::begins_with(zeroToFour, zeroToFour2));
    ASSERT_TRUE(Generic::begins_with(zeroToFour, zeroToThree));
    ASSERT_TRUE(Generic::begins_with(zeroToFour, zero));
}

TEST_F(ContainerUtilsTests, TestBeginsWithReturnsFalse)
{
    ASSERT_FALSE(Generic::begins_with(zeroToFour, fiveToNine));
    ASSERT_FALSE(Generic::begins_with(zeroToFour, oneToFour));
    ASSERT_FALSE(Generic::begins_with(zeroToFour, one));

    ASSERT_FALSE(Generic::begins_with(fiveToNine, zeroToFour));
    ASSERT_FALSE(Generic::begins_with(fiveToNine, oneToFour));
    ASSERT_FALSE(Generic::begins_with(fiveToNine, one));

    ASSERT_FALSE(Generic::begins_with(oneToFour, zeroToFour));
    ASSERT_FALSE(Generic::begins_with(oneToFour, fiveToNine));

    ASSERT_FALSE(Generic::begins_with(one, zeroToFour));
    ASSERT_FALSE(Generic::begins_with(one, fiveToNine));
    ASSERT_FALSE(Generic::begins_with(one, oneToFour));
}

TEST_F(ContainerUtilsTests, TestEndsWithReturnsTrue)
{
    ASSERT_TRUE(Generic::ends_with(empty, empty));

    ASSERT_TRUE(Generic::ends_with(zeroToFour, zeroToFour));
    ASSERT_TRUE(Generic::ends_with(zeroToFour, zeroToFour2));
    ASSERT_TRUE(Generic::ends_with(zeroToFour, oneToFour));
    ASSERT_TRUE(Generic::ends_with(zeroToFour, four));
}

TEST_F(ContainerUtilsTests, TestEndsWithReturnsFalse)
{
    ASSERT_FALSE(Generic::ends_with(zeroToFour, fiveToNine));
    ASSERT_FALSE(Generic::ends_with(zeroToFour, zeroToThree));
    ASSERT_FALSE(Generic::ends_with(zeroToFour, three));

    ASSERT_FALSE(Generic::ends_with(fiveToNine, zeroToFour));
    ASSERT_FALSE(Generic::ends_with(fiveToNine, zeroToThree));
    ASSERT_FALSE(Generic::ends_with(fiveToNine, three));

    ASSERT_FALSE(Generic::ends_with(zeroToThree, zeroToFour));
    ASSERT_FALSE(Generic::ends_with(zeroToThree, fiveToNine));

    ASSERT_FALSE(Generic::ends_with(three, zeroToFour));
    ASSERT_FALSE(Generic::ends_with(three, fiveToNine));
    ASSERT_FALSE(Generic::ends_with(three, zeroToThree));
}

TEST_F(ContainerUtilsTests, TestFindElemReturnsPosition)
{
    ASSERT_EQ(Generic::find_elem(zeroToFourTwice, 0), zeroToFourTwice.begin());
    ASSERT_EQ(Generic::find_elem(zeroToFourTwice, 1), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(Generic::find_elem(zeroToFourTwice, 2), zeroToFourTwice.begin() + 2);
    ASSERT_EQ(Generic::find_elem(zeroToFourTwice, 3), zeroToFourTwice.begin() + 3);
    ASSERT_EQ(Generic::find_elem(zeroToFourTwice, 4), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(Generic::find_elem(fourZeroOne, 4), fourZeroOne.begin());
    ASSERT_EQ(Generic::find_elem(fourZeroOne, 0), fourZeroOne.begin() + 1);
    ASSERT_EQ(Generic::find_elem(fourZeroOne, 1), fourZeroOne.begin() + 2);
}

TEST_F(ContainerUtilsTests, TestFindElemReturnsEnd)
{
    ASSERT_EQ(Generic::find_elem(empty, 0), empty.end());
    ASSERT_EQ(Generic::find_elem(zeroToFourTwice, 5), zeroToFourTwice.end());
}

TEST_F(ContainerUtilsTests, TestFindSequenceReturnsPosition)
{
    ASSERT_EQ(Generic::find_sequence(empty, empty), empty.begin());
    ASSERT_EQ(Generic::find_sequence(zeroToFourTwice, empty), zeroToFourTwice.begin());

    ASSERT_EQ(Generic::find_sequence(zeroToFourTwice, zeroToFourTwice), zeroToFourTwice.begin());
    ASSERT_EQ(Generic::find_sequence(zeroToFourTwice, zeroToFourTwice2), zeroToFourTwice.begin());
    ASSERT_EQ(Generic::find_sequence(zeroToFourTwice, fourZeroOne), zeroToFourTwice.begin() + 4);
    ASSERT_EQ(Generic::find_sequence(zeroToFourTwice, oneToThree), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(Generic::find_sequence(zeroToFourTwice, zero), zeroToFourTwice.begin());
    ASSERT_EQ(Generic::find_sequence(zeroToFourTwice, four), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(Generic::find_sequence(fourZeroOne, zero), fourZeroOne.begin() + 1);
    ASSERT_EQ(Generic::find_sequence(fourZeroOne, four), fourZeroOne.begin());
}

TEST_F(ContainerUtilsTests, TestFindSequenceReturnsEnd)
{
    ASSERT_EQ(Generic::find_sequence(zeroToFourTwice, five), zeroToFourTwice.end());
}

TEST_F(ContainerUtilsTests, TestFindIfReturnsPosition)
{
    auto equalsZero { [](int i) { return i == 0; } };
    auto equalsOne  { [](int i) { return i == 1; } };
    auto equalsTwo  { [](int i) { return i == 2; } };
    auto equalsThree{ [](int i) { return i == 3; } };
    auto equalsFour { [](int i) { return i == 4; } };

    ASSERT_EQ(Generic::find_if(zeroToFourTwice, equalsZero), zeroToFourTwice.begin());
    ASSERT_EQ(Generic::find_if(zeroToFourTwice, equalsOne), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(Generic::find_if(zeroToFourTwice, equalsTwo), zeroToFourTwice.begin() + 2);
    ASSERT_EQ(Generic::find_if(zeroToFourTwice, equalsThree), zeroToFourTwice.begin() + 3);
    ASSERT_EQ(Generic::find_if(zeroToFourTwice, equalsFour), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(Generic::find_if(fourZeroOne, equalsFour), fourZeroOne.begin());
    ASSERT_EQ(Generic::find_if(fourZeroOne, equalsZero), fourZeroOne.begin() + 1);
    ASSERT_EQ(Generic::find_if(fourZeroOne, equalsOne), fourZeroOne.begin() + 2);
}

TEST_F(ContainerUtilsTests, TestFindIfReturnsEnd)
{
    auto equalsZero{ [](int i) { return i == 0; } };
    auto equalsFive{ [](int i) { return i == 5; } };

    ASSERT_EQ(Generic::find_if(empty, equalsZero), empty.end());
    ASSERT_EQ(Generic::find_if(zeroToFourTwice, equalsFive), zeroToFourTwice.end());
}

TEST_F(ContainerUtilsTests, TestFindIfNotReturnsPosition)
{
    auto equalsZero { [](int i) { return i == 0; } };
    auto equalsOne  { [](int i) { return i == 1; } };
    auto equalsTwo  { [](int i) { return i == 2; } };
    auto equalsThree{ [](int i) { return i == 3; } };
    auto equalsFour { [](int i) { return i == 4; } };

    ASSERT_EQ(Generic::find_if_not(zeroToFourTwice, equalsZero), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(Generic::find_if_not(zeroToFourTwice, equalsOne), zeroToFourTwice.begin());
    ASSERT_EQ(Generic::find_if_not(zeroToFourTwice, equalsTwo), zeroToFourTwice.begin());
    ASSERT_EQ(Generic::find_if_not(zeroToFourTwice, equalsThree), zeroToFourTwice.begin());
    ASSERT_EQ(Generic::find_if_not(zeroToFourTwice, equalsFour), zeroToFourTwice.begin());

    ASSERT_EQ(Generic::find_if_not(fourZeroOne, equalsFour), fourZeroOne.begin() + 1);
    ASSERT_EQ(Generic::find_if_not(fourZeroOne, equalsZero), fourZeroOne.begin());
    ASSERT_EQ(Generic::find_if_not(fourZeroOne, equalsOne), fourZeroOne.begin());
}

TEST_F(ContainerUtilsTests, TestContainsElemReturnsTrue)
{
    ASSERT_TRUE(Generic::contains_elem(zeroToFourTwice, 0));
    ASSERT_TRUE(Generic::contains_elem(zeroToFourTwice, 1));
    ASSERT_TRUE(Generic::contains_elem(zeroToFourTwice, 2));
    ASSERT_TRUE(Generic::contains_elem(zeroToFourTwice, 3));
    ASSERT_TRUE(Generic::contains_elem(zeroToFourTwice, 4));

    ASSERT_TRUE(Generic::contains_elem(fourZeroOne, 4));
    ASSERT_TRUE(Generic::contains_elem(fourZeroOne, 0));
    ASSERT_TRUE(Generic::contains_elem(fourZeroOne, 1));
}

TEST_F(ContainerUtilsTests, TestContainsElemReturnsFalse)
{
    ASSERT_FALSE(Generic::contains_elem(zeroToFourTwice, 5));
}

TEST_F(ContainerUtilsTests, TestContainsSequenceReturnsTrue)
{
    ASSERT_TRUE(Generic::contains_sequence(empty, empty));
    ASSERT_TRUE(Generic::contains_sequence(zeroToFourTwice, empty));

    ASSERT_TRUE(Generic::contains_sequence(zeroToFourTwice, zeroToFourTwice));
    ASSERT_TRUE(Generic::contains_sequence(zeroToFourTwice, zeroToFourTwice2));
    ASSERT_TRUE(Generic::contains_sequence(zeroToFourTwice, fourZeroOne));
    ASSERT_TRUE(Generic::contains_sequence(zeroToFourTwice, oneToThree));
    ASSERT_TRUE(Generic::contains_sequence(zeroToFourTwice, zero));
    ASSERT_TRUE(Generic::contains_sequence(zeroToFourTwice, four));

    ASSERT_TRUE(Generic::contains_sequence(fourZeroOne, zero));
    ASSERT_TRUE(Generic::contains_sequence(fourZeroOne, four));
}

TEST_F(ContainerUtilsTests, TestContainsSequenceReturnsFalse)
{
    ASSERT_FALSE(Generic::contains_sequence(zeroToFourTwice, five));
}
