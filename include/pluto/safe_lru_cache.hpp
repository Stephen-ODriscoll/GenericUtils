/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#pragma once

#include <mutex>
#include <shared_mutex>

#include "lru_cache.hpp"

namespace pluto
{
    template<class KeyT, class ValueT>
    class SafeLRUCache
    {
#if (defined(__cplusplus) && __cplusplus > 201402L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201402L)
        typedef std::shared_mutex SharedMutexType;
#else
        typedef std::shared_timed_mutex SharedMutexType;
#endif

        mutable SharedMutexType         m_mutex{};
        pluto::LRUCache<KeyT, ValueT>   m_lruCache;

    public:
        typedef typename pluto::LRUCache<KeyT, ValueT>::KeyType KeyType;
        typedef typename pluto::LRUCache<KeyT, ValueT>::ValueType ValueType;
        typedef typename pluto::LRUCache<KeyT, ValueT>::ListType ListType;
        typedef typename pluto::LRUCache<KeyT, ValueT>::MapType MapType;

        SafeLRUCache(const std::size_t capacity) :
            m_lruCache{ capacity } {}

        ~SafeLRUCache() {}

        std::size_t size() const
        {
            const std::shared_lock<SharedMutexType> reader{ m_mutex };
            return m_lruCache.size();
        }

        std::size_t capacity() const
        {
            const std::shared_lock<SharedMutexType> reader{ m_mutex };
            return m_lruCache.capacity();
        }

        bool empty() const
        {
            const std::shared_lock<SharedMutexType> reader{ m_mutex };
            return m_lruCache.empty();
        }

        bool contains(const KeyType& key) const
        {
            const std::shared_lock<SharedMutexType> reader{ m_mutex };
            return m_lruCache.contains(key);
        }

        void capacity(const std::size_t newCapacity)
        {
            const std::unique_lock<SharedMutexType> writer{ m_mutex };
            m_lruCache.capacity(newCapacity);
        }

        void insert(const KeyType& key, const ValueType& value)
        {
            const std::unique_lock<SharedMutexType> writer{ m_mutex };
            m_lruCache.insert(key, value);
        }

        bool get(const KeyType& key, ValueType& value)
        {
            const std::unique_lock<SharedMutexType> writer{ m_mutex };
            return m_lruCache.get(key, value);
        }

        bool remove(const KeyType& key)
        {
            const std::unique_lock<SharedMutexType> writer{ m_mutex };
            return m_lruCache.remove(key);
        }

        void clear()
        {
            const std::unique_lock<SharedMutexType> writer{ m_mutex };
            m_lruCache.clear();
        }
    };
}
