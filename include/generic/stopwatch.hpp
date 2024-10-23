/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#pragma once

#include <chrono>

namespace Generic
{
    class stopwatch
    {
    public:
        typedef std::chrono::high_resolution_clock clock;

    private:
        clock::duration     m_time;
        clock::time_point   m_start;
        bool                m_isRunning;

    public:
        stopwatch(const bool startNow = false) :
            m_time      {},
            m_start     {},
            m_isRunning { false }
        {
            if (startNow)
            {
                start();
            }
        }

        stopwatch(const stopwatch& other) :
            m_time      { other.m_time },
            m_start     { other.m_start },
            m_isRunning { other.m_isRunning } {}

        ~stopwatch() {}

        void reset()
        {
            m_time = {};
            m_start = {};
            m_isRunning = false;
        }

        void restart()
        {
            m_time = {};
            m_start = clock::now();
            m_isRunning = true;
        }

        void start()
        {
            if (!m_isRunning)
            {
                m_start = clock::now();
                m_isRunning = true;
            }
        }

        void stop()
        {
            if (m_isRunning)
            {
                m_time += (clock::now() - m_start);
                m_isRunning = false;
            }
        }

        auto stop_and_time()
        {
            stop();
            return m_time;
        }

        auto time() const
        {
            return (m_isRunning ? (m_time + (clock::now() - m_start)) : m_time);
        }

        bool is_running() const
        {
            return m_isRunning;
        }

        template<class DurationT>
        auto count() const { return std::chrono::duration_cast<DurationT>(time()).count(); }

        template<class DurationT>
        auto count(const long long rollover) const { return (count<DurationT>() % rollover); }

        auto in_nanoseconds()    const   { return count<std::chrono::nanoseconds>(); }
        auto in_microseconds()   const   { return count<std::chrono::microseconds>(); }
        auto in_milliseconds()   const   { return count<std::chrono::milliseconds>(); }
        auto in_seconds()        const   { return count<std::chrono::seconds>(); }
        auto in_minutes()        const   { return count<std::chrono::minutes>(); }
        auto in_hours()          const   { return count<std::chrono::hours>(); }

        auto nanoseconds_part()  const   { return count<std::chrono::nanoseconds>(1'000); }
        auto microseconds_part() const   { return count<std::chrono::microseconds>(1'000); }
        auto milliseconds_part() const   { return count<std::chrono::milliseconds>(1'000); }
        auto seconds_part()      const   { return count<std::chrono::seconds>(60); }
        auto minutes_part()      const   { return count<std::chrono::minutes>(60); }
        auto hours_part()        const   { return count<std::chrono::hours>(); }
    };
}
