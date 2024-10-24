/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#pragma once

namespace pluto
{
    template<class T>
    struct Range
    {
        T begin;
        T end;

        Range(const T& begin, const T& end) :
            begin   { begin },
            end     { end } {}

        Range(const Range& other) :
            begin   { other.begin },
            end     { other.end } {}

        ~Range() {}

        auto size() const
        {
            return (end - begin);
        }

        bool isEqual(const Range& other) const
        {
            return (begin == other.begin && end == other.end);
        }

        bool isOverlapping(const Range& other) const
        {
            return (begin < other.end && other.begin < end);
        }

        bool isLess(const Range& other) const
        {
            return ((begin == other.begin) ? (end < other.end) : (begin < other.begin));
        }

        // Warning:
        // Ranges of size 0 sorted by "no overlap" will behave strangely.
        // They will never overlap with anything as their size is 0.
        // Multiple ranges of size 0 can exist at the same spot.
        // Ranges of size 0 cannot be found using "no overlap".
        // As such, they will be hidden in a sorted container.
        //
        // This is correct, technically a range of size 0 doesn't physically exist.
        bool isLessNoOverlap(const Range& other) const
        {
            return (end <= other.begin);
        }

        bool operator==(const Range& other) const
        {
            return isEqual(other);
        }

        bool operator!=(const Range& other) const
        {
            return !(isEqual(other));
        }

        bool operator<(const Range& other) const
        {
            return isLess(other);
        }

        bool operator>(const Range& other) const
        {
            return other.isLess(*this);
        }

        bool operator<=(const Range& other) const
        {
            return !(other.isLess(*this));
        }

        bool operator>=(const Range& other) const
        {
            return !(isLess(other));
        }
    };

    typedef Range<int>                  IntRange;
    typedef Range<unsigned int>         UIntRange;
    typedef Range<long>                 LongRange;
    typedef Range<unsigned long>        ULongRange;
    typedef Range<long long>            LongLongRange;
    typedef Range<unsigned long long>   ULongLongRange;
    typedef Range<void*>                PVoidRange;
}
