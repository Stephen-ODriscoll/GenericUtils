/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#pragma once

#include "iterator_utils.hpp"

namespace pluto
{
    template<class ContainerLeftT, class ContainerRightT, class PredicateT = pluto::IsEqual>
    inline bool equals(
        const ContainerLeftT&   left,
        const ContainerRightT&  right,
        PredicateT              predicate = {})
    {
        return pluto::equals(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

    template<class ContainerLeftT, class ContainerRightT, class PredicateT = pluto::IsEqual>
    inline bool beginsWith(
        const ContainerLeftT&   left,
        const ContainerRightT&  right,
        PredicateT              predicate = {})
    {
        return pluto::beginsWith(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

    template<class ContainerLeftT, class ContainerRightT, class PredicateT = pluto::IsEqual>
    inline bool endsWith(
        const ContainerLeftT&   left,
        const ContainerRightT&  right,
        PredicateT              predicate = {})
    {
        return pluto::endsWith(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

    template<class ContainerT, class ElemT>
    inline auto findElem(
        const ContainerT&   container,
        const ElemT&        elem)
    {
        return pluto::find(std::begin(container), std::end(container), elem);
    }

    template<class ContainerLeftT, class ContainerRightT, class PredicateT = pluto::IsEqual>
    inline auto findSequence(
        const ContainerLeftT&   left,
        const ContainerRightT&  right,
        PredicateT              predicate = {})
    {
        return pluto::find(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

    template<class ContainerT, class PredicateT>
    inline auto findIf(
        const ContainerT&   container,
        PredicateT          predicate)
    {
        return pluto::findIf(std::begin(container), std::end(container), predicate);
    }

    template<class ContainerT, class PredicateT>
    inline auto findIfNot(
        const ContainerT&   container,
        PredicateT          predicate)
    {
        return pluto::findIfNot(std::begin(container), std::end(container), predicate);
    }

    template<class ContainerT, class ElemT>
    inline bool containsElem(
        const ContainerT&   container,
        const ElemT&        elem)
    {
        return pluto::contains(std::begin(container), std::end(container), elem);
    }

    template<class ContainerLeftT, class ContainerRightT, class PredicateT = pluto::IsEqual>
    inline bool containsSequence(
        const ContainerLeftT&   left,
        const ContainerRightT&  right,
        PredicateT              predicate = {})
    {
        return pluto::contains(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }
}
