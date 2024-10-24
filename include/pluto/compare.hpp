/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#pragma once

#include <functional>

#include "locale.hpp"

namespace pluto
{
    typedef std::equal_to<>         IsEqual;
    typedef std::not_equal_to<>     IsNotEqual;
    typedef std::less<>             IsLess;
    typedef std::greater<>          IsGreater;
    typedef std::less_equal<>       IsLessEqual;
    typedef std::greater_equal<>    IsGreaterEqual;

    template<class ElemT>
    struct IsEqualIgnoreCase
    {
        const std::ctype<ElemT>& facet;

        IsEqualIgnoreCase(const std::locale& locale) :
            facet{ pluto::getFacet<ElemT>(locale) } {}

        bool operator()(const ElemT& left, const ElemT& right) const
        {
            return (left == right || facet.toupper(left) == facet.toupper(right));
        }
    };

    template<class ElemT>
    struct IsNotEqualIgnoreCase
    {
        const std::ctype<ElemT>& facet;

        IsNotEqualIgnoreCase(const std::locale& locale) :
            facet{ pluto::getFacet<ElemT>(locale) } {}

        bool operator()(const ElemT& left, const ElemT& right) const
        {
            return (left != right && facet.toupper(left) != facet.toupper(right));
        }
    };

    template<class ElemT>
    struct IsLessIgnoreCase
    {
        const std::ctype<ElemT>& facet;

        IsLessIgnoreCase(const std::locale& locale) :
            facet{ pluto::getFacet<ElemT>(locale) } {}

        bool operator()(const ElemT& left, const ElemT& right) const
        {
            return (facet.toupper(left) < facet.toupper(right));
        }
    };
    
    template<class ElemT>
    struct IsGreaterIgnoreCase
    {
        const std::ctype<ElemT>& facet;

        IsGreaterIgnoreCase(const std::locale& locale) :
            facet{ pluto::getFacet<ElemT>(locale) } {}

        bool operator()(const ElemT& left, const ElemT& right) const
        {
            return (facet.toupper(left) > facet.toupper(right));
        }
    };

    template<class ElemT>
    struct IsLessEqualIgnoreCase
    {
        const std::ctype<ElemT>& facet;

        IsLessEqualIgnoreCase(const std::locale& locale) :
            facet{ pluto::getFacet<ElemT>(locale) } {}

        bool operator()(const ElemT& left, const ElemT& right) const
        {
            return (left == right || facet.toupper(left) <= facet.toupper(right));
        }
    };

    template<class ElemT>
    struct IsGreaterEqualIgnoreCase
    {
        const std::ctype<ElemT>& facet;

        IsGreaterEqualIgnoreCase(const std::locale& locale) :
            facet{ pluto::getFacet<ElemT>(locale) } {}

        bool operator()(const ElemT& left, const ElemT& right) const
        {
            return (left == right || facet.toupper(left) >= facet.toupper(right));
        }
    };
}
