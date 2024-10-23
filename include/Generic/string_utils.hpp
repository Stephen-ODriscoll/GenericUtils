/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#pragma once

// Note that std::codecvt_utf8 is deprecated but there is no alternative in the std library
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#include <vector>
#include <string>
#include <sstream>
#include <codecvt>

#include "container_utils.hpp"

namespace Generic
{
    template<class ElemT>
    inline ElemT to_lower(
        const ElemT         elem,
        const std::locale&  locale = Generic::get_default_locale())
    {
        return Generic::get_facet<ElemT>(locale).tolower(elem);
    }

    template<class ElemT>
    inline void to_lower(
        ElemT* const        pElem,
        const std::size_t   size,
        const std::locale&  locale = Generic::get_default_locale())
    {
        Generic::get_facet<ElemT>(locale).tolower(pElem, (pElem + size));
    }

    template<class ElemT>
    inline void to_lower(
        std::basic_string<ElemT>&   str,
        const std::locale&          locale = Generic::get_default_locale())
    {
        Generic::to_lower(&str[0], str.size(), locale);
    }
    
    template<class ElemT>
    inline ElemT to_upper(
        const ElemT         elem,
        const std::locale&  locale = Generic::get_default_locale())
    {
        return Generic::get_facet<ElemT>(locale).toupper(elem);
    }

    template<class ElemT>
    inline void to_upper(
        ElemT* const        pElem,
        const std::size_t   size,
        const std::locale&  locale = Generic::get_default_locale())
    {
        Generic::get_facet<ElemT>(locale).toupper(pElem, (pElem + size));
    }

    template<class ElemT>
    inline void to_upper(
        std::basic_string<ElemT>&   str,
        const std::locale&          locale = Generic::get_default_locale())
    {
        Generic::to_upper(&str[0], str.size(), locale);
    }

    template<class ElemT>
    inline bool is_lower(
        const ElemT         elem,
        const std::locale&  locale = Generic::get_default_locale())
    {
        return !(Generic::get_facet<ElemT>(locale).is(std::ctype_base::upper, elem));
    }

    template<class ElemT>
    inline bool is_lower(
        const ElemT* const  pElem,
        const std::size_t   size,
        const std::locale&  locale = Generic::get_default_locale())
    {
        const auto& facet{ Generic::get_facet<ElemT>(locale) };

        const auto end{ pElem + size };
        for (auto it{ pElem }; it < end; ++it)
        {
            if (facet.is(std::ctype_base::upper, *it))
            {
                return false;
            }
        }

        return true;
    }

    template<class ElemT>
    inline bool is_lower(
        const std::basic_string<ElemT>& str,
        const std::locale&              locale = Generic::get_default_locale())
    {
        return Generic::is_lower(&str[0], str.size(), locale);
    }

    template<class ElemT>
    inline bool is_upper(
        const ElemT         elem,
        const std::locale&  locale = Generic::get_default_locale())
    {
        return !(Generic::get_facet<ElemT>(locale).is(std::ctype_base::lower, elem));
    }

    template<class ElemT>
    inline bool is_upper(
        const ElemT* const  pElem,
        const std::size_t   size,
        const std::locale&  locale = Generic::get_default_locale())
    {
        const auto& facet{ Generic::get_facet<ElemT>(locale) };

        const auto end{ pElem + size };
        for (auto it{ pElem }; it < end; ++it)
        {
            if (facet.is(std::ctype_base::lower, *it))
            {
                return false;
            }
        }

        return true;
    }

    template<class ElemT>
    inline bool is_upper(
        const std::basic_string<ElemT>& str,
        const std::locale&              locale = Generic::get_default_locale())
    {
        return Generic::is_upper(&str[0], str.size(), locale);
    }

    inline std::string to_narrow(const wchar_t* const str, const std::size_t size)
    {
        static std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter{};
        return converter.to_bytes(str, (str + size));
    }

    inline std::string to_narrow(const std::wstring& str)
    {
        return Generic::to_narrow(&str[0], str.size());
    }

    inline std::string to_narrow(const char* const str, const std::size_t size)
    {
        return std::string(str, size);
    }

    inline std::string to_narrow(const std::string& str)
    {
        return str;
    }

    template<class T>
    inline std::string to_narrow(const T& value)
    {
        std::ostringstream ss{};
        ss << value;
        return ss.str();
    }

    inline std::wstring to_wide(const char* const str, const std::size_t size)
    {
        static std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter{};
        return converter.from_bytes(str, (str + size));
    }

