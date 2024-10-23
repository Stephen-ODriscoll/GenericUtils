/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#pragma once

#include <iterator>
#include <algorithm>

#include "compare.hpp"

namespace Generic
{
    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Generic::is_equal>
    inline bool equals_same_size(
        const IteratorLeftT     beginL,
        const IteratorLeftT     endL,
        const IteratorRightT    beginR,
        PredicateT              predicate = {})
    {
        return std::equal(beginL, endL, beginR, predicate);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Generic::is_equal>
    inline bool equals(
        const IteratorLeftT     beginL,
        const IteratorLeftT     endL,
        const IteratorRightT    beginR,
        const IteratorRightT    endR,
        PredicateT              predicate = {})
    {
        return (std::distance(beginL, endL) == std::distance(beginR, endR)) &&
            Generic::equals_same_size(beginL, endL, beginR, predicate);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Generic::is_equal>
    inline bool equals(
        const IteratorLeftT     beginL,
        const std::size_t       sizeL,
        const IteratorRightT    beginR,
        const std::size_t       sizeR,
        PredicateT              predicate = {})
    {
        return (sizeL == sizeR) &&
            Generic::equals_same_size(beginL, std::next(beginL, sizeL), beginR, predicate);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Generic::is_equal>
    inline bool begins_with(
        const IteratorLeftT     beginL,
        const IteratorLeftT     endL,
        const IteratorRightT    beginR,
        const IteratorRightT    endR,
        PredicateT              predicate = {})
    {
        return (std::distance(beginR, endR) <= std::distance(beginL, endL)) &&
            Generic::equals_same_size(beginR, endR, beginL, predicate);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Generic::is_equal>
    inline bool begins_with(
        const IteratorLeftT     beginL,
        const std::size_t       sizeL,
        const IteratorRightT    beginR,
        const std::size_t       sizeR,
        PredicateT              predicate = {})
    {
        return (sizeR <= sizeL) &&
            Generic::equals_same_size(beginR, std::next(beginR, sizeR), beginL, predicate);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Generic::is_equal>
    inline bool ends_with(
        const IteratorLeftT     beginL,
        const IteratorLeftT     endL,
        const IteratorRightT    beginR,
        const IteratorRightT    endR,
        PredicateT              predicate = {})
    {
        const auto sizeR{ std::distance(beginR, endR) };

        return (sizeR <= std::distance(beginL, endL)) &&
            Generic::equals_same_size(beginR, endR, std::prev(endL, sizeR), predicate);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Generic::is_equal>
    inline bool ends_with(
        const IteratorLeftT     beginL,
        const std::size_t       sizeL,
        const IteratorRightT    beginR,
        const std::size_t       sizeR,
        PredicateT              predicate = {})
    {
        return (sizeR <= sizeL) &&
            Generic::equals_same_size(beginR, std::next(beginR, sizeR), std::next(beginL, (sizeL - sizeR)), predicate);
    }

    template<class IteratorT, class ElemT>
    inline IteratorT find(
        const IteratorT begin,
        const IteratorT end,
        const ElemT     elem)
    {
        return std::find(begin, end, elem);
    }

    template<class IteratorT, class ElemT>
    inline IteratorT find(
        const IteratorT     begin,
        const std::size_t   size,
        const ElemT         elem)
    {
        return Generic::find(begin, std::next(begin, size), elem);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Generic::is_equal>
    inline IteratorLeftT find(
        const IteratorLeftT     beginL,
        const IteratorLeftT     endL,
        const IteratorRightT    beginR,
        const IteratorRightT    endR,
        PredicateT              predicate = {})
    {
        return std::search(beginL, endL, beginR, endR, predicate);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Generic::is_equal>
    inline IteratorLeftT find(
        const IteratorLeftT     beginL,
        const std::size_t       sizeL,
        const IteratorRightT    beginR,
        const std::size_t       sizeR,
        PredicateT              predicate = {})
    {
        return Generic::find(beginL, std::next(beginL, sizeL), beginR, std::next(beginR, sizeR), predicate);
    }

    template<class IteratorT, class PredicateT>
    inline IteratorT find_if(
        const IteratorT begin,
        const IteratorT end,
        PredicateT      predicate)
    {
        return std::find_if(begin, end, predicate);
    }

    template<class IteratorT, class PredicateT>
    inline IteratorT find_if(
        const IteratorT     begin,
        const std::size_t   size,
        PredicateT          predicate)
    {
        return Generic::find_if(begin, std::next(begin, size), predicate);
    }

    template<class IteratorT, class PredicateT>
    inline IteratorT find_if_not(
        const IteratorT begin,
        const IteratorT end,
        PredicateT      predicate)
    {
        return std::find_if_not(begin, end, predicate);
    }

    template<class IteratorT, class PredicateT>
    inline IteratorT find_if_not(
        const IteratorT     begin,
        const std::size_t   size,
        PredicateT          predicate)
    {
        return Generic::find_if_not(begin, std::next(begin, size), predicate);
    }

    template<class IteratorT, class ElemT>
    inline bool contains(
        const IteratorT     begin,
        const IteratorT     end,
        const ElemT         elem)
    {
        return (Generic::find(begin, end, elem) != end);
    }

    template<class IteratorT, class ElemT>
    inline bool contains(
        const IteratorT     begin,
        const std::size_t   size,
        const ElemT         elem)
    {
        const auto end{ std::next(begin, size) };

        return (Generic::find(begin, end, elem) != end);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Generic::is_equal>
    inline bool contains(
        const IteratorLeftT     beginL,
        const IteratorLeftT     endL,
        const IteratorRightT    beginR,
        const IteratorRightT    endR,
        PredicateT              predicate = {})
    {
        return (beginR == endR) ||
            (Generic::find(beginL, endL, beginR, endR, predicate) != endL);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Generic::is_equal>
    inline bool contains(
        const IteratorLeftT     beginL,
        const std::size_t       sizeL,
        const IteratorRightT    beginR,
        const std::size_t       sizeR,
        PredicateT              predicate = {})
    {
        if (sizeR == 0)
        {
            return true;
        }

        const auto endL{ std::next(beginL, sizeL) };

        return (Generic::find(beginL, endL, beginR, std::next(beginR, sizeR), predicate) != endL);
    }
}
