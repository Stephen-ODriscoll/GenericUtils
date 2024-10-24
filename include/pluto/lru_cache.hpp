/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#pragma once

#include <map>
#include <list>

namespace pluto
{
    template<class KeyT, class ValueT>
    class LRUCache
    {
    public:
        typedef KeyT KeyType;
        typedef ValueT ValueType;
        typedef std::list<KeyType> ListType;
        typedef std::map<KeyType, std::pair<ValueType, typename ListType::iterator>> MapType;

    private:
        std::size_t m_capacity;
        ListType    m_list{};
        MapType     m_map{};
    
    public:
        LRUCache(const std::size_t capacity) :
            m_capacity{ capacity } {}

        ~LRUCache() {}

        std::size_t size()                  const   { return m_map.size(); }
        std::size_t capacity()              const   { return m_capacity; }
        bool empty()                        const   { return m_map.empty(); }
        bool contains(const KeyType& key)   const   { return (m_map.find(key) != m_map.end()); }

        void capacity(const std::size_t newCapacity)
        {
            m_capacity = newCapacity;

            // While cache is above capacity, evict the least recently used item
            while (m_capacity < size())
            {
                evictLRU();
            }
        }

        void insert(const KeyType& key, const ValueType& value)
        {
            auto itMap{ m_map.find(key) };
            if (itMap == m_map.end())
            {
                if (m_capacity != 0)
                {
                    // If cache is full, evict the least recently used item
                    if (m_capacity <= size())
                    {
                        evictLRU();
                    }

                    m_list.push_front(key);
                    m_map.emplace(key, std::make_pair(value, m_list.begin()));
                }
            }
            else
            {
                // Replace value in cache with new value
                itMap->second.first = value;
                moveToFront(itMap);
            }
        }

        bool get(const KeyType& key, ValueType& value)
        {
            auto itMap{ m_map.find(key) };
            if (itMap == m_map.end())
            {
                return false;
            }

            value = itMap->second.first;
            moveToFront(itMap);
            return true;
        }

        bool remove(const KeyType& key)
        {
            auto itMap{ m_map.find(key) };
            if (itMap == m_map.end())
            {
                return false;
            }

            m_list.erase(itMap->second.second);
            m_map.erase(itMap);
            return true;
        }

        void clear()
        {
            m_map.clear();
            m_list.clear();
        }

    private:
        void moveToFront(typename MapType::iterator itMap)
        {
            // Move item to front of most recently used list
            auto itList{ itMap->second.second };
            if (itList != m_list.begin())
            {
                m_list.erase(itList);
                m_list.push_front(itMap->first);

                itMap->second.second = m_list.begin();
            }
        }

        void evictLRU()
        {
            // Evict least recently used item
            auto itList{ --m_list.end() };
            m_map.erase(*itList);
            m_list.erase(itList);
        }
    };
}
