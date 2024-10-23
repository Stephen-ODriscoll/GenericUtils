/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#include "generic/compare.hpp"

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
#define TEST_CHAR8_ELEM_IGNORE_CASE(check, function, x, y) \
    do \
    { \
        try { check(function<char8_t>{ Generic::get_default_locale() }(u8##x, u8##y)); } catch (const std::bad_cast&) {} \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM_IGNORE_CASE(check, function, x, y) \
    do {} while (false)
#endif

#define TEST_ALL_ELEM_IGNORE_CASE(check, function, x, y) \
    do \
    { \
        check(function<char>{ Generic::get_default_locale() }(x, y)); \
        check(function<wchar_t>{ Generic::get_default_locale() }(L##x, L##y)); \
        TEST_CHAR8_ELEM_IGNORE_CASE(check, function, x, y); \
        try { check(function<char16_t>{ Generic::get_default_locale() }(u##x, u##y)); } catch (const std::bad_cast&) {} \
        try { check(function<char32_t>{ Generic::get_default_locale() }(U##x, U##y)); } catch (const std::bad_cast&) {} \
    } \
    while (false)

TEST_F(CompareTests, TestIsEqual)
{
    TEST_ALL_ELEM(ASSERT_TRUE,  Generic::is_equal{}, ' ', ' ');
    TEST_ALL_ELEM(ASSERT_TRUE,  Generic::is_equal{}, 'A', 'A');
    TEST_ALL_ELEM(ASSERT_FALSE, Generic::is_equal{}, 'a', 'A');
    TEST_ALL_ELEM(ASSERT_FALSE, Generic::is_equal{}, 'A', 'a');
    TEST_ALL_ELEM(ASSERT_TRUE,  Generic::is_equal{}, 'a', 'a');

    ASSERT_TRUE(Generic::is_equal{}(1,      1));
    ASSERT_TRUE(Generic::is_equal{}(1l,     1l));
    ASSERT_TRUE(Generic::is_equal{}(1ll,    1ll));
    ASSERT_TRUE(Generic::is_equal{}(1u,     1u));
    ASSERT_TRUE(Generic::is_equal{}(1ul,    1ul));
    ASSERT_TRUE(Generic::is_equal{}(1ull,   1ull));
    ASSERT_TRUE(Generic::is_equal{}(1.0,    1.0));
    ASSERT_TRUE(Generic::is_equal{}(1.0f,   1.0f));

    ASSERT_FALSE(Generic::is_equal{}(1,     2));
    ASSERT_FALSE(Generic::is_equal{}(1l,    2l));
    ASSERT_FALSE(Generic::is_equal{}(1ll,   2ll));
    ASSERT_FALSE(Generic::is_equal{}(1u,    2u));
    ASSERT_FALSE(Generic::is_equal{}(1ul,   2ul));
    ASSERT_FALSE(Generic::is_equal{}(1ull,  2ull));
    ASSERT_FALSE(Generic::is_equal{}(1.0,   2.0));
    ASSERT_FALSE(Generic::is_equal{}(1.0f,  2.0f));

    ASSERT_FALSE(Generic::is_equal{}(2,     1));
    ASSERT_FALSE(Generic::is_equal{}(2l,    1l));
    ASSERT_FALSE(Generic::is_equal{}(2ll,   1ll));
    ASSERT_FALSE(Generic::is_equal{}(2u,    1u));
    ASSERT_FALSE(Generic::is_equal{}(2ul,   1ul));
    ASSERT_FALSE(Generic::is_equal{}(2ull,  1ull));
    ASSERT_FALSE(Generic::is_equal{}(2.0,   1.0));
    ASSERT_FALSE(Generic::is_equal{}(2.0f,  1.0f));
}

TEST_F(CompareTests, TestIsNotEqual)
{
    TEST_ALL_ELEM(ASSERT_FALSE, Generic::is_not_equal{}, ' ', ' ');
    TEST_ALL_ELEM(ASSERT_FALSE, Generic::is_not_equal{}, 'A', 'A');
    TEST_ALL_ELEM(ASSERT_TRUE,  Generic::is_not_equal{}, 'a', 'A');
    TEST_ALL_ELEM(ASSERT_TRUE,  Generic::is_not_equal{}, 'A', 'a');
    TEST_ALL_ELEM(ASSERT_FALSE, Generic::is_not_equal{}, 'a', 'a');

    ASSERT_FALSE(   Generic::is_not_equal{} (' ', ' '));
    ASSERT_FALSE(   Generic::is_not_equal{} ('A', 'A'));
    ASSERT_TRUE(    Generic::is_not_equal{} ('a', 'A'));
    ASSERT_TRUE(    Generic::is_not_equal{} ('A', 'a'));
    ASSERT_FALSE(   Generic::is_not_equal{} ('a', 'a'));

    ASSERT_FALSE(Generic::is_not_equal{}(1,     1));
    ASSERT_FALSE(Generic::is_not_equal{}(1l,    1l));
    ASSERT_FALSE(Generic::is_not_equal{}(1ll,   1ll));
    ASSERT_FALSE(Generic::is_not_equal{}(1u,    1u));
    ASSERT_FALSE(Generic::is_not_equal{}(1ul,   1ul));
    ASSERT_FALSE(Generic::is_not_equal{}(1ull,  1ull));
    ASSERT_FALSE(Generic::is_not_equal{}(1.0,   1.0));
    ASSERT_FALSE(Generic::is_not_equal{}(1.0f,  1.0f));

    ASSERT_TRUE(Generic::is_not_equal{}(1,      2));
    ASSERT_TRUE(Generic::is_not_equal{}(1l,     2l));
    ASSERT_TRUE(Generic::is_not_equal{}(1ll,    2ll));
    ASSERT_TRUE(Generic::is_not_equal{}(1u,     2u));
    ASSERT_TRUE(Generic::is_not_equal{}(1ul,    2ul));
    ASSERT_TRUE(Generic::is_not_equal{}(1ull,   2ull));
    ASSERT_TRUE(Generic::is_not_equal{}(1.0,    2.0));
    ASSERT_TRUE(Generic::is_not_equal{}(1.0f,   2.0f));

    ASSERT_TRUE(Generic::is_not_equal{}(2,      1));
    ASSERT_TRUE(Generic::is_not_equal{}(2l,     1l));
    ASSERT_TRUE(Generic::is_not_equal{}(2ll,    1ll));
    ASSERT_TRUE(Generic::is_not_equal{}(2u,     1u));
    ASSERT_TRUE(Generic::is_not_equal{}(2ul,    1ul));
    ASSERT_TRUE(Generic::is_not_equal{}(2ull,   1ull));
    ASSERT_TRUE(Generic::is_not_equal{}(2.0,    1.0));
    ASSERT_TRUE(Generic::is_not_equal{}(2.0f,   1.0f));
}

TEST_F(CompareTests, TestIsLess)
{
    TEST_ALL_ELEM(ASSERT_FALSE, Generic::is_less{}, ' ', ' ');
    TEST_ALL_ELEM(ASSERT_FALSE, Generic::is_less{}, 'A', 'A');
    TEST_ALL_ELEM(ASSERT_FALSE, Generic::is_less{}, 'a', 'A');
    TEST_ALL_ELEM(ASSERT_TRUE,  Generic::is_less{}, 'A', 'a');
    TEST_ALL_ELEM(ASSERT_FALSE, Generic::is_less{}, 'a', 'a');

    ASSERT_FALSE(Generic::is_less{}(1,      1));
    ASSERT_FALSE(Generic::is_less{}(1l,     1l));
    ASSERT_FALSE(Generic::is_less{}(1ll,    1ll));
    ASSERT_FALSE(Generic::is_less{}(1u,     1u));
    ASSERT_FALSE(Generic::is_less{}(1ul,    1ul));
    ASSERT_FALSE(Generic::is_less{}(1ull,   1ull));
    ASSERT_FALSE(Generic::is_less{}(1.0,    1.0));
    ASSERT_FALSE(Generic::is_less{}(1.0f,   1.0f));

    ASSERT_TRUE(Generic::is_less{}(1,       2));
    ASSERT_TRUE(Generic::is_less{}(1l,      2l));
    ASSERT_TRUE(Generic::is_less{}(1ll,     2ll));
    ASSERT_TRUE(Generic::is_less{}(1u,      2u));
    ASSERT_TRUE(Generic::is_less{}(1ul,     2ul));
    ASSERT_TRUE(Generic::is_less{}(1ull,    2ull));
    ASSERT_TRUE(Generic::is_less{}(1.0,     2.0));
    ASSERT_TRUE(Generic::is_less{}(1.0f,    2.0f));

    ASSERT_FALSE(Generic::is_less{}(2,      1));
    ASSERT_FALSE(Generic::is_less{}(2l,     1l));
    ASSERT_FALSE(Generic::is_less{}(2ll,    1ll));
    ASSERT_FALSE(Generic::is_less{}(2u,     1u));
    ASSERT_FALSE(Generic::is_less{}(2ul,    1ul));
    ASSERT_FALSE(Generic::is_less{}(2ull,   1ull));
    ASSERT_FALSE(Generic::is_less{}(2.0,    1.0));
    ASSERT_FALSE(Generic::is_less{}(2.0f,   1.0f));
}

TEST_F(CompareTests, TestIsGreater)
{
    TEST_ALL_ELEM(ASSERT_FALSE, Generic::is_greater{}, ' ', ' ');
    TEST_ALL_ELEM(ASSERT_FALSE, Generic::is_greater{}, 'A', 'A');
    TEST_ALL_ELEM(ASSERT_TRUE,  Generic::is_greater{}, 'a', 'A');
    TEST_ALL_ELEM(ASSERT_FALSE, Generic::is_greater{}, 'A', 'a');
    TEST_ALL_ELEM(ASSERT_FALSE, Generic::is_greater{}, 'a', 'a');

    ASSERT_FALSE(Generic::is_greater{}(1,       1));
    ASSERT_FALSE(Generic::is_greater{}(1l,      1l));
    ASSERT_FALSE(Generic::is_greater{}(1ll,     1ll));
    ASSERT_FALSE(Generic::is_greater{}(1u,      1u));
    ASSERT_FALSE(Generic::is_greater{}(1ul,     1ul));
    ASSERT_FALSE(Generic::is_greater{}(1ull,    1ull));
    ASSERT_FALSE(Generic::is_greater{}(1.0,     1.0));
    ASSERT_FALSE(Generic::is_greater{}(1.0f,    1.0f));

    ASSERT_FALSE(Generic::is_greater{}(1,       2));
    ASSERT_FALSE(Generic::is_greater{}(1l,      2l));
    ASSERT_FALSE(Generic::is_greater{}(1ll,     2ll));
    ASSERT_FALSE(Generic::is_greater{}(1u,      2u));
    ASSERT_FALSE(Generic::is_greater{}(1ul,     2ul));
    ASSERT_FALSE(Generic::is_greater{}(1ull,    2ull));
    ASSERT_FALSE(Generic::is_greater{}(1.0,     2.0));
    ASSERT_FALSE(Generic::is_greater{}(1.0f,    2.0f));

    ASSERT_TRUE(Generic::is_greater{}(2,    1));
    ASSERT_TRUE(Generic::is_greater{}(2l,   1l));
    ASSERT_TRUE(Generic::is_greater{}(2ll,  1ll));
    ASSERT_TRUE(Generic::is_greater{}(2u,   1u));
    ASSERT_TRUE(Generic::is_greater{}(2ul,  1ul));
    ASSERT_TRUE(Generic::is_greater{}(2ull, 1ull));
    ASSERT_TRUE(Generic::is_greater{}(2.0,  1.0));
    ASSERT_TRUE(Generic::is_greater{}(2.0f, 1.0f));
}

TEST_F(CompareTests, TestIsLessEqual)
{
    TEST_ALL_ELEM(ASSERT_TRUE,  Generic::is_less_equal{}, ' ', ' ');
    TEST_ALL_ELEM(ASSERT_TRUE,  Generic::is_less_equal{}, 'A', 'A');
    TEST_ALL_ELEM(ASSERT_FALSE, Generic::is_less_equal{}, 'a', 'A');
    TEST_ALL_ELEM(ASSERT_TRUE,  Generic::is_less_equal{}, 'A', 'a');
    TEST_ALL_ELEM(ASSERT_TRUE,  Generic::is_less_equal{}, 'a', 'a');

    ASSERT_TRUE(Generic::is_less_equal{}(1,     1));
    ASSERT_TRUE(Generic::is_less_equal{}(1l,    1l));
    ASSERT_TRUE(Generic::is_less_equal{}(1ll,   1ll));
    ASSERT_TRUE(Generic::is_less_equal{}(1u,    1u));
    ASSERT_TRUE(Generic::is_less_equal{}(1ul,   1ul));
    ASSERT_TRUE(Generic::is_less_equal{}(1ull,  1ull));
    ASSERT_TRUE(Generic::is_less_equal{}(1.0,   1.0));
    ASSERT_TRUE(Generic::is_less_equal{}(1.0f,  1.0f));

    ASSERT_TRUE(Generic::is_less_equal{}(1,     2));
    ASSERT_TRUE(Generic::is_less_equal{}(1l,    2l));
    ASSERT_TRUE(Generic::is_less_equal{}(1ll,   2ll));
    ASSERT_TRUE(Generic::is_less_equal{}(1u,    2u));
    ASSERT_TRUE(Generic::is_less_equal{}(1ul,   2ul));
    ASSERT_TRUE(Generic::is_less_equal{}(1ull,  2ull));
    ASSERT_TRUE(Generic::is_less_equal{}(1.0,   2.0));
    ASSERT_TRUE(Generic::is_less_equal{}(1.0f,  2.0f));

    ASSERT_FALSE(Generic::is_less_equal{}(2,    1));
    ASSERT_FALSE(Generic::is_less_equal{}(2l,   1l));
    ASSERT_FALSE(Generic::is_less_equal{}(2ll,  1ll));
    ASSERT_FALSE(Generic::is_less_equal{}(2u,   1u));
    ASSERT_FALSE(Generic::is_less_equal{}(2ul,  1ul));
    ASSERT_FALSE(Generic::is_less_equal{}(2ull, 1ull));
    ASSERT_FALSE(Generic::is_less_equal{}(2.0,  1.0));
    ASSERT_FALSE(Generic::is_less_equal{}(2.0f, 1.0f));
}

TEST_F(CompareTests, TestIsGreaterEqual)
{
    TEST_ALL_ELEM(ASSERT_TRUE,  Generic::is_greater_equal{}, ' ', ' ');
    TEST_ALL_ELEM(ASSERT_TRUE,  Generic::is_greater_equal{}, 'A', 'A');
    TEST_ALL_ELEM(ASSERT_TRUE,  Generic::is_greater_equal{}, 'a', 'A');
    TEST_ALL_ELEM(ASSERT_FALSE, Generic::is_greater_equal{}, 'A', 'a');
    TEST_ALL_ELEM(ASSERT_TRUE,  Generic::is_greater_equal{}, 'a', 'a');

    ASSERT_TRUE(Generic::is_greater_equal{}(1,      1));
    ASSERT_TRUE(Generic::is_greater_equal{}(1l,     1l));
    ASSERT_TRUE(Generic::is_greater_equal{}(1ll,    1ll));
    ASSERT_TRUE(Generic::is_greater_equal{}(1u,     1u));
    ASSERT_TRUE(Generic::is_greater_equal{}(1ul,    1ul));
    ASSERT_TRUE(Generic::is_greater_equal{}(1ull,   1ull));
    ASSERT_TRUE(Generic::is_greater_equal{}(1.0,    1.0));
    ASSERT_TRUE(Generic::is_greater_equal{}(1.0f,   1.0f));

    ASSERT_FALSE(Generic::is_greater_equal{}(1,     2));
    ASSERT_FALSE(Generic::is_greater_equal{}(1l,    2l));
    ASSERT_FALSE(Generic::is_greater_equal{}(1ll,   2ll));
    ASSERT_FALSE(Generic::is_greater_equal{}(1u,    2u));
    ASSERT_FALSE(Generic::is_greater_equal{}(1ul,   2ul));
    ASSERT_FALSE(Generic::is_greater_equal{}(1ull,  2ull));
    ASSERT_FALSE(Generic::is_greater_equal{}(1.0,   2.0));
    ASSERT_FALSE(Generic::is_greater_equal{}(1.0f,  2.0f));

    ASSERT_TRUE(Generic::is_greater_equal{}(2,      1));
    ASSERT_TRUE(Generic::is_greater_equal{}(2l,     1l));
    ASSERT_TRUE(Generic::is_greater_equal{}(2ll,    1ll));
    ASSERT_TRUE(Generic::is_greater_equal{}(2u,     1u));
    ASSERT_TRUE(Generic::is_greater_equal{}(2ul,    1ul));
    ASSERT_TRUE(Generic::is_greater_equal{}(2ull,   1ull));
    ASSERT_TRUE(Generic::is_greater_equal{}(2.0,    1.0));
    ASSERT_TRUE(Generic::is_greater_equal{}(2.0f,   1.0f));
}

TEST_F(CompareTests, TestIsEqualIgnoreCase)
{
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_equal_ignore_case, ' ', ' ');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_equal_ignore_case, 'A', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_equal_ignore_case, 'a', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_equal_ignore_case, 'A', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_equal_ignore_case, 'a', 'a');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_equal_ignore_case, 'A', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_equal_ignore_case, 'a', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_equal_ignore_case, 'A', 'b');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_equal_ignore_case, 'a', 'b');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_equal_ignore_case, 'B', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_equal_ignore_case, 'b', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_equal_ignore_case, 'B', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_equal_ignore_case, 'b', 'a');
}

TEST_F(CompareTests, TestIsNotEqualIgnoreCase)
{
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_not_equal_ignore_case, ' ', ' ');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_not_equal_ignore_case, 'A', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_not_equal_ignore_case, 'a', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_not_equal_ignore_case, 'A', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_not_equal_ignore_case, 'a', 'a');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_not_equal_ignore_case, 'A', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_not_equal_ignore_case, 'a', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_not_equal_ignore_case, 'A', 'b');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_not_equal_ignore_case, 'a', 'b');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_not_equal_ignore_case, 'B', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_not_equal_ignore_case, 'b', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_not_equal_ignore_case, 'B', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_not_equal_ignore_case, 'b', 'a');
}

TEST_F(CompareTests, TestIsLessIgnoreCase)
{
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_less_ignore_case, ' ', ' ');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_less_ignore_case, 'A', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_less_ignore_case, 'a', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_less_ignore_case, 'A', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_less_ignore_case, 'a', 'a');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_less_ignore_case, 'A', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_less_ignore_case, 'a', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_less_ignore_case, 'A', 'b');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_less_ignore_case, 'a', 'b');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_less_ignore_case, 'B', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_less_ignore_case, 'b', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_less_ignore_case, 'B', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_less_ignore_case, 'b', 'a');
}

