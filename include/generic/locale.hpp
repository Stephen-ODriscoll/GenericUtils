/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#pragma once

#include <locale>

// Configurable with a macro
#ifndef GENERIC_LOCALE_DEFAULT_LOCALE
#define GENERIC_LOCALE_DEFAULT_LOCALE ""
#endif

namespace Generic
{
    inline const auto& get_c_locale()
    {
        static const std::locale cLocale{ "C" };
        return cLocale;
    }

    inline const auto& get_system_locale()
    {
        static const std::locale systemLocale{ "" };
        return systemLocale;
    }

    inline const auto& get_default_locale()
    {
        static const std::locale defaultLocale{ GENERIC_LOCALE_DEFAULT_LOCALE };
        return defaultLocale;
    }

    template<class ElemT>
    inline const auto& get_facet(const std::locale& locale)
    {
        return std::use_facet<std::ctype<ElemT>>(locale);
    }
}
