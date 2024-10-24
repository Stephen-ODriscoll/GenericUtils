/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include <Pluto/Logger.hpp>

#define LOG_FATAL(x)    PLUTO_LOG_STREAM_FATAL("logs/logFatal.log", x)
#define LOG_CRITICAL(x) PLUTO_LOG_STREAM_CRITICAL("logs/logCritical.log", x)
#define LOG_ERROR(x)    PLUTO_LOG_STREAM_ERROR("logs/logError.log", x)
#define LOG_WARNING(x)  PLUTO_LOG_STREAM_WARNING("logs/logWarning.log", x)
#define LOG_NOTICE(x)   PLUTO_LOG_STREAM_NOTICE("logs/logNotice.log", x)
#define LOG_INFO(x)     PLUTO_LOG_STREAM_INFO("logs/logInfo.log", x)
#define LOG_DEBUG(x)    PLUTO_LOG_STREAM_DEBUG("logs/logDebug.log", x)
#define LOG_TRACE(x)    PLUTO_LOG_STREAM_TRACE("logs/logTrace.log", x)
#define LOG_VERBOSE(x)  PLUTO_LOG_STREAM_VERBOSE("logs/logVerbose.log", x)

int main(int argc, char* argv[])
{
    pluto::Logger::getInstance().metaDataColumns(
        pluto::Logger::MetaDataColumn::Timestamp,
        pluto::Logger::MetaDataColumn::ProcessID,
        pluto::Logger::MetaDataColumn::ThreadID,
        pluto::Logger::MetaDataColumn::FileName,
        pluto::Logger::MetaDataColumn::Line,
        pluto::Logger::MetaDataColumn::Function);

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
