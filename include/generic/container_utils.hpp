/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#pragma once

#include "iterator_utils.hpp"

namespace Generic
{
    template<class ContainerLeftT, class ContainerRightT, class PredicateT = Generic::is_equal>
    inline bool equals(
        const ContainerLeftT&   left,
        const ContainerRightT&  right,
        PredicateT              predicate = {})
    {
        return Generic::equals(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

    template<class ContainerLeftT, class ContainerRightT, class PredicateT = Generic::is_equal>
    inline bool begins_with(
        const ContainerLeftT&   left,
        const ContainerRightT&  right,
        PredicateT              predicate = {})
    {
        return Generic::begins_with(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

    template<class ContainerLeftT, class ContainerRightT, class PredicateT = Generic::is_equal>
    inline bool ends_with(
        const ContainerLeftT&   left,
        const ContainerRightT&  right,
        PredicateT              predicate = {})
    {
        return Generic::ends_with(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

    template<class ContainerT, class ElemT>
    inline auto find_elem(
        const ContainerT&   container,
        const ElemT&        elem)
    {
        return Generic::find(std::begin(container), std::end(container), elem);
    }

    template<class ContainerLeftT, class ContainerRightT, class PredicateT = Generic::is_equal>
    inline auto find_sequence(
        const ContainerLeftT&   left,
        const ContainerRightT&  right,
        PredicateT              predicate = {})
    {
        return Generic::find(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

    template<class ContainerT, class PredicateT>
    inline auto find_if(
        const ContainerT&   container,
        PredicateT          predicate)
    {
        return Generic::find_if(std::begin(container), std::end(container), predicate);
    }

    template<class ContainerT, class PredicateT>
    inline auto find_if_not(
        const ContainerT&   container,
        PredicateT          predicate)
    {
        return Generic::find_if_not(std::begin(container), std::end(container), predicate);
    }

    template<class ContainerT, class ElemT>
    inline bool contains_elem(
        const ContainerT&   container,
        const ElemT&        elem)
    {
        return Generic::contains(std::begin(container), std::end(container), elem);
    }

    template<class ContainerLeftT, class ContainerRightT, class PredicateT = Generic::is_equal>
    inline bool contains_sequence(
        const ContainerLeftT&   left,
        const ContainerRightT&  right,
        PredicateT              predicate = {})
    {
        return Generic::contains(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }
}
