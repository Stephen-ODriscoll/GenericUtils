/*
* Copyright (c) 2024 Stephen O Driscoll
* 
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#pragma once

#include <map>
#include <list>
#include <mutex>
#include <atomic>
#include <chrono>
#include <string>
#include <thread>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdarg.h>
#include <condition_variable>

#ifdef _WIN32
#include <process.h>
#else
#include <unistd.h>
#endif

#include "filesystem.hpp"

// Configurable with macro
#ifndef GENERIC_LOGGER_HIDE_SOURCE_INFO
#define GENERIC_LOGGER_HIDE_SOURCE_INFO 0   // Define as 1 or 0
#endif

#ifndef GENERIC_LOGGER_NO_SINGLETON
#define GENERIC_LOGGER_NO_SINGLETON 0   // Define as 1 or 0
#endif

// Configurable with macros or setters
#ifndef GENERIC_LOGGER_DEFAULT_LOG_LEVEL
#define GENERIC_LOGGER_DEFAULT_LOG_LEVEL Generic::logger::level::verbose
#endif

#ifndef GENERIC_LOGGER_DEFAULT_LOG_LEVEL_FORMAT
#define GENERIC_LOGGER_DEFAULT_LOG_LEVEL_FORMAT Generic::logger::level_format::full
#endif

#ifndef GENERIC_LOGGER_DEFAULT_CREATE_DIRS
#define GENERIC_LOGGER_DEFAULT_CREATE_DIRS true
#endif

#ifndef GENERIC_LOGGER_DEFAULT_WRITE_HEADER
#define GENERIC_LOGGER_DEFAULT_WRITE_HEADER true
#endif

#ifndef GENERIC_LOGGER_DEFAULT_WRITE_HEADER_UNDERLINE
#define GENERIC_LOGGER_DEFAULT_WRITE_HEADER_UNDERLINE true
#endif

#ifndef GENERIC_LOGGER_DEFAULT_HEADER_UNDERLINE_FILL
#define GENERIC_LOGGER_DEFAULT_HEADER_UNDERLINE_FILL '-'
#endif

#ifndef GENERIC_LOGGER_DEFAULT_BUFFER_MAX_SIZE
#define GENERIC_LOGGER_DEFAULT_BUFFER_MAX_SIZE 0    // 0 means unlimited
#endif

#ifndef GENERIC_LOGGER_DEFAULT_BUFFER_FLUSH_SIZE
#define GENERIC_LOGGER_DEFAULT_BUFFER_FLUSH_SIZE 1
#endif

#ifndef GENERIC_LOGGER_DEFAULT_FILE_ROTATION_SIZE
#define GENERIC_LOGGER_DEFAULT_FILE_ROTATION_SIZE 0 // 0 means no rotation (in bytes)
#endif

#ifndef GENERIC_LOGGER_DEFAULT_FILE_ROTATION_LIMIT
#define GENERIC_LOGGER_DEFAULT_FILE_ROTATION_LIMIT 1
#endif

#ifndef GENERIC_LOGGER_DEFAULT_TIMESTAMP_LENGTH
#define GENERIC_LOGGER_DEFAULT_TIMESTAMP_LENGTH 26
#endif

#ifndef GENERIC_LOGGER_DEFAULT_PROCESS_ID_LENGTH
#define GENERIC_LOGGER_DEFAULT_PROCESS_ID_LENGTH 6
#endif

#ifndef GENERIC_LOGGER_DEFAULT_THREAD_ID_LENGTH
#define GENERIC_LOGGER_DEFAULT_THREAD_ID_LENGTH 6
#endif

#ifndef GENERIC_LOGGER_DEFAULT_FILE_NAME_LENGTH
#define GENERIC_LOGGER_DEFAULT_FILE_NAME_LENGTH 20
#endif

#ifndef GENERIC_LOGGER_DEFAULT_LINE_LENGTH
#define GENERIC_LOGGER_DEFAULT_LINE_LENGTH 6
#endif

#ifndef GENERIC_LOGGER_DEFAULT_FUNCTION_LENGTH
#define GENERIC_LOGGER_DEFAULT_FUNCTION_LENGTH 20
#endif

#ifndef GENERIC_LOGGER_DEFAULT_SEPARATOR
#define GENERIC_LOGGER_DEFAULT_SEPARATOR " | "
#endif

#ifndef GENERIC_LOGGER_DEFAULT_HEADER_UNDERLINE_SEPARATOR
#define GENERIC_LOGGER_DEFAULT_HEADER_UNDERLINE_SEPARATOR "-+-"
#endif

#ifndef GENERIC_LOGGER_DEFAULT_TIMESTAMP_FORMAT
#define GENERIC_LOGGER_DEFAULT_TIMESTAMP_FORMAT "%Y-%m-%d %H:%M:%S.%.6S"
#endif

#ifndef GENERIC_LOGGER_DEFAULT_TIMESTAMP_HEADER
#define GENERIC_LOGGER_DEFAULT_TIMESTAMP_HEADER "Timestamp"
#endif

#ifndef GENERIC_LOGGER_DEFAULT_PROCESS_ID_HEADER
#define GENERIC_LOGGER_DEFAULT_PROCESS_ID_HEADER "PID"
#endif

#ifndef GENERIC_LOGGER_DEFAULT_THREAD_ID_HEADER
#define GENERIC_LOGGER_DEFAULT_THREAD_ID_HEADER "TID"
#endif

#ifndef GENERIC_LOGGER_DEFAULT_FILE_NAME_HEADER
#define GENERIC_LOGGER_DEFAULT_FILE_NAME_HEADER "File Name"
#endif

#ifndef GENERIC_LOGGER_DEFAULT_LINE_HEADER
#define GENERIC_LOGGER_DEFAULT_LINE_HEADER "Line"
#endif

#ifndef GENERIC_LOGGER_DEFAULT_FUNCTION_HEADER
#define GENERIC_LOGGER_DEFAULT_FUNCTION_HEADER "Function"
#endif

#ifndef GENERIC_LOGGER_DEFAULT_MESSAGE_HEADER
#define GENERIC_LOGGER_DEFAULT_MESSAGE_HEADER "Message"
#endif

#ifndef GENERIC_LOGGER_DEFAULT_META_DATA_COLUMNS
#if GENERIC_LOGGER_HIDE_SOURCE_INFO
#define GENERIC_LOGGER_DEFAULT_META_DATA_COLUMNS \
    Generic::logger::meta_data::timestamp, \
    Generic::logger::meta_data::process_id, \
    Generic::logger::meta_data::thread_id, \
    Generic::logger::meta_data::level
#else
#define GENERIC_LOGGER_DEFAULT_META_DATA_COLUMNS \
    Generic::logger::meta_data::timestamp, \
    Generic::logger::meta_data::process_id, \
    Generic::logger::meta_data::thread_id, \
    Generic::logger::meta_data::level, \
    Generic::logger::meta_data::file_name, \
    Generic::logger::meta_data::line, \
    Generic::logger::meta_data::function
#endif
#endif

#if GENERIC_LOGGER_HIDE_SOURCE_INFO
#define GENERIC_LOG_FORMAT(file, level, ...) \
    Generic::logger::get_instance().writef(file, level, "", 0, "", __VA_ARGS__)

#define GENERIC_LOG_STREAM(file, level, message) \
    Generic::logger::get_instance().stream(file, level, "", 0, "") << message
#else
#define GENERIC_LOG_FORMAT(file, level, ...) \
    Generic::logger::get_instance().writef(file, level, __FILE__, __LINE__, __func__, __VA_ARGS__)

#define GENERIC_LOG_STREAM(file, level, message) \
    Generic::logger::get_instance().stream(file, level, __FILE__, __LINE__, __func__) << message
#endif

#define GENERIC_LOG_FORMAT_NONE(file, ...)      GENERIC_LOG_FORMAT(file, Generic::logger::level::none, __VA_ARGS__)
#define GENERIC_LOG_FORMAT_FATAL(file, ...)     GENERIC_LOG_FORMAT(file, Generic::logger::level::fatal, __VA_ARGS__)
#define GENERIC_LOG_FORMAT_CRITICAL(file, ...)  GENERIC_LOG_FORMAT(file, Generic::logger::level::critical, __VA_ARGS__)
#define GENERIC_LOG_FORMAT_ERROR(file, ...)     GENERIC_LOG_FORMAT(file, Generic::logger::level::error, __VA_ARGS__)
#define GENERIC_LOG_FORMAT_WARNING(file, ...)   GENERIC_LOG_FORMAT(file, Generic::logger::level::warning, __VA_ARGS__)
#define GENERIC_LOG_FORMAT_NOTICE(file, ...)    GENERIC_LOG_FORMAT(file, Generic::logger::level::notice, __VA_ARGS__)
#define GENERIC_LOG_FORMAT_INFO(file, ...)      GENERIC_LOG_FORMAT(file, Generic::logger::level::info, __VA_ARGS__)
#define GENERIC_LOG_FORMAT_DEBUG(file, ...)     GENERIC_LOG_FORMAT(file, Generic::logger::level::debug, __VA_ARGS__)
#define GENERIC_LOG_FORMAT_TRACE(file, ...)     GENERIC_LOG_FORMAT(file, Generic::logger::level::trace, __VA_ARGS__)
#define GENERIC_LOG_FORMAT_VERBOSE(file, ...)   GENERIC_LOG_FORMAT(file, Generic::logger::level::verbose, __VA_ARGS__)

#define GENERIC_LOG_STREAM_NONE(file, message)      GENERIC_LOG_STREAM(file, Generic::logger::level::none, message)
#define GENERIC_LOG_STREAM_FATAL(file, message)     GENERIC_LOG_STREAM(file, Generic::logger::level::fatal, message)
#define GENERIC_LOG_STREAM_CRITICAL(file, message)  GENERIC_LOG_STREAM(file, Generic::logger::level::critical, message)
#define GENERIC_LOG_STREAM_ERROR(file, message)     GENERIC_LOG_STREAM(file, Generic::logger::level::error, message)
#define GENERIC_LOG_STREAM_WARNING(file, message)   GENERIC_LOG_STREAM(file, Generic::logger::level::warning, message)
#define GENERIC_LOG_STREAM_NOTICE(file, message)    GENERIC_LOG_STREAM(file, Generic::logger::level::notice, message)
#define GENERIC_LOG_STREAM_INFO(file, message)      GENERIC_LOG_STREAM(file, Generic::logger::level::info, message)
#define GENERIC_LOG_STREAM_DEBUG(file, message)     GENERIC_LOG_STREAM(file, Generic::logger::level::debug, message)
#define GENERIC_LOG_STREAM_TRACE(file, message)     GENERIC_LOG_STREAM(file, Generic::logger::level::trace, message)
#define GENERIC_LOG_STREAM_VERBOSE(file, message)   GENERIC_LOG_STREAM(file, Generic::logger::level::verbose, message)

namespace Generic
{
    class logger
    {
    public:
        enum class level : unsigned char
        {
            off = 0,    // Disable logging.
            none,       // No level specified. Always log if logging is enabled.
            fatal,      // Issues which break the application or a large portion of it.
            critical,   // Issues which cause high impact or loss of functionality.
            error,      // Issues which have a noticeable impact but do not affect functionality.
            warning,    // Issues which should not be noticed or have been mitigated.
            notice,     // Strange or significant behaviour that is not an issue by itself.
            info,       // Important updates for tracking activity.
            debug,      // Helpful updates for more in depth tracking.
            trace,      // Specialised step-by-step tracking updates.
            verbose,    // Very informative and noisy updates.
            header      // Reserved for header info.
        };

        enum class level_format : unsigned char
        {
            full = 0,
            abbreviated,
            single_char
        };

        enum class meta_data : unsigned char
        {
            timestamp = 0,
            process_id,
            thread_id,
            level,
            file_name,
            line,
            function
        };

    private:
        class streamer
        {
            logger* const       m_logger;
            const std::string   m_logFileName;
            const level         m_logLevel;
            const char* const   m_sourceFilePath;
            const int           m_sourceLine;
            const char* const   m_sourceFunction;
            std::stringstream   m_stream;

        public:
            streamer(
                logger* const       logger,
                const std::string   logFileName,
                const level         logLevel,
                const char* const   sourceFilePath,
                const int           sourceLine,
                const char* const   sourceFunction) :
                m_logger        { logger },
                m_logFileName   { logFileName },
                m_logLevel      { logLevel },
                m_sourceFilePath{ sourceFilePath },
                m_sourceLine    { sourceLine },
                m_sourceFunction{ sourceFunction },
                m_stream        {} {}

            ~streamer()
            {
                try
                {
                    if (m_logger)
                    {
                        m_logger->write(
                            m_logFileName,
                            m_logLevel,
                            m_sourceFilePath,
                            m_sourceLine,
                            m_sourceFunction,
                            m_stream.str());
                    }
                }
                catch (...) {}
            }

            streamer& operator<<(const bool b)
            {
                m_stream << std::boolalpha << b;
                return *this;
            }

            template<class T>
            streamer& operator<<(const T& value)
            {
                m_stream << value;
                return *this;
            }
        };

        struct log
        {
            std::string     timestamp;
            std::thread::id threadID;
            level           logLevel;
            const char*     sourceFilePath;
            int             sourceLine;
            const char*     sourceFunction;
            std::string     message;

            log(
                const std::string&      timestamp,
                const std::thread::id&  threadID,
                const level             logLevel,
                const char*             sourceFilePath,
                const int               sourceLine,
                const char*             sourceFunction,
                const std::string&      message) :
                timestamp       { timestamp },
                threadID        { threadID },
                logLevel        { logLevel },
                sourceFilePath  { sourceFilePath },
                sourceLine      { sourceLine },
                sourceFunction  { sourceFunction },
                message         { message } {}

            ~log() {}
        };

        typedef std::list<log> log_buffer;

        struct file_info
        {
            log_buffer                  buffer;
            Generic::filesystem::path   filePath;
            bool                        dirsCreated;

            file_info() :
                buffer{},
                filePath{},
                dirsCreated{ false } {}
        };

        mutable std::mutex                  m_loggingMutex{};
        std::thread                         m_loggingThread{};
        std::condition_variable             m_loggingThreadCondition{};
        std::map<std::string, file_info>    m_logFiles{};

#ifdef _WIN32
        const int m_processID{ _getpid() };
#else
        const int m_processID{ getpid() };
#endif

        std::atomic_bool            m_isLogging             { true };
        std::atomic<level>          m_logLevel              { GENERIC_LOGGER_DEFAULT_LOG_LEVEL };
        std::atomic<level_format>   m_logLevelFormat        { GENERIC_LOGGER_DEFAULT_LOG_LEVEL_FORMAT };
        std::atomic_bool            m_createDirs            { GENERIC_LOGGER_DEFAULT_CREATE_DIRS };
        std::atomic_bool            m_writeHeader           { GENERIC_LOGGER_DEFAULT_WRITE_HEADER };
        std::atomic_bool            m_writeHeaderUnderline  { GENERIC_LOGGER_DEFAULT_WRITE_HEADER_UNDERLINE };
        std::atomic_char            m_headerUnderlineFill   { GENERIC_LOGGER_DEFAULT_HEADER_UNDERLINE_FILL };
        std::atomic_size_t          m_bufferMaxSize         { GENERIC_LOGGER_DEFAULT_BUFFER_MAX_SIZE };
        std::atomic_size_t          m_bufferFlushSize       { GENERIC_LOGGER_DEFAULT_BUFFER_FLUSH_SIZE };
        std::atomic_size_t          m_fileRotationSize      { GENERIC_LOGGER_DEFAULT_FILE_ROTATION_SIZE };
        std::atomic_size_t          m_fileRotationLimit     { GENERIC_LOGGER_DEFAULT_FILE_ROTATION_LIMIT };
        std::atomic_size_t          m_numDiscardedLogs      { 0 };
        std::atomic_size_t          m_timestampLength       { GENERIC_LOGGER_DEFAULT_TIMESTAMP_LENGTH };
        std::atomic_size_t          m_processIDLength       { GENERIC_LOGGER_DEFAULT_PROCESS_ID_LENGTH };
        std::atomic_size_t          m_threadIDLength        { GENERIC_LOGGER_DEFAULT_THREAD_ID_LENGTH };
        std::atomic_size_t          m_fileNameLength        { GENERIC_LOGGER_DEFAULT_FILE_NAME_LENGTH };
        std::atomic_size_t          m_lineLength            { GENERIC_LOGGER_DEFAULT_LINE_LENGTH };
        std::atomic_size_t          m_functionLength        { GENERIC_LOGGER_DEFAULT_FUNCTION_LENGTH };

        mutable std::mutex      m_configMutex{};
        std::string             m_separator                 { GENERIC_LOGGER_DEFAULT_SEPARATOR };
        std::string             m_headerUnderlineSeparator  { GENERIC_LOGGER_DEFAULT_HEADER_UNDERLINE_SEPARATOR };
        std::string             m_timestampFormat           { GENERIC_LOGGER_DEFAULT_TIMESTAMP_FORMAT };
        std::string             m_timestampHeader           { GENERIC_LOGGER_DEFAULT_TIMESTAMP_HEADER };
        std::string             m_processIDHeader           { GENERIC_LOGGER_DEFAULT_PROCESS_ID_HEADER };
        std::string             m_threadIDHeader            { GENERIC_LOGGER_DEFAULT_THREAD_ID_HEADER };
        std::string             m_fileNameHeader            { GENERIC_LOGGER_DEFAULT_FILE_NAME_HEADER };
        std::string             m_lineHeader                { GENERIC_LOGGER_DEFAULT_LINE_HEADER };
        std::string             m_functionHeader            { GENERIC_LOGGER_DEFAULT_FUNCTION_HEADER };
        std::string             m_messageHeader             { GENERIC_LOGGER_DEFAULT_MESSAGE_HEADER };
        std::vector<meta_data>  m_metaDataColumns           { GENERIC_LOGGER_DEFAULT_META_DATA_COLUMNS };

#if GENERIC_LOGGER_NO_SINGLETON
    public:
#endif
        logger()
        {
            m_loggingThread = std::thread(&logger::start_logging, this);
        }

        ~logger()
        {
            m_isLogging.store(false);
            m_loggingThreadCondition.notify_all();

            if (m_loggingThread.joinable())
            {
                m_loggingThread.join();
            }

            // Write all buffers to their files
            for (auto& logFilePair : m_logFiles)
            {
                auto& fileName      { logFilePair.first };
                auto& buffer        { logFilePair.second.buffer };
                auto& filePath      { logFilePair.second.filePath };
                auto& dirsCreated   { logFilePair.second.dirsCreated };

                if (!buffer.empty())
                {
                    write_buffer_to_file(buffer.begin(), --(buffer.end()), fileName, filePath, dirsCreated);
                }
            }
        }

    public:
        logger(const logger&) = delete;

        void operator=(const logger&) = delete;

        static logger& get_instance()
        {
            static logger instance{};
            return instance;
        }

        static inline std::string get_local_timestamp(const char* const format)
        {
            const auto nowTime{ std::chrono::system_clock::now() };
            const auto nowPosixTime{ std::chrono::system_clock::to_time_t(nowTime) };

            std::tm nowLocalTime{};
#ifdef _WIN32
            if (localtime_s(&nowLocalTime, &nowPosixTime) == 0)
#else
            if (localtime_r(&nowPosixTime, &nowLocalTime) != nullptr)
#endif
            {
                std::string formatCopy{ format };

                for (std::size_t i{ 0 }; (i + 3) < formatCopy.size(); ++i)
                {
                    if (formatCopy[i] == '%' && formatCopy[i + 1] == '.' && formatCopy[i + 3] == 'S')
                    {
                        const auto precision{ static_cast<std::size_t>(formatCopy[i + 2]) - '0' };

                        if (0 < precision && precision < 10)
                        {
                            const auto nowNanoseconds{ std::chrono::duration_cast<std::chrono::nanoseconds>(
                                nowTime.time_since_epoch()).count() % 1'000'000'000 };

                            formatCopy.replace(i, 4, std::to_string(nowNanoseconds), 0, precision);
                        }
                    }
                }

                std::ostringstream ss{};
                ss << std::put_time(&nowLocalTime, formatCopy.c_str());
                return ss.str();
            }

            return {};
        }

        static inline std::string get_file_name(const char* const filePath)
        {
            return Generic::filesystem::path{ filePath }.filename().string();
        }

        static inline std::string level_to_string(const level level, const level_format levelFormat)
        {
            switch (levelFormat)
            {
                case level_format::full:
                    switch (level)
                    {
                        case level::none:       return "        ";
                        case level::fatal:      return "Fatal   ";
                        case level::critical:   return "Critical";
                        case level::error:      return "Error   ";
                        case level::warning:    return "Warning ";
                        case level::notice:     return "Notice  ";
                        case level::info:       return "Info    ";
                        case level::debug:      return "Debug   ";
                        case level::trace:      return "Trace   ";
                        case level::verbose:    return "Verbose ";
                        case level::header:     return "Level   ";
                        default:                return "Unknown ";
                    }

                case level_format::abbreviated:
                    switch (level)
                    {
                        case level::none:       return "   ";
                        case level::fatal:      return "FTL";
                        case level::critical:   return "CRT";
                        case level::error:      return "ERR";
                        case level::warning:    return "WRN";
                        case level::notice:     return "NTC";
                        case level::info:       return "INF";
                        case level::debug:      return "DBG";
                        case level::trace:      return "TRC";
                        case level::verbose:    return "VRB";
                        case level::header:     return "LVL";
                        default:                return "UNK";
                    }

                case level_format::single_char:
                    switch (level)
                    {
                        case level::none:       return " ";
                        case level::fatal:      return "F";
                        case level::critical:   return "C";
                        case level::error:      return "E";
                        case level::warning:    return "W";
                        case level::notice:     return "N";
                        case level::info:       return "I";
                        case level::debug:      return "D";
                        case level::trace:      return "T";
                        case level::verbose:    return "V";
                        case level::header:     return "L";
                        default:                return "?";
                    }

                default: return "Bad Format";
            }
        }

        int process_id()                    const { return m_processID; }
        bool is_logging()                   const { return m_isLogging.load(); }
        level log_level()                   const { return m_logLevel.load(); }
        level_format log_level_format()     const { return m_logLevelFormat.load(); }
        bool create_dirs()                  const { return m_createDirs.load(); }
        bool write_header()                 const { return m_writeHeader.load(); }
        bool write_header_underline()       const { return m_writeHeaderUnderline.load(); }
        char header_underline_fill()        const { return m_headerUnderlineFill.load(); }
        std::size_t buffer_max_size()       const { return m_bufferMaxSize.load(); }
        std::size_t buffer_flush_size()     const { return m_bufferFlushSize.load(); }
        std::size_t file_rotation_size()    const { return m_fileRotationSize.load(); }
        std::size_t file_rotation_limit()   const { return m_fileRotationLimit.load(); }
        std::size_t num_discarded_logs()    const { return m_numDiscardedLogs.load(); }
        std::size_t timestamp_length()      const { return m_timestampLength.load(); }
        std::size_t process_id_length()     const { return m_processIDLength.load(); }
        std::size_t thread_id_length()      const { return m_threadIDLength.load(); }
        std::size_t file_name_length()      const { return m_fileNameLength.load(); }
        std::size_t line_length()           const { return m_lineLength.load(); }
        std::size_t function_length()       const { return m_functionLength.load(); }

        std::string separator() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_separator;
        }

        std::string header_underline_separator() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_headerUnderlineSeparator;
        }

        std::string timestamp_format() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_timestampFormat;
        }

        std::string timestamp_header() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_timestampHeader;
        }

        std::string process_id_header() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_processIDHeader;
        }

        std::string thread_id_header() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_threadIDHeader;
        }

        std::string file_name_header() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_fileNameHeader;
        }

        std::string line_header() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_lineHeader;
        }

        std::string function_header() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_functionHeader;
        }

        std::string message_header() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_messageHeader;
        }

        std::vector<meta_data> meta_data_columns() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_metaDataColumns;
        }

        logger& log_level(const level l)                    { m_logLevel.store(l);              return *this; }
        logger& log_level_format(const level_format lf)     { m_logLevelFormat.store(lf);       return *this; }
        logger& create_dirs(const bool b)                   { m_createDirs.store(b);            return *this; }
        logger& write_header(const bool b)                  { m_writeHeader.store(b);           return *this; }
        logger& write_header_underline(const bool b)        { m_writeHeaderUnderline.store(b);  return *this; }
        logger& header_underline_fill(const char c)         { m_headerUnderlineFill.store(c);   return *this; }
        logger& buffer_max_size(const std::size_t s)        { m_bufferMaxSize.store(s);         return *this; }

        logger& buffer_flush_size(const std::size_t s)
        {
            m_bufferFlushSize.store(s);
            m_loggingThreadCondition.notify_one();  // wake the logging thread
            return *this;
        }

        logger& file_rotation_size(const std::size_t s)     { m_fileRotationSize.store(s);  return *this; }
        logger& file_rotation_limit(const std::size_t s)    { m_fileRotationLimit.store(s); return *this; }
        logger& reset_num_discarded_logs()                  { m_numDiscardedLogs.store(0);  return *this; }
        logger& timestamp_length(const std::size_t s)       { m_timestampLength.store(s);   return *this; }
        logger& process_id_length(const std::size_t s)      { m_processIDLength.store(s);   return *this; }
        logger& thread_id_length(const std::size_t s)       { m_threadIDLength.store(s);    return *this; }
        logger& file_name_length(const std::size_t s)       { m_fileNameLength.store(s);    return *this; }
        logger& line_length(const std::size_t s)            { m_lineLength.store(s);        return *this; }
        logger& function_length(const std::size_t s)        { m_functionLength.store(s);    return *this; }

        logger& separator(const std::string& s)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_separator = s;
            return *this;
        }

        logger& header_underline_separator(const std::string& s)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_headerUnderlineSeparator = s;
            return *this;
        }

        logger& timestamp_format(const std::string& s)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_timestampFormat = s;
            return *this;
        }

        logger& timestamp_header(const std::string& s)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_timestampHeader = s;
            return *this;
        }

        logger& process_id_header(const std::string& s)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_processIDHeader = s;
            return *this;
        }

        logger& thread_id_header(const std::string& s)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_threadIDHeader = s;
            return *this;
        }

        logger& file_name_header(const std::string& s)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_fileNameHeader = s;
            return *this;
        }

        logger& line_header(const std::string& s)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_lineHeader = s;
            return *this;
        }

        logger& function_header(const std::string& s)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_functionHeader = s;
            return *this;
        }

        logger& message_header(const std::string& s)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_messageHeader = s;
            return *this;
        }

        logger& meta_data_columns(const std::vector<meta_data>& v)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_metaDataColumns = v;
            return *this;
        }

        template<typename ...Ts>
        logger& meta_data_columns(const Ts... ts)
        {
            return meta_data_columns({ ts... });
        }

        bool should_log(const level logLevel) const
        {
            return (is_logging() && logLevel <= level());
        }

        void writef(
            const std::string&  logFileName,
            const level         logLevel,
            const char* const   sourceFilePath,
            const int           sourceLine,
            const char* const   sourceFunction,
            const char* const   format,
            ...)
        {
            if (should_log(logLevel))
            {
                // Message character limit is 8192
                va_list args;
                va_start(args, format);
                char buffer[8192]{};

                try
                {
                    // Create message from format and args
                    if (vsnprintf(buffer, (sizeof(buffer) / sizeof(buffer[0])), format, args) < 0)
                    {
                        buffer[0] = '\0';
                    }
                }
                catch (...) { buffer[0] = '\0'; }

                va_end(args);

                // Write message, or use format if message creation failed
                add_entry_to_buffer(
                    logFileName,
                    logLevel,
                    sourceFilePath,
                    sourceLine,
                    sourceFunction,
                    (buffer[0] == '\0') ? format : buffer);
            }
        }

        void write(
            const std::string&  logFileName,
            const level         logLevel,
            const char* const   sourceFilePath,
            const int           sourceLine,
            const char* const   sourceFunction,
            const std::string&  message)
        {
            if (should_log(logLevel))
            {
                add_entry_to_buffer(logFileName, logLevel, sourceFilePath, sourceLine, sourceFunction, message);
            }
        }

        streamer stream(
            const std::string&  logFileName,
            const level         logLevel,
            const char* const   sourceFilePath,
            const int           sourceLine,
            const char* const   sourceFunction)
        {
            return streamer{ this, logFileName, logLevel, sourceFilePath, sourceLine, sourceFunction };
        }

    private:
        void add_entry_to_buffer(
            const std::string&  logFileName,
            const level         logLevel,
            const char* const   sourceFilePath,
            const int           sourceLine,
            const char* const   sourceFunction,
            const std::string&  message)
        {
            const auto timestamp{ get_local_timestamp(timestamp_format().c_str()) };

            const auto threadID{ std::this_thread::get_id() };

            std::unique_lock<std::mutex> lock{ m_loggingMutex };

            auto it{ m_logFiles.find(logFileName) };
            if (it == m_logFiles.end())
            {
                it = m_logFiles.emplace(logFileName, file_info{}).first;
            }

            auto& buffer{ it->second.buffer };
            auto bufferMaxSize{ this->buffer_max_size() };

            if (bufferMaxSize == 0 || buffer.size() < bufferMaxSize)
            {
                buffer.emplace_back(
                    timestamp,
                    threadID,
                    logLevel,
                    sourceFilePath,
                    sourceLine,
                    sourceFunction,
                    message);

                if (buffer_flush_size() <= buffer.size())
                {
                    // Unlock the mutex and wake the logging thread
                    lock.unlock();
                    m_loggingThreadCondition.notify_one();
                }
            }
            else
            {
                // Queue is full, discard log
                ++m_numDiscardedLogs;
            }
        }

        void rotate_file(const Generic::filesystem::path& filePath) const
        {
            const auto stem{ filePath.stem().string() };
            const auto extension{ filePath.extension().string() };
            const auto parentPath{ filePath.parent_path() };
            const auto fileRotationLimit{ this->file_rotation_limit() };

            std::size_t numFiles{ 0 };
            for (std::size_t i{ 0 }; ; ++i)
            {
                const auto thisStem{ stem + ((i == 0) ? "" : ("_" + std::to_string(i))) };
                const auto thisPath{ parentPath / (thisStem + extension) };

                if (!Generic::filesystem::exists(thisPath))
                {
                    break;
                }

                if (i < fileRotationLimit)
                {
                    ++numFiles;
                    continue;
                }

                Generic::filesystem::remove(thisPath);
            }

            for (auto i{ numFiles }; 0 < i; )
            {
                const auto newStem{ stem + "_" + std::to_string(i) };
                const auto newPath{ parentPath / (newStem + extension) };

                --i;

                const auto oldStem{ stem + ((i == 0) ? "" : ("_" + std::to_string(i))) };
                const auto oldPath{ parentPath / (oldStem + extension) };

                Generic::filesystem::rename(oldPath, newPath);
            }
        }

        void open_file_stream(std::ofstream& fileStream, const Generic::filesystem::path& filePath) const
        {
            fileStream.open(filePath, (std::ios_base::ate | std::ios_base::app));

            if (!fileStream.is_open() || !fileStream.good())
            {
                throw Generic::filesystem::filesystem_error{ "Logger failed to open file",
                    std::make_error_code(std::errc::io_error) };
            }
        }

        void write_header_to_stream(std::ostream& stream) const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };

            const auto levelHeader{ level_to_string(level::header, level_format()) };

            stream << std::left << std::setfill(' ');

            for (const auto metaDataColumn : m_metaDataColumns)
            {
                switch (metaDataColumn)
                {
                case meta_data::timestamp:
                    stream << std::setw(timestamp_length()) << m_timestampHeader << m_separator;
                    break;

                case meta_data::process_id:
                    stream << std::setw(process_id_length()) << m_processIDHeader << m_separator;
                    break;

                case meta_data::thread_id:
                    stream << std::setw(thread_id_length()) << m_threadIDHeader << m_separator;
                    break;

                case meta_data::level:
                    stream << levelHeader << m_separator;
                    break;

                case meta_data::file_name:
                    stream << std::setw(file_name_length()) << m_fileNameHeader << m_separator;
                    break;

                case meta_data::line:
                    stream << std::setw(line_length()) << m_lineHeader << m_separator;
                    break;

                case meta_data::function:
                    stream << std::setw(function_length()) << m_functionHeader << m_separator;
                    break;
                }
            }

            stream << m_messageHeader << '\n';

            if (write_header_underline())
            {
                stream << std::left << std::setfill(header_underline_fill());

                for (const auto metaDataColumn : m_metaDataColumns)
                {
                    switch (metaDataColumn)
                    {
                    case meta_data::timestamp:
                        stream << std::setw(timestamp_length()) << "" << m_headerUnderlineSeparator;
                        break;

                    case meta_data::process_id:
                        stream << std::setw(process_id_length()) << "" << m_headerUnderlineSeparator;
                        break;

                    case meta_data::thread_id:
                        stream << std::setw(thread_id_length()) << "" << m_headerUnderlineSeparator;
                        break;

                    case meta_data::level:
                        stream << std::setw(levelHeader.size()) << "" << m_headerUnderlineSeparator;
                        break;

                    case meta_data::file_name:
                        stream << std::setw(file_name_length()) << "" << m_headerUnderlineSeparator;
                        break;

                    case meta_data::line:
                        stream << std::setw(line_length()) << "" << m_headerUnderlineSeparator;
                        break;

                    case meta_data::function:
                        stream << std::setw(function_length()) << "" << m_headerUnderlineSeparator;
                        break;
                    }
                }

                stream << std::setw(m_messageHeader.size()) << "" << '\n';
            }
        }

        void write_entry_to_stream(std::ostream& stream, const log& log) const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };

            stream << std::left << std::setfill(' ');

            for (const auto metaDataColumn : m_metaDataColumns)
            {
                switch (metaDataColumn)
                {
                case meta_data::timestamp:
                    stream << std::setw(timestamp_length()) << log.timestamp << m_separator;
                    break;

                case meta_data::process_id:
                    stream << std::setw(process_id_length()) << m_processID << m_separator;
                    break;

                case meta_data::thread_id:
                    stream << std::setw(thread_id_length()) << log.threadID << m_separator;
                    break;

                case meta_data::level:
                    stream << level_to_string(log.logLevel, log_level_format()) << m_separator;
                    break;

                case meta_data::file_name:
                {
                    const auto fileNameLength{ this->file_name_length() };

                    stream << std::setw(fileNameLength)
                        << std::string(get_file_name(log.sourceFilePath), 0, fileNameLength) << m_separator;
                    break;
                }

                case meta_data::line:
                    stream << std::setw(line_length()) << log.sourceLine << m_separator;
                    break;

                case meta_data::function:
                {
                    const auto functionLength{ this->function_length() };

                    stream << std::setw(functionLength)
                        << std::string(log.sourceFunction, 0, functionLength) << m_separator;
                    break;
                }
                }
            }

            stream << log.message << '\n';
        }

        bool write_buffer_to_file(
            const log_buffer::iterator  begin,
            const log_buffer::iterator  secondToEnd,
            const std::string&          fileName,
            Generic::filesystem::path&  filePath,
            bool&                       dirsCreated) const
        {
            auto result{ true };

            try
            {
                // Get file path if empty
                if (filePath.empty())
                {
                    filePath = Generic::filesystem::absolute(fileName);
                }

                // Create path to file if needed
                if (create_dirs() && !dirsCreated)
                {
                    Generic::filesystem::create_directories(filePath.parent_path());
                    dirsCreated = true;
                }

                const auto writeHeader{ this->write_header() };
                const auto fileRotationSize{ this->file_rotation_size() };

                std::size_t fileSize{ 0 };
                std::ofstream fileStream{};
                open_file_stream(fileStream, filePath);

                for (auto it{ begin }; ; ++it)
                {
                    fileSize = static_cast<std::size_t>(fileStream.tellp());

                    // Rotate file if needed
                    if (fileRotationSize != 0 && fileRotationSize <= fileSize)
                    {
                        fileStream.close();
                        rotate_file(filePath);
                        open_file_stream(fileStream, filePath);
                        fileSize = static_cast<std::size_t>(fileStream.tellp());
                    }

                    // Write header if needed
                    if (writeHeader && fileSize == 0)
                    {
                        write_header_to_stream(fileStream);
                    }

                    write_entry_to_stream(fileStream, *it);

                    if (it == secondToEnd)
                    {
                        break;
                    }
                }
            }
            catch (const Generic::filesystem::filesystem_error&)
            {
                result = false;
            }

            return result;
        }

        void start_logging()
        {
            bool shouldWait{ false };
            std::unique_lock<std::mutex> lock{ m_loggingMutex };

            while (m_isLogging.load())
            {
                if (shouldWait)
                {
                    m_loggingThreadCondition.wait(lock);
                    shouldWait = false;
                }
                else
                {
                    shouldWait = true;

                    for (auto& logFilePair : m_logFiles)
                    {
                        auto& fileName      { logFilePair.first };
                        auto& buffer        { logFilePair.second.buffer };
                        auto& filePath      { logFilePair.second.filePath };
                        auto& dirsCreated   { logFilePair.second.dirsCreated };

                        if (!buffer.empty() && buffer_flush_size() <= buffer.size())
                        {
                            const auto begin        { buffer.begin() };
                            const auto secondToEnd  { --(buffer.end()) };

                            // Doesn't require synchronization.
                            // Since this thread stays within the range gotten when locked
                            // and other threads only add after second to end, unlocking is fine.
                            lock.unlock();

                            // Since other threads can add logs, don't wait when done.
                            shouldWait = false;

                            const auto result{ write_buffer_to_file(
                                begin, secondToEnd, fileName, filePath, dirsCreated) };

                            lock.lock();

                            // Erase the logs after re-locking.
                            if (result)
                            {
                                buffer.erase(begin, std::next(secondToEnd));
                            }
                        }
                    }
                }
            }
        }
    };
}
