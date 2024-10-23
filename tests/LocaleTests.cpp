/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#include "generic/locale.hpp"

#include <gtest/gtest.h>

class LocaleTests : public testing::Test
{
protected:
    LocaleTests() {}
    ~LocaleTests() {}
};

TEST_F(LocaleTests, TestGetCLocale)
{
    const auto& cLocale{ Generic::get_c_locale() };
}

TEST_F(LocaleTests, TestGetSystemLocale)
{
    const auto& systemLocale{ Generic::get_system_locale() };
}

TEST_F(LocaleTests, TestGetDefaultLocale)
{
    const auto& defaultLocale{ Generic::get_default_locale() };
}

TEST_F(LocaleTests, TestGetFacet)
{
    const auto& facet{ Generic::get_facet<char>(Generic::get_default_locale()) };
}
