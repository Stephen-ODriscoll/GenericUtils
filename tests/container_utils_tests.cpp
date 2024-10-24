/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include "pluto/container_utils.hpp"

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
    ASSERT_TRUE(pluto::equals(empty, empty));

    ASSERT_TRUE(pluto::equals(zeroToFour, zeroToFour));
    ASSERT_TRUE(pluto::equals(zeroToFour, zeroToFour2));
}

TEST_F(ContainerUtilsTests, TestEqualsReturnsFalse)
{
    ASSERT_FALSE(pluto::equals(zeroToFour, fiveToNine));
    ASSERT_FALSE(pluto::equals(zeroToFour, zeroToThree));
    ASSERT_FALSE(pluto::equals(zeroToFour, oneToFour));

    ASSERT_FALSE(pluto::equals(fiveToNine, zeroToFour));
    ASSERT_FALSE(pluto::equals(fiveToNine, zeroToThree));
    ASSERT_FALSE(pluto::equals(fiveToNine, oneToFour));

    ASSERT_FALSE(pluto::equals(zeroToThree, zeroToFour));
    ASSERT_FALSE(pluto::equals(zeroToThree, fiveToNine));
    ASSERT_FALSE(pluto::equals(zeroToThree, oneToFour));

    ASSERT_FALSE(pluto::equals(oneToFour, zeroToFour));
    ASSERT_FALSE(pluto::equals(oneToFour, fiveToNine));
    ASSERT_FALSE(pluto::equals(oneToFour, zeroToThree));
}

TEST_F(ContainerUtilsTests, TestBeginsWithReturnsTrue)
{
    ASSERT_TRUE(pluto::beginsWith(empty, empty));

    ASSERT_TRUE(pluto::beginsWith(zeroToFour, zeroToFour));
    ASSERT_TRUE(pluto::beginsWith(zeroToFour, zeroToFour2));
    ASSERT_TRUE(pluto::beginsWith(zeroToFour, zeroToThree));
    ASSERT_TRUE(pluto::beginsWith(zeroToFour, zero));
}

TEST_F(ContainerUtilsTests, TestBeginsWithReturnsFalse)
{
    ASSERT_FALSE(pluto::beginsWith(zeroToFour, fiveToNine));
    ASSERT_FALSE(pluto::beginsWith(zeroToFour, oneToFour));
    ASSERT_FALSE(pluto::beginsWith(zeroToFour, one));

    ASSERT_FALSE(pluto::beginsWith(fiveToNine, zeroToFour));
    ASSERT_FALSE(pluto::beginsWith(fiveToNine, oneToFour));
    ASSERT_FALSE(pluto::beginsWith(fiveToNine, one));

    ASSERT_FALSE(pluto::beginsWith(oneToFour, zeroToFour));
    ASSERT_FALSE(pluto::beginsWith(oneToFour, fiveToNine));

    ASSERT_FALSE(pluto::beginsWith(one, zeroToFour));
    ASSERT_FALSE(pluto::beginsWith(one, fiveToNine));
    ASSERT_FALSE(pluto::beginsWith(one, oneToFour));
}

TEST_F(ContainerUtilsTests, TestEndsWithReturnsTrue)
{
    ASSERT_TRUE(pluto::endsWith(empty, empty));

    ASSERT_TRUE(pluto::endsWith(zeroToFour, zeroToFour));
    ASSERT_TRUE(pluto::endsWith(zeroToFour, zeroToFour2));
    ASSERT_TRUE(pluto::endsWith(zeroToFour, oneToFour));
    ASSERT_TRUE(pluto::endsWith(zeroToFour, four));
}

TEST_F(ContainerUtilsTests, TestEndsWithReturnsFalse)
{
    ASSERT_FALSE(pluto::endsWith(zeroToFour, fiveToNine));
    ASSERT_FALSE(pluto::endsWith(zeroToFour, zeroToThree));
    ASSERT_FALSE(pluto::endsWith(zeroToFour, three));

    ASSERT_FALSE(pluto::endsWith(fiveToNine, zeroToFour));
    ASSERT_FALSE(pluto::endsWith(fiveToNine, zeroToThree));
    ASSERT_FALSE(pluto::endsWith(fiveToNine, three));

    ASSERT_FALSE(pluto::endsWith(zeroToThree, zeroToFour));
    ASSERT_FALSE(pluto::endsWith(zeroToThree, fiveToNine));

    ASSERT_FALSE(pluto::endsWith(three, zeroToFour));
    ASSERT_FALSE(pluto::endsWith(three, fiveToNine));
    ASSERT_FALSE(pluto::endsWith(three, zeroToThree));
}

