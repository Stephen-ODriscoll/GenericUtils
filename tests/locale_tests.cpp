/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include "pluto/locale.hpp"

#include <gtest/gtest.h>

class LocaleTests : public testing::Test
{
protected:
    LocaleTests() {}
    ~LocaleTests() {}
};

TEST_F(LocaleTests, TestGetCLocale)
{
    const auto& cLocale{ pluto::getCLocale() };
}

TEST_F(LocaleTests, TestGetSystemLocale)
{
    const auto& systemLocale{ pluto::getSystemLocale() };
}

TEST_F(LocaleTests, TestGetDefaultLocale)
{
    const auto& defaultLocale{ pluto::getDefaultLocale() };
}

TEST_F(LocaleTests, TestGetFacet)
{
    const auto& facet{ pluto::getFacet<char>(pluto::getDefaultLocale()) };
}
