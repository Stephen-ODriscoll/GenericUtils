/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#define GENERIC_LOGGER_DEFAULT_TIMESTAMP_FORMAT "%H:%M:%S.%.3S"
#define GENERIC_LOGGER_DEFAULT_TIMESTAMP_LENGTH 12
#define GENERIC_LOGGER_DEFAULT_BUFFER_MAX_SIZE 1000
#define GENERIC_LOGGER_DEFAULT_BUFFER_FLUSH_SIZE 100
#define GENERIC_LOGGER_DEFAULT_FILE_ROTATION_SIZE 1024  // 1 KB
#define GENERIC_LOGGER_DEFAULT_FILE_ROTATION_LIMIT 5
#define GENERIC_LOGGER_DEFAULT_HEADER_UNDERLINE_FILL '='
#define GENERIC_LOGGER_DEFAULT_SEPARATOR "  "
#define GENERIC_LOGGER_DEFAULT_HEADER_UNDERLINE_SEPARATOR "  "
#define GENERIC_LOGGER_DEFAULT_LOG_LEVEL Generic::logger::level::info
#define GENERIC_LOGGER_DEFAULT_LOG_LEVEL_FORMAT Generic::logger::level_format::abbreviated
#define GENERIC_LOGGER_DEFAULT_META_DATA_COLUMNS \
    Generic::logger::meta_data::timestamp, \
    Generic::logger::meta_data::thread_id, \
    Generic::logger::meta_data::level, \
    Generic::logger::meta_data::file_name, \
    Generic::logger::meta_data::line

#include <generic/log.hpp>

#define LOG_FILE "logs/log_with_macros.log"

#define LOG_FATAL(x)    GENERIC_LOG_STREAM_FATAL(LOG_FILE, x)
#define LOG_CRITICAL(x) GENERIC_LOG_STREAM_CRITICAL(LOG_FILE, x)
#define LOG_ERROR(x)    GENERIC_LOG_STREAM_ERROR(LOG_FILE, x)
#define LOG_WARNING(x)  GENERIC_LOG_STREAM_WARNING(LOG_FILE, x)
#define LOG_NOTICE(x)   GENERIC_LOG_STREAM_NOTICE(LOG_FILE, x)
#define LOG_INFO(x)     GENERIC_LOG_STREAM_INFO(LOG_FILE, x)
#define LOG_DEBUG(x)    GENERIC_LOG_STREAM_DEBUG(LOG_FILE, x)
#define LOG_TRACE(x)    GENERIC_LOG_STREAM_TRACE(LOG_FILE, x)
#define LOG_VERBOSE(x)  GENERIC_LOG_STREAM_VERBOSE(LOG_FILE, x)

int main(int argc, char* argv[])
{
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
