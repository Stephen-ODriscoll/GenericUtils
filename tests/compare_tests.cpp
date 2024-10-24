/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include "pluto/compare.hpp"

#include <gtest/gtest.h>

class CompareTests : public testing::Test
{
protected:
    CompareTests() {}
    ~CompareTests() {}
};

#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
#define TEST_CHAR8_ELEM(check, function, x, y) \
    do \
    { \
        try { check(function(u8##x, u8##y)); } catch (const std::bad_cast&) {} \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM(check, function, x, y) \
    do {} while (false)
#endif

#define TEST_ALL_ELEM(check, function, x, y) \
    do \
    { \
        check(function(x, y)); \
        check(function(L##x, L##y)); \
        TEST_CHAR8_ELEM(check, function, x, y); \
        try { check(function(u##x, u##y)); } catch (const std::bad_cast&) {} \
        try { check(function(U##x, U##y)); } catch (const std::bad_cast&) {} \
    } \
    while (false)

#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
#define TEST_CHAR8_ELEM_IGNORE_CASE(check, function, x, y, z) \
    do \
    { \
        try { check(function<char8_t>(x)(u8##y, u8##z)); } catch (const std::bad_cast&) {} \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM_IGNORE_CASE(check, function, x, y, z) \
    do {} while (false)
#endif

#define TEST_ALL_ELEM_IGNORE_CASE(check, function, x, y, z) \
    do \
    { \
        check(function<char>(x)(y, z)); \
        check(function<wchar_t>(x)(L##y, L##z)); \
        TEST_CHAR8_ELEM_IGNORE_CASE(check, function, x, y, z); \
        try { check(function<char16_t>(x)(u##y, u##z)); } catch (const std::bad_cast&) {} \
        try { check(function<char32_t>(x)(U##y, U##z)); } catch (const std::bad_cast&) {} \
    } \
    while (false)

TEST_F(CompareTests, TestIsEqual)
{
    TEST_ALL_ELEM(ASSERT_TRUE,  pluto::IsEqual(), ' ', ' ');
    TEST_ALL_ELEM(ASSERT_TRUE,  pluto::IsEqual(), 'A', 'A');
    TEST_ALL_ELEM(ASSERT_FALSE, pluto::IsEqual(), 'a', 'A');
    TEST_ALL_ELEM(ASSERT_FALSE, pluto::IsEqual(), 'A', 'a');
    TEST_ALL_ELEM(ASSERT_TRUE,  pluto::IsEqual(), 'a', 'a');

    ASSERT_TRUE(pluto::IsEqual()(1,       1));
    ASSERT_TRUE(pluto::IsEqual()(1l,      1l));
    ASSERT_TRUE(pluto::IsEqual()(1ll,     1ll));
    ASSERT_TRUE(pluto::IsEqual()(1u,      1u));
    ASSERT_TRUE(pluto::IsEqual()(1ul,     1ul));
    ASSERT_TRUE(pluto::IsEqual()(1ull,    1ull));
    ASSERT_TRUE(pluto::IsEqual()(1.0,     1.0));
    ASSERT_TRUE(pluto::IsEqual()(1.0f,    1.0f));

    ASSERT_FALSE(pluto::IsEqual()(1,      2));
    ASSERT_FALSE(pluto::IsEqual()(1l,     2l));
    ASSERT_FALSE(pluto::IsEqual()(1ll,    2ll));
    ASSERT_FALSE(pluto::IsEqual()(1u,     2u));
    ASSERT_FALSE(pluto::IsEqual()(1ul,    2ul));
    ASSERT_FALSE(pluto::IsEqual()(1ull,   2ull));
    ASSERT_FALSE(pluto::IsEqual()(1.0,    2.0));
    ASSERT_FALSE(pluto::IsEqual()(1.0f,   2.0f));

    ASSERT_FALSE(pluto::IsEqual()(2,      1));
    ASSERT_FALSE(pluto::IsEqual()(2l,     1l));
    ASSERT_FALSE(pluto::IsEqual()(2ll,    1ll));
    ASSERT_FALSE(pluto::IsEqual()(2u,     1u));
    ASSERT_FALSE(pluto::IsEqual()(2ul,    1ul));
    ASSERT_FALSE(pluto::IsEqual()(2ull,   1ull));
    ASSERT_FALSE(pluto::IsEqual()(2.0,    1.0));
    ASSERT_FALSE(pluto::IsEqual()(2.0f,   1.0f));
}

TEST_F(CompareTests, TestIsNotEqual)
{
    TEST_ALL_ELEM(ASSERT_FALSE, pluto::IsNotEqual(), ' ', ' ');
    TEST_ALL_ELEM(ASSERT_FALSE, pluto::IsNotEqual(), 'A', 'A');
    TEST_ALL_ELEM(ASSERT_TRUE,  pluto::IsNotEqual(), 'a', 'A');
    TEST_ALL_ELEM(ASSERT_TRUE,  pluto::IsNotEqual(), 'A', 'a');
    TEST_ALL_ELEM(ASSERT_FALSE, pluto::IsNotEqual(), 'a', 'a');

    ASSERT_FALSE(pluto::IsNotEqual()  (' ', ' '));
    ASSERT_FALSE(pluto::IsNotEqual()  ('A', 'A'));
    ASSERT_TRUE(pluto::IsNotEqual()   ('a', 'A'));
    ASSERT_TRUE(pluto::IsNotEqual()   ('A', 'a'));
    ASSERT_FALSE(pluto::IsNotEqual()  ('a', 'a'));

    ASSERT_FALSE(pluto::IsNotEqual()(1,       1));
    ASSERT_FALSE(pluto::IsNotEqual()(1l,      1l));
    ASSERT_FALSE(pluto::IsNotEqual()(1ll,     1ll));
    ASSERT_FALSE(pluto::IsNotEqual()(1u,      1u));
    ASSERT_FALSE(pluto::IsNotEqual()(1ul,     1ul));
    ASSERT_FALSE(pluto::IsNotEqual()(1ull,    1ull));
    ASSERT_FALSE(pluto::IsNotEqual()(1.0,     1.0));
    ASSERT_FALSE(pluto::IsNotEqual()(1.0f,    1.0f));

    ASSERT_TRUE(pluto::IsNotEqual()(1,    2));
    ASSERT_TRUE(pluto::IsNotEqual()(1l,   2l));
    ASSERT_TRUE(pluto::IsNotEqual()(1ll,  2ll));
    ASSERT_TRUE(pluto::IsNotEqual()(1u,   2u));
    ASSERT_TRUE(pluto::IsNotEqual()(1ul,  2ul));
    ASSERT_TRUE(pluto::IsNotEqual()(1ull, 2ull));
    ASSERT_TRUE(pluto::IsNotEqual()(1.0,  2.0));
    ASSERT_TRUE(pluto::IsNotEqual()(1.0f, 2.0f));

    ASSERT_TRUE(pluto::IsNotEqual()(2,    1));
    ASSERT_TRUE(pluto::IsNotEqual()(2l,   1l));
    ASSERT_TRUE(pluto::IsNotEqual()(2ll,  1ll));
    ASSERT_TRUE(pluto::IsNotEqual()(2u,   1u));
    ASSERT_TRUE(pluto::IsNotEqual()(2ul,  1ul));
    ASSERT_TRUE(pluto::IsNotEqual()(2ull, 1ull));
    ASSERT_TRUE(pluto::IsNotEqual()(2.0,  1.0));
    ASSERT_TRUE(pluto::IsNotEqual()(2.0f, 1.0f));
}

TEST_F(CompareTests, TestIsLess)
{
    TEST_ALL_ELEM(ASSERT_FALSE, pluto::IsLess(), ' ', ' ');
    TEST_ALL_ELEM(ASSERT_FALSE, pluto::IsLess(), 'A', 'A');
    TEST_ALL_ELEM(ASSERT_FALSE, pluto::IsLess(), 'a', 'A');
    TEST_ALL_ELEM(ASSERT_TRUE,  pluto::IsLess(), 'A', 'a');
    TEST_ALL_ELEM(ASSERT_FALSE, pluto::IsLess(), 'a', 'a');

    ASSERT_FALSE(pluto::IsLess()(1,       1));
    ASSERT_FALSE(pluto::IsLess()(1l,      1l));
    ASSERT_FALSE(pluto::IsLess()(1ll,     1ll));
    ASSERT_FALSE(pluto::IsLess()(1u,      1u));
    ASSERT_FALSE(pluto::IsLess()(1ul,     1ul));
    ASSERT_FALSE(pluto::IsLess()(1ull,    1ull));
    ASSERT_FALSE(pluto::IsLess()(1.0,     1.0));
    ASSERT_FALSE(pluto::IsLess()(1.0f,    1.0f));

    ASSERT_TRUE(pluto::IsLess()(1,    2));
    ASSERT_TRUE(pluto::IsLess()(1l,   2l));
    ASSERT_TRUE(pluto::IsLess()(1ll,  2ll));
    ASSERT_TRUE(pluto::IsLess()(1u,   2u));
    ASSERT_TRUE(pluto::IsLess()(1ul,  2ul));
    ASSERT_TRUE(pluto::IsLess()(1ull, 2ull));
    ASSERT_TRUE(pluto::IsLess()(1.0,  2.0));
    ASSERT_TRUE(pluto::IsLess()(1.0f, 2.0f));

    ASSERT_FALSE(pluto::IsLess()(2,       1));
    ASSERT_FALSE(pluto::IsLess()(2l,      1l));
    ASSERT_FALSE(pluto::IsLess()(2ll,     1ll));
    ASSERT_FALSE(pluto::IsLess()(2u,      1u));
    ASSERT_FALSE(pluto::IsLess()(2ul,     1ul));
    ASSERT_FALSE(pluto::IsLess()(2ull,    1ull));
    ASSERT_FALSE(pluto::IsLess()(2.0,     1.0));
    ASSERT_FALSE(pluto::IsLess()(2.0f,    1.0f));
}

TEST_F(CompareTests, TestIsGreater)
{
    TEST_ALL_ELEM(ASSERT_FALSE, pluto::IsGreater(), ' ', ' ');
    TEST_ALL_ELEM(ASSERT_FALSE, pluto::IsGreater(), 'A', 'A');
    TEST_ALL_ELEM(ASSERT_TRUE,  pluto::IsGreater(), 'a', 'A');
    TEST_ALL_ELEM(ASSERT_FALSE, pluto::IsGreater(), 'A', 'a');
    TEST_ALL_ELEM(ASSERT_FALSE, pluto::IsGreater(), 'a', 'a');

    ASSERT_FALSE(pluto::IsGreater()(1,    1));
    ASSERT_FALSE(pluto::IsGreater()(1l,   1l));
    ASSERT_FALSE(pluto::IsGreater()(1ll,  1ll));
    ASSERT_FALSE(pluto::IsGreater()(1u,   1u));
    ASSERT_FALSE(pluto::IsGreater()(1ul,  1ul));
    ASSERT_FALSE(pluto::IsGreater()(1ull, 1ull));
    ASSERT_FALSE(pluto::IsGreater()(1.0,  1.0));
    ASSERT_FALSE(pluto::IsGreater()(1.0f, 1.0f));

    ASSERT_FALSE(pluto::IsGreater()(1,    2));
    ASSERT_FALSE(pluto::IsGreater()(1l,   2l));
    ASSERT_FALSE(pluto::IsGreater()(1ll,  2ll));
    ASSERT_FALSE(pluto::IsGreater()(1u,   2u));
    ASSERT_FALSE(pluto::IsGreater()(1ul,  2ul));
    ASSERT_FALSE(pluto::IsGreater()(1ull, 2ull));
    ASSERT_FALSE(pluto::IsGreater()(1.0,  2.0));
    ASSERT_FALSE(pluto::IsGreater()(1.0f, 2.0f));

    ASSERT_TRUE(pluto::IsGreater()(2,     1));
    ASSERT_TRUE(pluto::IsGreater()(2l,    1l));
    ASSERT_TRUE(pluto::IsGreater()(2ll,   1ll));
    ASSERT_TRUE(pluto::IsGreater()(2u,    1u));
    ASSERT_TRUE(pluto::IsGreater()(2ul,   1ul));
    ASSERT_TRUE(pluto::IsGreater()(2ull,  1ull));
    ASSERT_TRUE(pluto::IsGreater()(2.0,   1.0));
    ASSERT_TRUE(pluto::IsGreater()(2.0f,  1.0f));
}

TEST_F(CompareTests, TestIsLessEqual)
{
    TEST_ALL_ELEM(ASSERT_TRUE,  pluto::IsLessEqual(), ' ', ' ');
    TEST_ALL_ELEM(ASSERT_TRUE,  pluto::IsLessEqual(), 'A', 'A');
    TEST_ALL_ELEM(ASSERT_FALSE, pluto::IsLessEqual(), 'a', 'A');
    TEST_ALL_ELEM(ASSERT_TRUE,  pluto::IsLessEqual(), 'A', 'a');
    TEST_ALL_ELEM(ASSERT_TRUE,  pluto::IsLessEqual(), 'a', 'a');

    ASSERT_TRUE(pluto::IsLessEqual()(1,       1));
    ASSERT_TRUE(pluto::IsLessEqual()(1l,      1l));
    ASSERT_TRUE(pluto::IsLessEqual()(1ll,     1ll));
    ASSERT_TRUE(pluto::IsLessEqual()(1u,      1u));
    ASSERT_TRUE(pluto::IsLessEqual()(1ul,     1ul));
    ASSERT_TRUE(pluto::IsLessEqual()(1ull,    1ull));
    ASSERT_TRUE(pluto::IsLessEqual()(1.0,     1.0));
    ASSERT_TRUE(pluto::IsLessEqual()(1.0f,    1.0f));

    ASSERT_TRUE(pluto::IsLessEqual()(1,       2));
    ASSERT_TRUE(pluto::IsLessEqual()(1l,      2l));
    ASSERT_TRUE(pluto::IsLessEqual()(1ll,     2ll));
    ASSERT_TRUE(pluto::IsLessEqual()(1u,      2u));
    ASSERT_TRUE(pluto::IsLessEqual()(1ul,     2ul));
    ASSERT_TRUE(pluto::IsLessEqual()(1ull,    2ull));
    ASSERT_TRUE(pluto::IsLessEqual()(1.0,     2.0));
    ASSERT_TRUE(pluto::IsLessEqual()(1.0f,    2.0f));

    ASSERT_FALSE(pluto::IsLessEqual()(2,      1));
    ASSERT_FALSE(pluto::IsLessEqual()(2l,     1l));
    ASSERT_FALSE(pluto::IsLessEqual()(2ll,    1ll));
    ASSERT_FALSE(pluto::IsLessEqual()(2u,     1u));
    ASSERT_FALSE(pluto::IsLessEqual()(2ul,    1ul));
    ASSERT_FALSE(pluto::IsLessEqual()(2ull,   1ull));
    ASSERT_FALSE(pluto::IsLessEqual()(2.0,    1.0));
    ASSERT_FALSE(pluto::IsLessEqual()(2.0f,   1.0f));
}

TEST_F(CompareTests, TestIsGreaterEqual)
{
    TEST_ALL_ELEM(ASSERT_TRUE,  pluto::IsGreaterEqual(), ' ', ' ');
    TEST_ALL_ELEM(ASSERT_TRUE,  pluto::IsGreaterEqual(), 'A', 'A');
    TEST_ALL_ELEM(ASSERT_TRUE,  pluto::IsGreaterEqual(), 'a', 'A');
    TEST_ALL_ELEM(ASSERT_FALSE, pluto::IsGreaterEqual(), 'A', 'a');
    TEST_ALL_ELEM(ASSERT_TRUE,  pluto::IsGreaterEqual(), 'a', 'a');

    ASSERT_TRUE(pluto::IsGreaterEqual()(1,    1));
    ASSERT_TRUE(pluto::IsGreaterEqual()(1l,   1l));
    ASSERT_TRUE(pluto::IsGreaterEqual()(1ll,  1ll));
    ASSERT_TRUE(pluto::IsGreaterEqual()(1u,   1u));
    ASSERT_TRUE(pluto::IsGreaterEqual()(1ul,  1ul));
    ASSERT_TRUE(pluto::IsGreaterEqual()(1ull, 1ull));
    ASSERT_TRUE(pluto::IsGreaterEqual()(1.0,  1.0));
    ASSERT_TRUE(pluto::IsGreaterEqual()(1.0f, 1.0f));

    ASSERT_FALSE(pluto::IsGreaterEqual()(1,       2));
    ASSERT_FALSE(pluto::IsGreaterEqual()(1l,      2l));
    ASSERT_FALSE(pluto::IsGreaterEqual()(1ll,     2ll));
    ASSERT_FALSE(pluto::IsGreaterEqual()(1u,      2u));
    ASSERT_FALSE(pluto::IsGreaterEqual()(1ul,     2ul));
    ASSERT_FALSE(pluto::IsGreaterEqual()(1ull,    2ull));
    ASSERT_FALSE(pluto::IsGreaterEqual()(1.0,     2.0));
    ASSERT_FALSE(pluto::IsGreaterEqual()(1.0f,    2.0f));

    ASSERT_TRUE(pluto::IsGreaterEqual()(2,    1));
    ASSERT_TRUE(pluto::IsGreaterEqual()(2l,   1l));
    ASSERT_TRUE(pluto::IsGreaterEqual()(2ll,  1ll));
    ASSERT_TRUE(pluto::IsGreaterEqual()(2u,   1u));
    ASSERT_TRUE(pluto::IsGreaterEqual()(2ul,  1ul));
    ASSERT_TRUE(pluto::IsGreaterEqual()(2ull, 1ull));
    ASSERT_TRUE(pluto::IsGreaterEqual()(2.0,  1.0));
    ASSERT_TRUE(pluto::IsGreaterEqual()(2.0f, 1.0f));
}

TEST_F(CompareTests, TestIsEqualIgnoreCase)
{
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsEqualIgnoreCase, pluto::getDefaultLocale(), ' ', ' ');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsEqualIgnoreCase, pluto::getDefaultLocale(), 'A', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsEqualIgnoreCase, pluto::getDefaultLocale(), 'a', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsEqualIgnoreCase, pluto::getDefaultLocale(), 'A', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsEqualIgnoreCase, pluto::getDefaultLocale(), 'a', 'a');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsEqualIgnoreCase, pluto::getDefaultLocale(), 'A', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsEqualIgnoreCase, pluto::getDefaultLocale(), 'a', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsEqualIgnoreCase, pluto::getDefaultLocale(), 'A', 'b');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsEqualIgnoreCase, pluto::getDefaultLocale(), 'a', 'b');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsEqualIgnoreCase, pluto::getDefaultLocale(), 'B', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsEqualIgnoreCase, pluto::getDefaultLocale(), 'b', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsEqualIgnoreCase, pluto::getDefaultLocale(), 'B', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsEqualIgnoreCase, pluto::getDefaultLocale(), 'b', 'a');
}

TEST_F(CompareTests, TestIsNotEqualIgnoreCase)
{
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsNotEqualIgnoreCase, pluto::getDefaultLocale(), ' ', ' ');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsNotEqualIgnoreCase, pluto::getDefaultLocale(), 'A', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsNotEqualIgnoreCase, pluto::getDefaultLocale(), 'a', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsNotEqualIgnoreCase, pluto::getDefaultLocale(), 'A', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsNotEqualIgnoreCase, pluto::getDefaultLocale(), 'a', 'a');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsNotEqualIgnoreCase, pluto::getDefaultLocale(), 'A', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsNotEqualIgnoreCase, pluto::getDefaultLocale(), 'a', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsNotEqualIgnoreCase, pluto::getDefaultLocale(), 'A', 'b');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsNotEqualIgnoreCase, pluto::getDefaultLocale(), 'a', 'b');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsNotEqualIgnoreCase, pluto::getDefaultLocale(), 'B', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsNotEqualIgnoreCase, pluto::getDefaultLocale(), 'b', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsNotEqualIgnoreCase, pluto::getDefaultLocale(), 'B', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsNotEqualIgnoreCase, pluto::getDefaultLocale(), 'b', 'a');
}

TEST_F(CompareTests, TestIsLessIgnoreCase)
{
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsLessIgnoreCase, pluto::getDefaultLocale(), ' ', ' ');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsLessIgnoreCase, pluto::getDefaultLocale(), 'A', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsLessIgnoreCase, pluto::getDefaultLocale(), 'a', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsLessIgnoreCase, pluto::getDefaultLocale(), 'A', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsLessIgnoreCase, pluto::getDefaultLocale(), 'a', 'a');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsLessIgnoreCase, pluto::getDefaultLocale(), 'A', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsLessIgnoreCase, pluto::getDefaultLocale(), 'a', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsLessIgnoreCase, pluto::getDefaultLocale(), 'A', 'b');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsLessIgnoreCase, pluto::getDefaultLocale(), 'a', 'b');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsLessIgnoreCase, pluto::getDefaultLocale(), 'B', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsLessIgnoreCase, pluto::getDefaultLocale(), 'b', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsLessIgnoreCase, pluto::getDefaultLocale(), 'B', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsLessIgnoreCase, pluto::getDefaultLocale(), 'b', 'a');
}

TEST_F(CompareTests, TestIsGreaterIgnoreCase)
{
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsGreaterIgnoreCase, pluto::getDefaultLocale(), ' ', ' ');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsGreaterIgnoreCase, pluto::getDefaultLocale(), 'A', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsGreaterIgnoreCase, pluto::getDefaultLocale(), 'a', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsGreaterIgnoreCase, pluto::getDefaultLocale(), 'A', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsGreaterIgnoreCase, pluto::getDefaultLocale(), 'a', 'a');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsGreaterIgnoreCase, pluto::getDefaultLocale(), 'A', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsGreaterIgnoreCase, pluto::getDefaultLocale(), 'a', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsGreaterIgnoreCase, pluto::getDefaultLocale(), 'A', 'b');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsGreaterIgnoreCase, pluto::getDefaultLocale(), 'a', 'b');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsGreaterIgnoreCase, pluto::getDefaultLocale(), 'B', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsGreaterIgnoreCase, pluto::getDefaultLocale(), 'b', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsGreaterIgnoreCase, pluto::getDefaultLocale(), 'B', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsGreaterIgnoreCase, pluto::getDefaultLocale(), 'b', 'a');
}

TEST_F(CompareTests, TestIsLessEqualIgnoreCase)
{
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsLessEqualIgnoreCase, pluto::getDefaultLocale(), ' ', ' ');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsLessEqualIgnoreCase, pluto::getDefaultLocale(), 'A', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsLessEqualIgnoreCase, pluto::getDefaultLocale(), 'a', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsLessEqualIgnoreCase, pluto::getDefaultLocale(), 'A', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsLessEqualIgnoreCase, pluto::getDefaultLocale(), 'a', 'a');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsLessEqualIgnoreCase, pluto::getDefaultLocale(), 'A', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsLessEqualIgnoreCase, pluto::getDefaultLocale(), 'a', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsLessEqualIgnoreCase, pluto::getDefaultLocale(), 'A', 'b');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsLessEqualIgnoreCase, pluto::getDefaultLocale(), 'a', 'b');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsLessEqualIgnoreCase, pluto::getDefaultLocale(), 'B', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsLessEqualIgnoreCase, pluto::getDefaultLocale(), 'b', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsLessEqualIgnoreCase, pluto::getDefaultLocale(), 'B', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsLessEqualIgnoreCase, pluto::getDefaultLocale(), 'b', 'a');
}