    inline std::wstring to_wide(const std::string& str)
    {
        return Generic::to_wide(&str[0], str.size());
    }

    inline std::wstring to_wide(const wchar_t* const str, const std::size_t size)
    {
        return std::wstring(str, size);
    }

    inline std::wstring to_wide(const std::wstring& str)
    {
        return str;
    }

    template<class T>
    inline std::wstring to_wide(const T& value)
    {
        std::wostringstream ss{};
        ss << value;
        return ss.str();
    }

    template<class T>
    inline T narrow_to(const std::string& str)
    {
        T value;
        std::istringstream(str) >> value;
        return value;
    }

    template<class T>
    inline T narrow_to(const char* const str, const std::size_t size)
    {
        return Generic::narrow_to<T>(std::string(str, size));
    }

    template<class T>
    inline T wide_to(const std::wstring& str)
    {
        T value;
        std::wistringstream(str) >> value;
        return value;
    }

    template<class T>
    inline T wide_to(const wchar_t* const str, const std::size_t size)
    {
        return Generic::wide_to<T>(std::wstring(str, size));
    }

    template<class ElemT>
    inline bool equals_ignore_case(
        const ElemT* const  beginL,
        const std::size_t   sizeL,
        const ElemT* const  beginR,
        const std::size_t   sizeR,
        const std::locale&  locale = Generic::get_default_locale())
    {
        return Generic::equals(beginL, sizeL, beginR, sizeR, Generic::is_equal_ignore_case<ElemT>{ locale });
    }

    template<class ElemT>
    inline bool equals_ignore_case(
        const std::basic_string<ElemT>& left,
        const std::basic_string<ElemT>& right,
        const std::locale&              locale = Generic::get_default_locale())
    {
        return Generic::equals(left, right, Generic::is_equal_ignore_case<ElemT>{ locale });
    }

    template<class ElemT>
    inline bool begins_with_ignore_case(
        const ElemT* const  beginL,
        const std::size_t   sizeL,
        const ElemT* const  beginR,
        const std::size_t   sizeR,
        const std::locale&  locale = Generic::get_default_locale())
    {
        return Generic::begins_with(beginL, sizeL, beginR, sizeR, Generic::is_equal_ignore_case<ElemT>{ locale });
    }

    template<class ElemT>
    inline bool begins_with_ignore_case(
        const std::basic_string<ElemT>& left,
        const std::basic_string<ElemT>& right,
        const std::locale&              locale = Generic::get_default_locale())
    {
        return Generic::begins_with(left, right, Generic::is_equal_ignore_case<ElemT>{ locale });
    }

    template<class ElemT>
    inline bool ends_with_ignore_case(
        const ElemT* const  beginL,
        const std::size_t   sizeL,
        const ElemT* const  beginR,
        const std::size_t   sizeR,
        const std::locale&  locale = Generic::get_default_locale())
    {
        return Generic::ends_with(beginL, sizeL, beginR, sizeR, Generic::is_equal_ignore_case<ElemT>{ locale });
    }

    template<class ElemT>
    inline bool ends_with_ignore_case(
        const std::basic_string<ElemT>& left,
        const std::basic_string<ElemT>& right,
        const std::locale&              locale = Generic::get_default_locale())
    {
        return Generic::ends_with(left, right, Generic::is_equal_ignore_case<ElemT>{ locale });
    }

    template<class ElemT, class PredicateT = Generic::is_equal>
    inline auto find(
        const std::basic_string<ElemT>& left,
        const std::basic_string<ElemT>& right,
        PredicateT                      predicate = {})
    {
        return Generic::find_sequence(left, right, predicate);
    }

    template<class ElemT>
    inline const ElemT* const find_ignore_case(
        const ElemT* const  beginL,
        const std::size_t   sizeL,
        const ElemT* const  beginR,
        const std::size_t   sizeR,
        const std::locale&  locale = Generic::get_default_locale())
    {
        return Generic::find(beginL, sizeL, beginR, sizeR, Generic::is_equal_ignore_case<ElemT>{ locale });
    }

    template<class ElemT>
    inline auto find_ignore_case(
        const std::basic_string<ElemT>& left,
        const std::basic_string<ElemT>& right,
        const std::locale&              locale = Generic::get_default_locale())
    {
        return Generic::find_sequence(left, right, Generic::is_equal_ignore_case<ElemT>{ locale });
    }

    template<class ElemT, class PredicateT = Generic::is_equal>
    inline bool contains(
        const std::basic_string<ElemT>& left,
        const std::basic_string<ElemT>& right,
        PredicateT                      predicate = {})
    {
        return Generic::contains_sequence(left, right, predicate);
    }

