/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include "Pluto/ContainerUtils.hpp"

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
    ASSERT_TRUE(Pluto::equals(empty, empty));

    ASSERT_TRUE(Pluto::equals(zeroToFour, zeroToFour));
    ASSERT_TRUE(Pluto::equals(zeroToFour, zeroToFour2));
}

TEST_F(ContainerUtilsTests, TestEqualsReturnsFalse)
{
    ASSERT_FALSE(Pluto::equals(zeroToFour, fiveToNine));
    ASSERT_FALSE(Pluto::equals(zeroToFour, zeroToThree));
    ASSERT_FALSE(Pluto::equals(zeroToFour, oneToFour));

    ASSERT_FALSE(Pluto::equals(fiveToNine, zeroToFour));
    ASSERT_FALSE(Pluto::equals(fiveToNine, zeroToThree));
    ASSERT_FALSE(Pluto::equals(fiveToNine, oneToFour));

    ASSERT_FALSE(Pluto::equals(zeroToThree, zeroToFour));
    ASSERT_FALSE(Pluto::equals(zeroToThree, fiveToNine));
    ASSERT_FALSE(Pluto::equals(zeroToThree, oneToFour));

    ASSERT_FALSE(Pluto::equals(oneToFour, zeroToFour));
    ASSERT_FALSE(Pluto::equals(oneToFour, fiveToNine));
    ASSERT_FALSE(Pluto::equals(oneToFour, zeroToThree));
}

TEST_F(ContainerUtilsTests, TestBeginsWithReturnsTrue)
{
    ASSERT_TRUE(Pluto::beginsWith(empty, empty));

    ASSERT_TRUE(Pluto::beginsWith(zeroToFour, zeroToFour));
    ASSERT_TRUE(Pluto::beginsWith(zeroToFour, zeroToFour2));
    ASSERT_TRUE(Pluto::beginsWith(zeroToFour, zeroToThree));
    ASSERT_TRUE(Pluto::beginsWith(zeroToFour, zero));
}

TEST_F(ContainerUtilsTests, TestBeginsWithReturnsFalse)
{
    ASSERT_FALSE(Pluto::beginsWith(zeroToFour, fiveToNine));
    ASSERT_FALSE(Pluto::beginsWith(zeroToFour, oneToFour));
    ASSERT_FALSE(Pluto::beginsWith(zeroToFour, one));

    ASSERT_FALSE(Pluto::beginsWith(fiveToNine, zeroToFour));
    ASSERT_FALSE(Pluto::beginsWith(fiveToNine, oneToFour));
    ASSERT_FALSE(Pluto::beginsWith(fiveToNine, one));

    ASSERT_FALSE(Pluto::beginsWith(oneToFour, zeroToFour));
    ASSERT_FALSE(Pluto::beginsWith(oneToFour, fiveToNine));

    ASSERT_FALSE(Pluto::beginsWith(one, zeroToFour));
    ASSERT_FALSE(Pluto::beginsWith(one, fiveToNine));
    ASSERT_FALSE(Pluto::beginsWith(one, oneToFour));
}

TEST_F(ContainerUtilsTests, TestEndsWithReturnsTrue)
{
    ASSERT_TRUE(Pluto::endsWith(empty, empty));

    ASSERT_TRUE(Pluto::endsWith(zeroToFour, zeroToFour));
    ASSERT_TRUE(Pluto::endsWith(zeroToFour, zeroToFour2));
    ASSERT_TRUE(Pluto::endsWith(zeroToFour, oneToFour));
    ASSERT_TRUE(Pluto::endsWith(zeroToFour, four));
}

TEST_F(ContainerUtilsTests, TestEndsWithReturnsFalse)
{
    ASSERT_FALSE(Pluto::endsWith(zeroToFour, fiveToNine));
    ASSERT_FALSE(Pluto::endsWith(zeroToFour, zeroToThree));
    ASSERT_FALSE(Pluto::endsWith(zeroToFour, three));

    ASSERT_FALSE(Pluto::endsWith(fiveToNine, zeroToFour));
    ASSERT_FALSE(Pluto::endsWith(fiveToNine, zeroToThree));
    ASSERT_FALSE(Pluto::endsWith(fiveToNine, three));

    ASSERT_FALSE(Pluto::endsWith(zeroToThree, zeroToFour));
    ASSERT_FALSE(Pluto::endsWith(zeroToThree, fiveToNine));

    ASSERT_FALSE(Pluto::endsWith(three, zeroToFour));
    ASSERT_FALSE(Pluto::endsWith(three, fiveToNine));
    ASSERT_FALSE(Pluto::endsWith(three, zeroToThree));
}

