/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#pragma once

#include <mutex>
#include <shared_mutex>

#include "LRUCache.hpp"

namespace Generic
{
    template<class KeyT, class ValueT>
    class SafeLRUCache
    {
#if (defined(_MSVC_LANG) && _MSVC_LANG > 201402L) || (defined(__cplusplus) && __cplusplus > 201402L)
        typedef std::shared_mutex SharedMutexType;
#else
        typedef std::shared_timed_mutex SharedMutexType;
#endif

        mutable SharedMutexType         m_mutex{};
        Generic::LRUCache<KeyT, ValueT> m_lruCache;

    public:
        typedef typename Generic::LRUCache<KeyT, ValueT>::KeyType KeyType;
        typedef typename Generic::LRUCache<KeyT, ValueT>::ValueType ValueType;
        typedef typename Generic::LRUCache<KeyT, ValueT>::ListType ListType;
        typedef typename Generic::LRUCache<KeyT, ValueT>::MapType MapType;

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

        void clear()
        {
            const std::unique_lock<SharedMutexType> writer{ m_mutex };
            m_lruCache.clear();
        }
    };
}
