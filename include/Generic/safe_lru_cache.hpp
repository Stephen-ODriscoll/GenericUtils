/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#pragma once

#include <mutex>
#include <shared_mutex>

#include "lru_cache.hpp"

namespace Generic
{
    template<class KeyT, class ValueT>
    class safe_lru_cache
    {
#if (defined(__cplusplus) && __cplusplus > 201402L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201402L)
        typedef std::shared_mutex shared_mutex_type;
#else
        typedef std::shared_timed_mutex shared_mutex_type;
#endif

        mutable shared_mutex_type           m_mutex{};
        Generic::lru_cache<KeyT, ValueT>    m_lruCache;

    public:
        typedef typename Generic::lru_cache<KeyT, ValueT>::key_type key_type;
        typedef typename Generic::lru_cache<KeyT, ValueT>::value_type value_type;
        typedef typename Generic::lru_cache<KeyT, ValueT>::list_type list_type;
        typedef typename Generic::lru_cache<KeyT, ValueT>::map_type map_type;

        safe_lru_cache(const std::size_t capacity) :
            m_lruCache{ capacity } {}

        ~safe_lru_cache() {}

        std::size_t size() const
        {
            const std::shared_lock<shared_mutex_type> reader{ m_mutex };
            return m_lruCache.size();
        }

        std::size_t capacity() const
        {
            const std::shared_lock<shared_mutex_type> reader{ m_mutex };
            return m_lruCache.capacity();
        }

        bool empty() const
        {
            const std::shared_lock<shared_mutex_type> reader{ m_mutex };
            return m_lruCache.empty();
        }

        bool contains(const key_type& key) const
        {
            const std::shared_lock<shared_mutex_type> reader{ m_mutex };
            return m_lruCache.contains(key);
        }

        void capacity(const std::size_t newCapacity)
        {
            const std::unique_lock<shared_mutex_type> writer{ m_mutex };
            m_lruCache.capacity(newCapacity);
        }

        void insert(const key_type& key, const value_type& value)
        {
            const std::unique_lock<shared_mutex_type> writer{ m_mutex };
            m_lruCache.insert(key, value);
        }

        bool get(const key_type& key, value_type& value)
        {
            const std::unique_lock<shared_mutex_type> writer{ m_mutex };
            return m_lruCache.get(key, value);
        }

        bool remove(const key_type& key)
        {
            const std::unique_lock<shared_mutex_type> writer{ m_mutex };
            return m_lruCache.remove(key);
        }

        void clear()
        {
            const std::unique_lock<shared_mutex_type> writer{ m_mutex };
            m_lruCache.clear();
        }
    };
}
