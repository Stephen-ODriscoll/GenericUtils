/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#pragma once

#include <functional>

#include "locale.hpp"

namespace Generic
{
    typedef std::equal_to<>         is_equal;
    typedef std::not_equal_to<>     is_not_equal;
    typedef std::less<>             is_less;
    typedef std::greater<>          is_greater;
    typedef std::less_equal<>       is_less_equal;
    typedef std::greater_equal<>    is_greater_equal;

    template<class ElemT>
    struct is_equal_ignore_case
    {
        const std::ctype<ElemT>& facet;

        is_equal_ignore_case(const std::locale& locale) :
            facet{ Generic::get_facet<ElemT>(locale) } {}

        bool operator()(const ElemT& left, const ElemT& right) const
        {
            return (left == right || facet.toupper(left) == facet.toupper(right));
        }
    };

    template<class ElemT>
    struct is_not_equal_ignore_case
    {
        const std::ctype<ElemT>& facet;

        is_not_equal_ignore_case(const std::locale& locale) :
            facet{ Generic::get_facet<ElemT>(locale) } {}

        bool operator()(const ElemT& left, const ElemT& right) const
        {
            return (left != right && facet.toupper(left) != facet.toupper(right));
        }
    };

    template<class ElemT>
    struct is_less_ignore_case
    {
        const std::ctype<ElemT>& facet;

        is_less_ignore_case(const std::locale& locale) :
            facet{ Generic::get_facet<ElemT>(locale) } {}

        bool operator()(const ElemT& left, const ElemT& right) const
        {
            return (facet.toupper(left) < facet.toupper(right));
        }
    };
    
    template<class ElemT>
    struct is_greater_ignore_case
    {
        const std::ctype<ElemT>& facet;

        is_greater_ignore_case(const std::locale& locale) :
            facet{ Generic::get_facet<ElemT>(locale) } {}

        bool operator()(const ElemT& left, const ElemT& right) const
        {
            return (facet.toupper(left) > facet.toupper(right));
        }
    };

    template<class ElemT>
    struct is_less_equal_ignore_case
    {
        const std::ctype<ElemT>& facet;

        is_less_equal_ignore_case(const std::locale& locale) :
            facet{ Generic::get_facet<ElemT>(locale) } {}

        bool operator()(const ElemT& left, const ElemT& right) const
        {
            return (left == right || facet.toupper(left) <= facet.toupper(right));
        }
    };

    template<class ElemT>
    struct is_greater_equal_ignore_case
    {
        const std::ctype<ElemT>& facet;

        is_greater_equal_ignore_case(const std::locale& locale) :
            facet{ Generic::get_facet<ElemT>(locale) } {}

        bool operator()(const ElemT& left, const ElemT& right) const
        {
            return (left == right || facet.toupper(left) >= facet.toupper(right));
        }
    };
}