TEST_F(ContainerUtilsTests, TestFindElemReturnsPosition)
{
    ASSERT_EQ(pluto::findElem(zeroToFourTwice, 0), zeroToFourTwice.begin());
    ASSERT_EQ(pluto::findElem(zeroToFourTwice, 1), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(pluto::findElem(zeroToFourTwice, 2), zeroToFourTwice.begin() + 2);
    ASSERT_EQ(pluto::findElem(zeroToFourTwice, 3), zeroToFourTwice.begin() + 3);
    ASSERT_EQ(pluto::findElem(zeroToFourTwice, 4), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(pluto::findElem(fourZeroOne, 4), fourZeroOne.begin());
    ASSERT_EQ(pluto::findElem(fourZeroOne, 0), fourZeroOne.begin() + 1);
    ASSERT_EQ(pluto::findElem(fourZeroOne, 1), fourZeroOne.begin() + 2);
}

TEST_F(ContainerUtilsTests, TestFindElemReturnsEnd)
{
    ASSERT_EQ(pluto::findElem(empty, 0), empty.end());
    ASSERT_EQ(pluto::findElem(zeroToFourTwice, 5), zeroToFourTwice.end());
}

TEST_F(ContainerUtilsTests, TestFindSequenceReturnsPosition)
{
    ASSERT_EQ(pluto::findSequence(empty, empty), empty.begin());
    ASSERT_EQ(pluto::findSequence(zeroToFourTwice, empty), zeroToFourTwice.begin());

    ASSERT_EQ(pluto::findSequence(zeroToFourTwice, zeroToFourTwice), zeroToFourTwice.begin());
    ASSERT_EQ(pluto::findSequence(zeroToFourTwice, zeroToFourTwice2), zeroToFourTwice.begin());
    ASSERT_EQ(pluto::findSequence(zeroToFourTwice, fourZeroOne), zeroToFourTwice.begin() + 4);
    ASSERT_EQ(pluto::findSequence(zeroToFourTwice, oneToThree), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(pluto::findSequence(zeroToFourTwice, zero), zeroToFourTwice.begin());
    ASSERT_EQ(pluto::findSequence(zeroToFourTwice, four), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(pluto::findSequence(fourZeroOne, zero), fourZeroOne.begin() + 1);
    ASSERT_EQ(pluto::findSequence(fourZeroOne, four), fourZeroOne.begin());
}

TEST_F(ContainerUtilsTests, TestFindSequenceReturnsEnd)
{
    ASSERT_EQ(pluto::findSequence(zeroToFourTwice, five), zeroToFourTwice.end());
}

TEST_F(ContainerUtilsTests, TestFindIfReturnsPosition)
{
    auto equalsZero { [](int i) { return i == 0; } };
    auto equalsOne  { [](int i) { return i == 1; } };
    auto equalsTwo  { [](int i) { return i == 2; } };
    auto equalsThree{ [](int i) { return i == 3; } };
    auto equalsFour { [](int i) { return i == 4; } };

    ASSERT_EQ(pluto::findIf(zeroToFourTwice, equalsZero), zeroToFourTwice.begin());
    ASSERT_EQ(pluto::findIf(zeroToFourTwice, equalsOne), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(pluto::findIf(zeroToFourTwice, equalsTwo), zeroToFourTwice.begin() + 2);
    ASSERT_EQ(pluto::findIf(zeroToFourTwice, equalsThree), zeroToFourTwice.begin() + 3);
    ASSERT_EQ(pluto::findIf(zeroToFourTwice, equalsFour), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(pluto::findIf(fourZeroOne, equalsFour), fourZeroOne.begin());
    ASSERT_EQ(pluto::findIf(fourZeroOne, equalsZero), fourZeroOne.begin() + 1);
    ASSERT_EQ(pluto::findIf(fourZeroOne, equalsOne), fourZeroOne.begin() + 2);
}

TEST_F(ContainerUtilsTests, TestFindIfReturnsEnd)
{
    auto equalsZero{ [](int i) { return i == 0; } };
    auto equalsFive{ [](int i) { return i == 5; } };

    ASSERT_EQ(pluto::findIf(empty, equalsZero), empty.end());
    ASSERT_EQ(pluto::findIf(zeroToFourTwice, equalsFive), zeroToFourTwice.end());
}

TEST_F(ContainerUtilsTests, TestFindIfNotReturnsPosition)
{
    auto equalsZero { [](int i) { return i == 0; } };
    auto equalsOne  { [](int i) { return i == 1; } };
    auto equalsTwo  { [](int i) { return i == 2; } };
    auto equalsThree{ [](int i) { return i == 3; } };
    auto equalsFour { [](int i) { return i == 4; } };

    ASSERT_EQ(pluto::findIfNot(zeroToFourTwice, equalsZero), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(pluto::findIfNot(zeroToFourTwice, equalsOne), zeroToFourTwice.begin());
    ASSERT_EQ(pluto::findIfNot(zeroToFourTwice, equalsTwo), zeroToFourTwice.begin());
    ASSERT_EQ(pluto::findIfNot(zeroToFourTwice, equalsThree), zeroToFourTwice.begin());
    ASSERT_EQ(pluto::findIfNot(zeroToFourTwice, equalsFour), zeroToFourTwice.begin());

    ASSERT_EQ(pluto::findIfNot(fourZeroOne, equalsFour), fourZeroOne.begin() + 1);
    ASSERT_EQ(pluto::findIfNot(fourZeroOne, equalsZero), fourZeroOne.begin());
    ASSERT_EQ(pluto::findIfNot(fourZeroOne, equalsOne), fourZeroOne.begin());
}

TEST_F(ContainerUtilsTests, TestContainsElemReturnsTrue)
{
    ASSERT_TRUE(pluto::containsElem(zeroToFourTwice, 0));
    ASSERT_TRUE(pluto::containsElem(zeroToFourTwice, 1));
    ASSERT_TRUE(pluto::containsElem(zeroToFourTwice, 2));
    ASSERT_TRUE(pluto::containsElem(zeroToFourTwice, 3));
    ASSERT_TRUE(pluto::containsElem(zeroToFourTwice, 4));

    ASSERT_TRUE(pluto::containsElem(fourZeroOne, 4));
    ASSERT_TRUE(pluto::containsElem(fourZeroOne, 0));
    ASSERT_TRUE(pluto::containsElem(fourZeroOne, 1));
}

TEST_F(ContainerUtilsTests, TestContainsElemReturnsFalse)
{
    ASSERT_FALSE(pluto::containsElem(zeroToFourTwice, 5));
}

TEST_F(ContainerUtilsTests, TestContainsSequenceReturnsTrue)
{
    ASSERT_TRUE(pluto::containsSequence(empty, empty));
    ASSERT_TRUE(pluto::containsSequence(zeroToFourTwice, empty));

    ASSERT_TRUE(pluto::containsSequence(zeroToFourTwice, zeroToFourTwice));
    ASSERT_TRUE(pluto::containsSequence(zeroToFourTwice, zeroToFourTwice2));
    ASSERT_TRUE(pluto::containsSequence(zeroToFourTwice, fourZeroOne));
    ASSERT_TRUE(pluto::containsSequence(zeroToFourTwice, oneToThree));
    ASSERT_TRUE(pluto::containsSequence(zeroToFourTwice, zero));
    ASSERT_TRUE(pluto::containsSequence(zeroToFourTwice, four));

    ASSERT_TRUE(pluto::containsSequence(fourZeroOne, zero));
    ASSERT_TRUE(pluto::containsSequence(fourZeroOne, four));
}

TEST_F(ContainerUtilsTests, TestContainsSequenceReturnsFalse)
{
    ASSERT_FALSE(pluto::containsSequence(zeroToFourTwice, five));
}