TEST_F(ContainerUtilsTests, TestFindElemReturnsPosition)
{
    ASSERT_EQ(Pluto::findElem(zeroToFourTwice, 0), zeroToFourTwice.begin());
    ASSERT_EQ(Pluto::findElem(zeroToFourTwice, 1), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(Pluto::findElem(zeroToFourTwice, 2), zeroToFourTwice.begin() + 2);
    ASSERT_EQ(Pluto::findElem(zeroToFourTwice, 3), zeroToFourTwice.begin() + 3);
    ASSERT_EQ(Pluto::findElem(zeroToFourTwice, 4), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(Pluto::findElem(fourZeroOne, 4), fourZeroOne.begin());
    ASSERT_EQ(Pluto::findElem(fourZeroOne, 0), fourZeroOne.begin() + 1);
    ASSERT_EQ(Pluto::findElem(fourZeroOne, 1), fourZeroOne.begin() + 2);
}

TEST_F(ContainerUtilsTests, TestFindElemReturnsEnd)
{
    ASSERT_EQ(Pluto::findElem(empty, 0), empty.end());
    ASSERT_EQ(Pluto::findElem(zeroToFourTwice, 5), zeroToFourTwice.end());
}

TEST_F(ContainerUtilsTests, TestFindSequenceReturnsPosition)
{
    ASSERT_EQ(Pluto::findSequence(empty, empty), empty.begin());
    ASSERT_EQ(Pluto::findSequence(zeroToFourTwice, empty), zeroToFourTwice.begin());

    ASSERT_EQ(Pluto::findSequence(zeroToFourTwice, zeroToFourTwice), zeroToFourTwice.begin());
    ASSERT_EQ(Pluto::findSequence(zeroToFourTwice, zeroToFourTwice2), zeroToFourTwice.begin());
    ASSERT_EQ(Pluto::findSequence(zeroToFourTwice, fourZeroOne), zeroToFourTwice.begin() + 4);
    ASSERT_EQ(Pluto::findSequence(zeroToFourTwice, oneToThree), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(Pluto::findSequence(zeroToFourTwice, zero), zeroToFourTwice.begin());
    ASSERT_EQ(Pluto::findSequence(zeroToFourTwice, four), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(Pluto::findSequence(fourZeroOne, zero), fourZeroOne.begin() + 1);
    ASSERT_EQ(Pluto::findSequence(fourZeroOne, four), fourZeroOne.begin());
}

TEST_F(ContainerUtilsTests, TestFindSequenceReturnsEnd)
{
    ASSERT_EQ(Pluto::findSequence(zeroToFourTwice, five), zeroToFourTwice.end());
}

TEST_F(ContainerUtilsTests, TestFindIfReturnsPosition)
{
    auto equalsZero { [](int i) { return i == 0; } };
    auto equalsOne  { [](int i) { return i == 1; } };
    auto equalsTwo  { [](int i) { return i == 2; } };
    auto equalsThree{ [](int i) { return i == 3; } };
    auto equalsFour { [](int i) { return i == 4; } };

    ASSERT_EQ(Pluto::findIf(zeroToFourTwice, equalsZero), zeroToFourTwice.begin());
    ASSERT_EQ(Pluto::findIf(zeroToFourTwice, equalsOne), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(Pluto::findIf(zeroToFourTwice, equalsTwo), zeroToFourTwice.begin() + 2);
    ASSERT_EQ(Pluto::findIf(zeroToFourTwice, equalsThree), zeroToFourTwice.begin() + 3);
    ASSERT_EQ(Pluto::findIf(zeroToFourTwice, equalsFour), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(Pluto::findIf(fourZeroOne, equalsFour), fourZeroOne.begin());
    ASSERT_EQ(Pluto::findIf(fourZeroOne, equalsZero), fourZeroOne.begin() + 1);
    ASSERT_EQ(Pluto::findIf(fourZeroOne, equalsOne), fourZeroOne.begin() + 2);
}

TEST_F(ContainerUtilsTests, TestFindIfReturnsEnd)
{
    auto equalsZero{ [](int i) { return i == 0; } };
    auto equalsFive{ [](int i) { return i == 5; } };

    ASSERT_EQ(Pluto::findIf(empty, equalsZero), empty.end());
    ASSERT_EQ(Pluto::findIf(zeroToFourTwice, equalsFive), zeroToFourTwice.end());
}

TEST_F(ContainerUtilsTests, TestFindIfNotReturnsPosition)
{
    auto equalsZero { [](int i) { return i == 0; } };
    auto equalsOne  { [](int i) { return i == 1; } };
    auto equalsTwo  { [](int i) { return i == 2; } };
    auto equalsThree{ [](int i) { return i == 3; } };
    auto equalsFour { [](int i) { return i == 4; } };

    ASSERT_EQ(Pluto::findIfNot(zeroToFourTwice, equalsZero), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(Pluto::findIfNot(zeroToFourTwice, equalsOne), zeroToFourTwice.begin());
    ASSERT_EQ(Pluto::findIfNot(zeroToFourTwice, equalsTwo), zeroToFourTwice.begin());
    ASSERT_EQ(Pluto::findIfNot(zeroToFourTwice, equalsThree), zeroToFourTwice.begin());
    ASSERT_EQ(Pluto::findIfNot(zeroToFourTwice, equalsFour), zeroToFourTwice.begin());

    ASSERT_EQ(Pluto::findIfNot(fourZeroOne, equalsFour), fourZeroOne.begin() + 1);
    ASSERT_EQ(Pluto::findIfNot(fourZeroOne, equalsZero), fourZeroOne.begin());
    ASSERT_EQ(Pluto::findIfNot(fourZeroOne, equalsOne), fourZeroOne.begin());
}

TEST_F(ContainerUtilsTests, TestContainsElemReturnsTrue)
{
    ASSERT_TRUE(Pluto::containsElem(zeroToFourTwice, 0));
    ASSERT_TRUE(Pluto::containsElem(zeroToFourTwice, 1));
    ASSERT_TRUE(Pluto::containsElem(zeroToFourTwice, 2));
    ASSERT_TRUE(Pluto::containsElem(zeroToFourTwice, 3));
    ASSERT_TRUE(Pluto::containsElem(zeroToFourTwice, 4));

    ASSERT_TRUE(Pluto::containsElem(fourZeroOne, 4));
    ASSERT_TRUE(Pluto::containsElem(fourZeroOne, 0));
    ASSERT_TRUE(Pluto::containsElem(fourZeroOne, 1));
}

TEST_F(ContainerUtilsTests, TestContainsElemReturnsFalse)
{
    ASSERT_FALSE(Pluto::containsElem(zeroToFourTwice, 5));
}

TEST_F(ContainerUtilsTests, TestContainsSequenceReturnsTrue)
{
    ASSERT_TRUE(Pluto::containsSequence(empty, empty));
    ASSERT_TRUE(Pluto::containsSequence(zeroToFourTwice, empty));

    ASSERT_TRUE(Pluto::containsSequence(zeroToFourTwice, zeroToFourTwice));
    ASSERT_TRUE(Pluto::containsSequence(zeroToFourTwice, zeroToFourTwice2));
    ASSERT_TRUE(Pluto::containsSequence(zeroToFourTwice, fourZeroOne));
    ASSERT_TRUE(Pluto::containsSequence(zeroToFourTwice, oneToThree));
    ASSERT_TRUE(Pluto::containsSequence(zeroToFourTwice, zero));
    ASSERT_TRUE(Pluto::containsSequence(zeroToFourTwice, four));

    ASSERT_TRUE(Pluto::containsSequence(fourZeroOne, zero));
    ASSERT_TRUE(Pluto::containsSequence(fourZeroOne, four));
}

TEST_F(ContainerUtilsTests, TestContainsSequenceReturnsFalse)
{
    ASSERT_FALSE(Pluto::containsSequence(zeroToFourTwice, five));
}
