/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#include <generic/log.hpp>

#define LOG_FATAL(x)    GENERIC_LOG_STREAM_FATAL("logs/log_fatal.log", x)
#define LOG_CRITICAL(x) GENERIC_LOG_STREAM_CRITICAL("logs/log_critical.log", x)
#define LOG_ERROR(x)    GENERIC_LOG_STREAM_ERROR("logs/log_error.log", x)
#define LOG_WARNING(x)  GENERIC_LOG_STREAM_WARNING("logs/log_warning.log", x)
#define LOG_NOTICE(x)   GENERIC_LOG_STREAM_NOTICE("logs/log_notice.log", x)
#define LOG_INFO(x)     GENERIC_LOG_STREAM_INFO("logs/log_info.log", x)
#define LOG_DEBUG(x)    GENERIC_LOG_STREAM_DEBUG("logs/log_debug.log", x)
#define LOG_TRACE(x)    GENERIC_LOG_STREAM_TRACE("logs/log_trace.log", x)
#define LOG_VERBOSE(x)  GENERIC_LOG_STREAM_VERBOSE("logs/log_verbose.log", x)

int main(int argc, char* argv[])
{
    Generic::logger::get_instance().meta_data_columns(
        Generic::logger::meta_data::timestamp,
        Generic::logger::meta_data::process_id,
        Generic::logger::meta_data::thread_id,
        Generic::logger::meta_data::file_name,
        Generic::logger::meta_data::line,
        Generic::logger::meta_data::function);

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