TEST_F(CompareTests, TestIsGreaterEqualIgnoreCase)
{
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsGreaterEqualIgnoreCase, pluto::getDefaultLocale(), ' ', ' ');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsGreaterEqualIgnoreCase, pluto::getDefaultLocale(), 'A', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsGreaterEqualIgnoreCase, pluto::getDefaultLocale(), 'a', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsGreaterEqualIgnoreCase, pluto::getDefaultLocale(), 'A', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsGreaterEqualIgnoreCase, pluto::getDefaultLocale(), 'a', 'a');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsGreaterEqualIgnoreCase, pluto::getDefaultLocale(), 'A', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsGreaterEqualIgnoreCase, pluto::getDefaultLocale(), 'a', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsGreaterEqualIgnoreCase, pluto::getDefaultLocale(), 'A', 'b');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, pluto::IsGreaterEqualIgnoreCase, pluto::getDefaultLocale(), 'a', 'b');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsGreaterEqualIgnoreCase, pluto::getDefaultLocale(), 'B', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsGreaterEqualIgnoreCase, pluto::getDefaultLocale(), 'b', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsGreaterEqualIgnoreCase, pluto::getDefaultLocale(), 'B', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, pluto::IsGreaterEqualIgnoreCase, pluto::getDefaultLocale(), 'b', 'a');
}