TEST_F(CompareTests, TestIsGreaterIgnoreCase)
{
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_greater_ignore_case, ' ', ' ');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_greater_ignore_case, 'A', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_greater_ignore_case, 'a', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_greater_ignore_case, 'A', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_greater_ignore_case, 'a', 'a');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_greater_ignore_case, 'A', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_greater_ignore_case, 'a', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_greater_ignore_case, 'A', 'b');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_greater_ignore_case, 'a', 'b');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_greater_ignore_case, 'B', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_greater_ignore_case, 'b', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_greater_ignore_case, 'B', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_greater_ignore_case, 'b', 'a');
}

TEST_F(CompareTests, TestIsLessEqualIgnoreCase)
{
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_less_equal_ignore_case, ' ', ' ');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_less_equal_ignore_case, 'A', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_less_equal_ignore_case, 'a', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_less_equal_ignore_case, 'A', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_less_equal_ignore_case, 'a', 'a');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_less_equal_ignore_case, 'A', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_less_equal_ignore_case, 'a', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_less_equal_ignore_case, 'A', 'b');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_less_equal_ignore_case, 'a', 'b');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_less_equal_ignore_case, 'B', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_less_equal_ignore_case, 'b', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_less_equal_ignore_case, 'B', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_less_equal_ignore_case, 'b', 'a');
}

TEST_F(CompareTests, TestIsGreaterEqualIgnoreCase)
{
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_greater_equal_ignore_case, ' ', ' ');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_greater_equal_ignore_case, 'A', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_greater_equal_ignore_case, 'a', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_greater_equal_ignore_case, 'A', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_greater_equal_ignore_case, 'a', 'a');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_greater_equal_ignore_case, 'A', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_greater_equal_ignore_case, 'a', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_greater_equal_ignore_case, 'A', 'b');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::is_greater_equal_ignore_case, 'a', 'b');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_greater_equal_ignore_case, 'B', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_greater_equal_ignore_case, 'b', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_greater_equal_ignore_case, 'B', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::is_greater_equal_ignore_case, 'b', 'a');
}