    template<class ElemT>
    inline bool contains_ignore_case(
        const ElemT* const  beginL,
        const std::size_t   sizeL,
        const ElemT* const  beginR,
        const std::size_t   sizeR,
        const std::locale&  locale = Generic::get_default_locale())
    {
        return Generic::contains(beginL, sizeL, beginR, sizeR, Generic::is_equal_ignore_case<ElemT>{ locale });
    }

    template<class ElemT>
    inline bool contains_ignore_case(
        const std::basic_string<ElemT>& left,
        const std::basic_string<ElemT>& right,
        const std::locale&              locale = Generic::get_default_locale())
    {
        return Generic::contains_sequence(left, right, Generic::is_equal_ignore_case<ElemT>{ locale });
    }

    template<class ElemT>
    inline std::vector<std::basic_string<ElemT>> split_any_of(
        const std::basic_string<ElemT>& str,
        const std::basic_string<ElemT>& sep)
    {
        std::size_t from, to{ 0 };
        std::vector<std::basic_string<ElemT>> splits{};
        while ((from = str.find_first_not_of(sep, to)) != str.npos)
        {
            to = str.find_first_of(sep, from);
            splits.push_back(str.substr(from, (to - from)));
        }

        return splits;
    }

    template<class ElemT>
    inline std::vector<std::basic_string<ElemT>> split(
        const std::basic_string<ElemT>& str,
        const std::locale&              locale = Generic::get_default_locale())
    {
        const auto& facet{ Generic::get_facet<ElemT>(locale) };

        std::size_t from{ 0 }, to;
        std::vector<std::basic_string<ElemT>> splits{};
        while (from < str.size())
        {
            while (facet.is(std::ctype_base::space, str[from]))
            {
                ++from;

                if (!(from < str.size()))
                {
                    goto done;
                }
            }

            to = from;
            ++to;

            while (to < str.size() && !facet.is(std::ctype_base::space, str[to]))
            {
                ++to;
            }

            splits.push_back(str.substr(from, (to - from)));
            from = to;
            ++from;
        }

    done:
        return splits;
    }

    template<class ElemT>
    inline std::vector<std::basic_string<ElemT>> split(
        const std::basic_string<ElemT>& str,
        const std::basic_string<ElemT>& sep)
    {
        if (sep.empty())
        {
            throw std::invalid_argument("Generic::split() got empty separator");
        }

        std::size_t from{ 0 }, to;
        std::vector<std::basic_string<ElemT>> splits{};
        while ((to = str.find(sep, from)) != str.npos)
        {
            splits.push_back(str.substr(from, (to - from)));
            from = (to + sep.size());
        }

        splits.push_back(str.substr(from));
        return splits;
    }

    template<class ElemT, class IteratorT>
    inline std::basic_string<ElemT> join(
        const std::basic_string<ElemT>& sep,
        const IteratorT                 begin,
        const IteratorT                 end)
    {
        std::basic_string<ElemT> str{};
        for (auto it{ begin }; it != end; ++it)
        {
            if (it != begin)
            {
                str.append(sep);
            }

            str.append(*it);
        }

        return str;
    }

    template<class ElemT, class ContainerT>
    inline std::basic_string<ElemT> join(
        const std::basic_string<ElemT>& sep,
        const ContainerT&               container)
    {
        return Generic::join(sep, std::begin(container), std::end(container));
    }

    template<class ElemT>
    inline void ltrim(
        std::basic_string<ElemT>&   str,
        const std::locale&          locale = Generic::get_default_locale())
    {
        const auto& facet{ Generic::get_facet<ElemT>(locale) };

        std::size_t from{ 0 };
        while (from < str.size() && facet.is(std::ctype_base::space, str[from]))
        {
            ++from;
        }

        str.erase(0, from);
    }

    template<class ElemT>
    inline void rtrim(
        std::basic_string<ElemT>&   str,
        const std::locale&          locale = Generic::get_default_locale())
    {
        const auto& facet{ Generic::get_facet<ElemT>(locale) };

        std::size_t to{ str.size() };
        while (0 < to)
        {
            if (!facet.is(std::ctype_base::space, str[--to]))
            {
                ++to;
                break;
            }
        }

        str.erase(to);
    }

    template<class ElemT>
    inline void trim(
        std::basic_string<ElemT>&   str,
        const std::locale&          locale = Generic::get_default_locale())
    {
        Generic::ltrim(str, locale);
        Generic::rtrim(str, locale);
    }
}
