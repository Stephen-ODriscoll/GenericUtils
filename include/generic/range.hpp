/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#pragma once

namespace Generic
{
    template<class T>
    struct range
    {
        T begin;
        T end;

        range(const T& begin, const T& end) :
            begin   { begin },
            end     { end } {}

        range(const range& other) :
            begin   { other.begin },
            end     { other.end } {}

        ~range() {}

        auto size() const
        {
            return (end - begin);
        }

        bool is_equal(const range& other) const
        {
            return (begin == other.begin && end == other.end);
        }

        bool is_overlapping(const range& other) const
        {
            return (begin < other.end && other.begin < end);
        }

        bool is_less(const range& other) const
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
        bool is_less_no_overlap(const range& other) const
        {
            return (end <= other.begin);
        }

        bool operator==(const range& other) const
        {
            return is_equal(other);
        }

        bool operator!=(const range& other) const
        {
            return !(is_equal(other));
        }

        bool operator<(const range& other) const
        {
            return is_less(other);
        }

        bool operator>(const range& other) const
        {
            return other.is_less(*this);
        }

        bool operator<=(const range& other) const
        {
            return !(other.is_less(*this));
        }

        bool operator>=(const range& other) const
        {
            return !(is_less(other));
        }
    };

    typedef range<int>                  int_range;
    typedef range<unsigned int>         uint_range;
    typedef range<long>                 long_range;
    typedef range<unsigned long>        ulong_range;
    typedef range<long long>            long_long_range;
    typedef range<unsigned long long>   u_long_long_range;
    typedef range<void*>                pvoid_range;
}
