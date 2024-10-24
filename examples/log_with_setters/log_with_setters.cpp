/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include <Pluto/Logger.hpp>

#define LOG_FILE "logs/logWithSetters.log"

#define LOG_FATAL(x)    PLUTO_LOG_STREAM_FATAL(LOG_FILE, x)
#define LOG_CRITICAL(x) PLUTO_LOG_STREAM_CRITICAL(LOG_FILE, x)
#define LOG_ERROR(x)    PLUTO_LOG_STREAM_ERROR(LOG_FILE, x)
#define LOG_WARNING(x)  PLUTO_LOG_STREAM_WARNING(LOG_FILE, x)
#define LOG_NOTICE(x)   PLUTO_LOG_STREAM_NOTICE(LOG_FILE, x)
#define LOG_INFO(x)     PLUTO_LOG_STREAM_INFO(LOG_FILE, x)
#define LOG_DEBUG(x)    PLUTO_LOG_STREAM_DEBUG(LOG_FILE, x)
#define LOG_TRACE(x)    PLUTO_LOG_STREAM_TRACE(LOG_FILE, x)
#define LOG_VERBOSE(x)  PLUTO_LOG_STREAM_VERBOSE(LOG_FILE, x)

int main(int argc, char* argv[])
{
    pluto::Logger::getInstance()
        .timestampFormat("%H:%M:%S.%.3S")
        .timestampLength(12)
        .bufferMaxSize(1000)
        .bufferFlushSize(100)
        .fileRotationSize(1024) // 1 KB
        .fileRotationLimit(5)
        .headerUnderlineFill('=')
        .separator("  ")
        .headerUnderlineSeparator("  ")
        .level(pluto::Logger::Level::Info)
        .levelFormat(pluto::Logger::LevelFormat::Short)
        .metaDataColumns(
            pluto::Logger::MetaDataColumn::Timestamp,
            pluto::Logger::MetaDataColumn::ThreadID,
            pluto::Logger::MetaDataColumn::Level,
            pluto::Logger::MetaDataColumn::FileName,
            pluto::Logger::MetaDataColumn::Line);

    std::size_t numLogs{ 100 };
    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_FATAL("Log entry " << i << " of " << numLogs);
        LOG_CRITICAL("Log entry " << i << " of " << numLogs);
        LOG_ERROR("Log entry " << i << " of " << numLogs);
        LOG_WARNING("Log entry " << i << " of " << numLogs);
        LOG_NOTICE("Log entry " << i << " of " << numLogs);
        LOG_INFO("Log entry " << i << " of " << numLogs);
        LOG_DEBUG("Log entry " << i << " of " << numLogs);
        LOG_TRACE("Log entry " << i << " of " << numLogs);
        LOG_VERBOSE("Log entry " << i << " of " << numLogs);
    }

    return 0;
}
