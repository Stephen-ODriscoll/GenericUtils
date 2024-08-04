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

#include "FileSystem.hpp"

// Configurable with macro
#ifndef GENERIC_LOGGER_HIDE_SOURCE_INFO
#define GENERIC_LOGGER_HIDE_SOURCE_INFO 0   // Define as 1 or 0
#endif

#ifndef GENERIC_LOGGER_NO_SINGLETON
#define GENERIC_LOGGER_NO_SINGLETON 0   // Define as 1 or 0
#endif

// Configurable with macros or setters
#ifndef GENERIC_LOGGER_DEFAULT_LEVEL
#define GENERIC_LOGGER_DEFAULT_LEVEL Generic::Logger::Level::Verbose
#endif

#ifndef GENERIC_LOGGER_DEFAULT_LEVEL_FORMAT
#define GENERIC_LOGGER_DEFAULT_LEVEL_FORMAT Generic::Logger::LevelFormat::Full
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
#define GENERIC_LOGGER_DEFAULT_TIMESTAMP_LENGTH 24
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
#define GENERIC_LOGGER_DEFAULT_TIMESTAMP_FORMAT "%Y-%m-%d %H:%M:%S.%.4S"
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
    MetaDataColumn::Timestamp, \
    MetaDataColumn::ProcessID, \
    MetaDataColumn::ThreadID, \
    MetaDataColumn::Level
#else
#define GENERIC_LOGGER_DEFAULT_META_DATA_COLUMNS \
    MetaDataColumn::Timestamp, \
    MetaDataColumn::ProcessID, \
    MetaDataColumn::ThreadID, \
    MetaDataColumn::Level, \
    MetaDataColumn::FileName, \
    MetaDataColumn::Line, \
    MetaDataColumn::Function
#endif
#endif

#if GENERIC_LOGGER_HIDE_SOURCE_INFO
#define GENERIC_LOG_FORMAT(file, level, ...) \
    Generic::Logger::getInstance().writef(file, level, "", 0, "", __VA_ARGS__)

#define GENERIC_LOG_STREAM(file, level, message) \
    Generic::Logger::getInstance().stream(file, level, "", 0, "") << message
#else
#define GENERIC_LOG_FORMAT(file, level, ...) \
    Generic::Logger::getInstance().writef(file, level, __FILE__, __LINE__, __func__, __VA_ARGS__)

#define GENERIC_LOG_STREAM(file, level, message) \
    Generic::Logger::getInstance().stream(file, level, __FILE__, __LINE__, __func__) << message
#endif

#define GENERIC_LOG_FORMAT_NONE(file, ...)      GENERIC_LOG_FORMAT(file, Generic::Logger::Level::None, __VA_ARGS__)
#define GENERIC_LOG_FORMAT_FATAL(file, ...)     GENERIC_LOG_FORMAT(file, Generic::Logger::Level::Fatal, __VA_ARGS__)
#define GENERIC_LOG_FORMAT_CRITICAL(file, ...)  GENERIC_LOG_FORMAT(file, Generic::Logger::Level::Critical, __VA_ARGS__)
#define GENERIC_LOG_FORMAT_ERROR(file, ...)     GENERIC_LOG_FORMAT(file, Generic::Logger::Level::Error, __VA_ARGS__)
#define GENERIC_LOG_FORMAT_WARNING(file, ...)   GENERIC_LOG_FORMAT(file, Generic::Logger::Level::Warning, __VA_ARGS__)
#define GENERIC_LOG_FORMAT_NOTICE(file, ...)    GENERIC_LOG_FORMAT(file, Generic::Logger::Level::Notice, __VA_ARGS__)
#define GENERIC_LOG_FORMAT_INFO(file, ...)      GENERIC_LOG_FORMAT(file, Generic::Logger::Level::Info, __VA_ARGS__)
#define GENERIC_LOG_FORMAT_DEBUG(file, ...)     GENERIC_LOG_FORMAT(file, Generic::Logger::Level::Debug, __VA_ARGS__)
#define GENERIC_LOG_FORMAT_TRACE(file, ...)     GENERIC_LOG_FORMAT(file, Generic::Logger::Level::Trace, __VA_ARGS__)
#define GENERIC_LOG_FORMAT_VERBOSE(file, ...)   GENERIC_LOG_FORMAT(file, Generic::Logger::Level::Verbose, __VA_ARGS__)

#define GENERIC_LOG_STREAM_NONE(file, message)      GENERIC_LOG_STREAM(file, Generic::Logger::Level::None, message)
#define GENERIC_LOG_STREAM_FATAL(file, message)     GENERIC_LOG_STREAM(file, Generic::Logger::Level::Fatal, message)
#define GENERIC_LOG_STREAM_CRITICAL(file, message)  GENERIC_LOG_STREAM(file, Generic::Logger::Level::Critical, message)
#define GENERIC_LOG_STREAM_ERROR(file, message)     GENERIC_LOG_STREAM(file, Generic::Logger::Level::Error, message)
#define GENERIC_LOG_STREAM_WARNING(file, message)   GENERIC_LOG_STREAM(file, Generic::Logger::Level::Warning, message)
#define GENERIC_LOG_STREAM_NOTICE(file, message)    GENERIC_LOG_STREAM(file, Generic::Logger::Level::Notice, message)
#define GENERIC_LOG_STREAM_INFO(file, message)      GENERIC_LOG_STREAM(file, Generic::Logger::Level::Info, message)
#define GENERIC_LOG_STREAM_DEBUG(file, message)     GENERIC_LOG_STREAM(file, Generic::Logger::Level::Debug, message)
#define GENERIC_LOG_STREAM_TRACE(file, message)     GENERIC_LOG_STREAM(file, Generic::Logger::Level::Trace, message)
#define GENERIC_LOG_STREAM_VERBOSE(file, message)   GENERIC_LOG_STREAM(file, Generic::Logger::Level::Verbose, message)

namespace Generic
{
    class Logger
    {
    public:
        enum class Level : unsigned char
        {
            Off = 0,    // Disable logging.
            None,       // No level specified. Always log if logging is enabled.
            Fatal,      // Issues which break the application or a large portion of it.
            Critical,   // Issues which cause high impact or loss of functionality.
            Error,      // Issues which have a noticeable impact but do not affect functionality.
            Warning,    // Issues which should not be noticed or have been mitigated.
            Notice,     // Strange or significant behaviour that is not an issue by itself.
            Info,       // Important updates for tracking activity.
            Debug,      // Helpful updates for more in depth tracking.
            Trace,      // Specialised step-by-step tracking updates.
            Verbose,    // Very informative and noisy updates.
            Header      // Reserved for header info.
        };

        enum class LevelFormat : unsigned char
        {
            Full = 0,
            Short,
            Char
        };

        enum class MetaDataColumn : unsigned char
        {
            Timestamp = 0,
            ProcessID,
            ThreadID,
            Level,
            FileName,
            Line,
            Function
        };

    private:
        struct Log
        {
            std::string     timestamp;
            std::thread::id threadID;
            Level           level;
            std::string     sourceFileName;
            int             sourceLine;
            std::string     sourceFunction;
            std::string     message;

            Log(
                const std::string&      timestamp,
                const std::thread::id&  threadID,
                const Level             level,
                const std::string&      sourceFileName,
                const int               sourceLine,
                const std::string&      sourceFunction,
                const std::string&      message) :
                timestamp       { timestamp },
                threadID        { threadID },
                level           { level },
                sourceFileName  { sourceFileName },
                sourceLine      { sourceLine },
                sourceFunction  { sourceFunction },
                message         { message } {}

            ~Log() {}
        };

        class Stream
        {
            Logger* const       m_logger;
            const std::string   m_logFileName;
            const Level         m_logLevel;
            const char* const   m_sourceFilePath;
            const int           m_sourceLine;
            const char* const   m_sourceFunction;
            std::stringstream   m_stream;

        public:
            Stream(
                Logger* const       logger,
                const std::string   logFileName,
                const Level         logLevel,
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

            ~Stream()
            {
                try
                {
                    if (m_logger && m_logger->shouldLog(m_logLevel))
                    {
                        m_logger->addLogToBuffer(
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

            Stream& operator<<(const bool b)
            {
                m_stream << std::boolalpha << b;
                return *this;
            }

            template<class T>
            Stream& operator<<(const T& value)
            {
                m_stream << value;
                return *this;
            }
        };

        typedef std::list<Log> LogBuffer;

        struct LogFile
        {
            LogBuffer                   buffer;
            Generic::FileSystem::path   filePath;
            bool                        dirsCreated;

            LogFile() :
                buffer      {},
                filePath    {},
                dirsCreated { false } {}
        };

        mutable std::mutex              m_loggingMutex          {};
        std::thread                     m_loggingThread         {};
        std::condition_variable         m_loggingThreadCondition{};
        std::map<std::string, LogFile>  m_logFiles              {};

#ifdef _WIN32
        const int m_processID{ _getpid() };
#else
        const int m_processID{ getpid() };
#endif

        std::atomic_bool            m_isLogging             { true };
        std::atomic<Level>          m_level                 { GENERIC_LOGGER_DEFAULT_LEVEL };
        std::atomic<LevelFormat>    m_levelFormat           { GENERIC_LOGGER_DEFAULT_LEVEL_FORMAT };
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

        mutable std::mutex          m_configMutex               {};
        std::string                 m_separator                 { GENERIC_LOGGER_DEFAULT_SEPARATOR };
        std::string                 m_headerUnderlineSeparator  { GENERIC_LOGGER_DEFAULT_HEADER_UNDERLINE_SEPARATOR };
        std::string                 m_timestampFormat           { GENERIC_LOGGER_DEFAULT_TIMESTAMP_FORMAT };
        std::string                 m_timestampHeader           { GENERIC_LOGGER_DEFAULT_TIMESTAMP_HEADER };
        std::string                 m_processIDHeader           { GENERIC_LOGGER_DEFAULT_PROCESS_ID_HEADER };
        std::string                 m_threadIDHeader            { GENERIC_LOGGER_DEFAULT_THREAD_ID_HEADER };
        std::string                 m_fileNameHeader            { GENERIC_LOGGER_DEFAULT_FILE_NAME_HEADER };
        std::string                 m_lineHeader                { GENERIC_LOGGER_DEFAULT_LINE_HEADER };
        std::string                 m_functionHeader            { GENERIC_LOGGER_DEFAULT_FUNCTION_HEADER };
        std::string                 m_messageHeader             { GENERIC_LOGGER_DEFAULT_MESSAGE_HEADER };
        std::vector<MetaDataColumn> m_metaDataColumns           { GENERIC_LOGGER_DEFAULT_META_DATA_COLUMNS };

#if GENERIC_LOGGER_NO_SINGLETON
    public:
#endif
        Logger()
        {
            m_loggingThread = std::thread(&Logger::startLogging, this);
        }

        ~Logger()
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
                    writeBufferToFile(buffer.begin(), --(buffer.end()), fileName, filePath, dirsCreated);
                }
            }
        }

    public:
        Logger(const Logger&) = delete;

        void operator=(const Logger&) = delete;

        static Logger& getInstance()
        {
            static Logger instance{};
            return instance;
        }

        static inline std::string getLocalTimestamp(const char* const format)
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

        static inline std::string getFileName(const char* const filePath)
        {
            return Generic::FileSystem::path{ filePath }.filename().string();
        }

        static inline std::string levelToString(const Level level, const LevelFormat levelFormat)
        {
            switch (levelFormat)
            {
                case LevelFormat::Full:
                    switch (level)
                    {
                        case Level::None:       return "        ";
                        case Level::Fatal:      return "Fatal   ";
                        case Level::Critical:   return "Critical";
                        case Level::Error:      return "Error   ";
                        case Level::Warning:    return "Warning ";
                        case Level::Notice:     return "Notice  ";
                        case Level::Info:       return "Info    ";
                        case Level::Debug:      return "Debug   ";
                        case Level::Trace:      return "Trace   ";
                        case Level::Verbose:    return "Verbose ";
                        case Level::Header:     return "Level   ";
                        default:                return "Unknown ";
                    }

                case LevelFormat::Short:
                    switch (level)
                    {
                        case Level::None:       return "   ";
                        case Level::Fatal:      return "FTL";
                        case Level::Critical:   return "CRT";
                        case Level::Error:      return "ERR";
                        case Level::Warning:    return "WRN";
                        case Level::Notice:     return "NTC";
                        case Level::Info:       return "INF";
                        case Level::Debug:      return "DBG";
                        case Level::Trace:      return "TRC";
                        case Level::Verbose:    return "VRB";
                        case Level::Header:     return "LVL";
                        default:                return "UNK";
                    }

                case LevelFormat::Char:
                    switch (level)
                    {
                        case Level::None:       return " ";
                        case Level::Fatal:      return "F";
                        case Level::Critical:   return "C";
                        case Level::Error:      return "E";
                        case Level::Warning:    return "W";
                        case Level::Notice:     return "N";
                        case Level::Info:       return "I";
                        case Level::Debug:      return "D";
                        case Level::Trace:      return "T";
                        case Level::Verbose:    return "V";
                        case Level::Header:     return "L";
                        default:                return "?";
                    }

                default: return "Bad Format";
            }
        }

        int processID()                 const   { return m_processID; }
        bool isLogging()                const   { return m_isLogging.load(); }
        Level level()                   const   { return m_level.load(); }
        LevelFormat levelFormat()       const   { return m_levelFormat.load(); }
        bool createDirs()               const   { return m_createDirs.load(); }
        bool writeHeader()              const   { return m_writeHeader.load(); }
        bool writeHeaderUnderline()     const   { return m_writeHeaderUnderline.load(); }
        char headerUnderlineFill()      const   { return m_headerUnderlineFill.load(); }
        std::size_t bufferMaxSize()     const   { return m_bufferMaxSize.load(); }
        std::size_t bufferFlushSize()   const   { return m_bufferFlushSize.load(); }
        std::size_t fileRotationSize()  const   { return m_fileRotationSize.load(); }
        std::size_t fileRotationLimit() const   { return m_fileRotationLimit.load(); }
        std::size_t numDiscardedLogs()  const   { return m_numDiscardedLogs.load(); }
        std::size_t timestampLength()   const   { return m_timestampLength.load(); }
        std::size_t processIDLength()   const   { return m_processIDLength.load(); }
        std::size_t threadIDLength()    const   { return m_threadIDLength.load(); }
        std::size_t fileNameLength()    const   { return m_fileNameLength.load(); }
        std::size_t lineLength()        const   { return m_lineLength.load(); }
        std::size_t functionLength()    const   { return m_functionLength.load(); }

        std::string separator() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_separator;
        }

        std::string headerUnderlineSeparator() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_headerUnderlineSeparator;
        }

        std::string timestampFormat() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_timestampFormat;
        }

        std::string timestampHeader() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_timestampHeader;
        }

        std::string processIDHeader() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_processIDHeader;
        }

        std::string threadIDHeader() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_threadIDHeader;
        }

        std::string fileNameHeader() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_fileNameHeader;
        }

        std::string lineHeader() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_lineHeader;
        }

        std::string functionHeader() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_functionHeader;
        }

        std::string messageHeader() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_messageHeader;
        }

        std::vector<MetaDataColumn> metaDataColumns() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_metaDataColumns;
        }
        
        Logger& level(const Level l)                { m_level.store(l);                 return *this; }
        Logger& levelFormat(const LevelFormat lf)   { m_levelFormat.store(lf);          return *this; }
        Logger& createDirs(const bool b)            { m_createDirs.store(b);            return *this; }
        Logger& writeHeader(const bool b)           { m_writeHeader.store(b);           return *this; }
        Logger& writeHeaderUnderline(const bool b)  { m_writeHeaderUnderline.store(b);  return *this; }
        Logger& headerUnderlineFill(const char c)   { m_headerUnderlineFill.store(c);   return *this; }
        Logger& bufferMaxSize(const std::size_t s)  { m_bufferMaxSize.store(s);         return *this; }

        Logger& bufferFlushSize(const std::size_t s)
        {
            m_bufferFlushSize.store(s);
            m_loggingThreadCondition.notify_one();  // wake the logging thread
            return *this;
        }

        Logger& fileRotationSize(const std::size_t s)   { m_fileRotationSize.store(s);  return *this; }
        Logger& fileRotationLimit(const std::size_t s)  { m_fileRotationLimit.store(s); return *this; }
        Logger& resetNumDiscardedLogs()                 { m_numDiscardedLogs.store(0);  return *this; }
        Logger& timestampLength(const std::size_t s)    { m_timestampLength.store(s);   return *this; }
        Logger& processIDLength(const std::size_t s)    { m_processIDLength.store(s);   return *this; }
        Logger& threadIDLength(const std::size_t s)     { m_threadIDLength.store(s);    return *this; }
        Logger& fileNameLength(const std::size_t s)     { m_fileNameLength.store(s);    return *this; }
        Logger& lineLength(const std::size_t s)         { m_lineLength.store(s);        return *this; }
        Logger& functionLength(const std::size_t s)     { m_functionLength.store(s);    return *this; }
        
        Logger& separator(const std::string& s)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_separator = s;
            return *this;
        }

        Logger& headerUnderlineSeparator(const std::string& s)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_headerUnderlineSeparator = s;
            return *this;
        }

        Logger& timestampFormat(const std::string& s)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_timestampFormat = s;
            return *this;
        }

        Logger& timestampHeader(const std::string& s)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_timestampHeader = s;
            return *this;
        }

        Logger& processIDHeader(const std::string& s)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_processIDHeader = s;
            return *this;
        }

        Logger& threadIDHeader(const std::string& s)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_threadIDHeader = s;
            return *this;
        }

        Logger& fileNameHeader(const std::string& s)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_fileNameHeader = s;
            return *this;
        }

        Logger& lineHeader(const std::string& s)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_lineHeader = s;
            return *this;
        }

        Logger& functionHeader(const std::string& s)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_functionHeader = s;
            return *this;
        }

        Logger& messageHeader(const std::string& s)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_messageHeader = s;
            return *this;
        }

        Logger& metaDataColumns(const std::vector<MetaDataColumn>& v)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_metaDataColumns = v;
            return *this;
        }

        template<typename ...Ts>
        Logger& metaDataColumns(const Ts... ts)
        {
            return metaDataColumns({ ts... });
        }

        bool shouldLog(const Level logLevel) const
        {
            return (isLogging() && logLevel <= level());
        }

        void writef(
            const std::string&  logFileName,
            const Level         logLevel,
            const char* const   sourceFilePath,
            const int           sourceLine,
            const char* const   sourceFunction,
            const char* const   format,
            ...)
        {
            if (shouldLog(logLevel))
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
                addLogToBuffer(
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
            const Level         logLevel,
            const char* const   sourceFilePath,
            const int           sourceLine,
            const char* const   sourceFunction,
            const std::string&  message)
        {
            if (shouldLog(logLevel))
            {
                addLogToBuffer(logFileName, logLevel, sourceFilePath, sourceLine, sourceFunction, message);
            }
        }

        Stream stream(
            const std::string&  logFileName,
            const Level         logLevel,
            const char* const   sourceFilePath,
            const int           sourceLine,
            const char* const   sourceFunction)
        {
            return Stream{ this, logFileName, logLevel, sourceFilePath, sourceLine, sourceFunction };
        }

    private:
        void addLogToBuffer(
            const std::string&  logFileName,
            const Level         logLevel,
            const char* const   sourceFilePath,
            const int           sourceLine,
            const char* const   sourceFunction,
            const std::string&  message)
        {
            const auto timestamp{ getLocalTimestamp(timestampFormat().c_str()) };

            const auto threadID{ std::this_thread::get_id() };

            const auto sourceFileName{ getFileName(sourceFilePath) };

            std::unique_lock<std::mutex> lock{ m_loggingMutex };

            auto it{ m_logFiles.find(logFileName) };
            if (it == m_logFiles.end())
            {
                it = m_logFiles.emplace(logFileName, LogFile{}).first;
            }

            auto& buffer        { it->second.buffer };
            auto bufferMaxSize  { this->bufferMaxSize() };

            if (bufferMaxSize == 0 || buffer.size() < bufferMaxSize)
            {
                buffer.emplace_back(
                    timestamp,
                    threadID,
                    logLevel,
                    sourceFileName,
                    sourceLine,
                    sourceFunction,
                    message);

                if (bufferFlushSize() <= buffer.size())
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

        void rotateFile(const Generic::FileSystem::path& filePath) const
        {
            const auto stem             { filePath.stem().string() };
            const auto extension        { filePath.extension().string() };
            const auto parentPath       { filePath.parent_path() };
            const auto fileRotationLimit{ this->fileRotationLimit() };

            std::size_t numFiles{ 0 };
            for (std::size_t i{ 0 }; ; ++i)
            {
                const auto thisStem{ stem + ((i == 0) ? "" : ("_" + std::to_string(i))) };
                const auto thisPath{ parentPath / (thisStem + extension) };

                if (!Generic::FileSystem::exists(thisPath))
                {
                    break;
                }

                if (i < fileRotationLimit)
                {
                    ++numFiles;
                    continue;
                }

                Generic::FileSystem::remove(thisPath);
            }

            for (auto i{ numFiles }; 0 < i; )
            {
                const auto newStem{ stem + "_" + std::to_string(i) };
                const auto newPath{ parentPath / (newStem + extension) };

                --i;

                const auto oldStem{ stem + ((i == 0) ? "" : ("_" + std::to_string(i))) };
                const auto oldPath{ parentPath / (oldStem + extension) };

                Generic::FileSystem::rename(oldPath, newPath);
            }
        }

        void openFileStream(std::ofstream& fileStream, const Generic::FileSystem::path& filePath) const
        {
            fileStream.open(filePath, (std::ios_base::ate | std::ios_base::app));

            if (!fileStream.is_open() || !fileStream.good())
            {
                throw Generic::FileSystem::filesystem_error{ "Logger failed to open file",
                    std::make_error_code(std::errc::io_error) };
            }
        }

        void writeHeaderToStream(std::ostream& stream) const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };

            const auto levelHeader{ levelToString(Level::Header, levelFormat()) };

            stream << std::left << std::setfill(' ');

            for (const auto metaDataColumn : m_metaDataColumns)
            {
                switch (metaDataColumn)
                {
                    case MetaDataColumn::Timestamp:
                        stream << std::setw(timestampLength()) << m_timestampHeader << m_separator;
                        break;

                    case MetaDataColumn::ProcessID:
                        stream << std::setw(processIDLength()) << m_processIDHeader << m_separator;
                        break;

                    case MetaDataColumn::ThreadID:
                        stream << std::setw(threadIDLength()) << m_threadIDHeader << m_separator;
                        break;

                    case MetaDataColumn::Level:
                        stream << levelHeader << m_separator;
                        break;

                    case MetaDataColumn::FileName:
                        stream << std::setw(fileNameLength()) << m_fileNameHeader << m_separator;
                        break;

                    case MetaDataColumn::Line:
                        stream << std::setw(lineLength()) << m_lineHeader << m_separator;
                        break;

                    case MetaDataColumn::Function:
                        stream << std::setw(functionLength()) << m_functionHeader << m_separator;
                        break;
                }
            }

            stream << m_messageHeader << '\n';

            if (writeHeaderUnderline())
            {
                stream << std::left << std::setfill(headerUnderlineFill());

                for (const auto metaDataColumn : m_metaDataColumns)
                {
                    switch (metaDataColumn)
                    {
                        case MetaDataColumn::Timestamp:
                            stream << std::setw(timestampLength()) << "" << m_headerUnderlineSeparator;
                            break;

                        case MetaDataColumn::ProcessID:
                            stream << std::setw(processIDLength()) << "" << m_headerUnderlineSeparator;
                            break;

                        case MetaDataColumn::ThreadID:
                            stream << std::setw(threadIDLength()) << "" << m_headerUnderlineSeparator;
                            break;

                        case MetaDataColumn::Level:
                            stream << std::setw(levelHeader.size()) << "" << m_headerUnderlineSeparator;
                            break;

                        case MetaDataColumn::FileName:
                            stream << std::setw(fileNameLength()) << "" << m_headerUnderlineSeparator;
                            break;

                        case MetaDataColumn::Line:
                            stream << std::setw(lineLength()) << "" << m_headerUnderlineSeparator;
                            break;

                        case MetaDataColumn::Function:
                            stream << std::setw(functionLength()) << "" << m_headerUnderlineSeparator;
                            break;
                    }
                }

                stream << std::setw(m_messageHeader.size()) << "" << '\n';
            }
        }

        void writeLogToStream(std::ostream& stream, const Log& log) const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };

            stream << std::left << std::setfill(' ');

            for (const auto metaDataColumn : m_metaDataColumns)
            {
                switch (metaDataColumn)
                {
                    case MetaDataColumn::Timestamp:
                        stream << std::setw(timestampLength()) << log.timestamp << m_separator;
                        break;

                    case MetaDataColumn::ProcessID:
                        stream << std::setw(processIDLength()) << m_processID << m_separator;
                        break;

                    case MetaDataColumn::ThreadID:
                        stream << std::setw(threadIDLength()) << log.threadID << m_separator;
                        break;

                    case MetaDataColumn::Level:
                        stream << levelToString(log.level, levelFormat()) << m_separator;
                        break;

                    case MetaDataColumn::FileName:
                    {
                        const auto fileNameLength{ this->fileNameLength() };
                        const auto fileName{ log.sourceFileName.substr(0, fileNameLength) };
                        stream << std::setw(fileNameLength) << fileName << m_separator;
                        break;
                    }

                    case MetaDataColumn::Line:
                        stream << std::setw(lineLength()) << log.sourceLine << m_separator;
                        break;

                    case MetaDataColumn::Function:
                    {
                        const auto functionLength{ this->functionLength() };
                        const auto function{ log.sourceFunction.substr(0, functionLength) };
                        stream << std::setw(functionLength) << function << m_separator;
                        break;
                    }
                }
            }

            stream << log.message << '\n';
        }

        bool writeBufferToFile(
            const LogBuffer::iterator   begin,
            const LogBuffer::iterator   secondToEnd,
            const std::string&          fileName,
            Generic::FileSystem::path&  filePath,
            bool&                       dirsCreated) const
        {
            auto result{ true };

            try
            {
                // Get file path if empty
                if (filePath.empty())
                {
                    filePath = Generic::FileSystem::absolute(fileName);
                }

                // Create path to file if needed
                if (createDirs() && !dirsCreated)
                {
                    Generic::FileSystem::create_directories(filePath.parent_path());
                    dirsCreated = true;
                }

                const auto writeHeader{ this->writeHeader() };
                const auto fileRotationSize{ this->fileRotationSize() };

                std::size_t fileSize{ 0 };
                std::ofstream fileStream{};
                openFileStream(fileStream, filePath);

                for (auto it{ begin }; ; ++it)
                {
                    fileSize = static_cast<std::size_t>(fileStream.tellp());

                    // Rotate file if needed
                    if (fileRotationSize != 0 && fileRotationSize <= fileSize)
                    {
                        fileStream.close();
                        rotateFile(filePath);
                        openFileStream(fileStream, filePath);
                        fileSize = static_cast<std::size_t>(fileStream.tellp());
                    }

                    // Write header if needed
                    if (writeHeader && fileSize == 0)
                    {
                        writeHeaderToStream(fileStream);
                    }

                    writeLogToStream(fileStream, *it);

                    if (it == secondToEnd)
                    {
                        break;
                    }
                }
            }
            catch (const Generic::FileSystem::filesystem_error&)
            {
                result = false;
            }

            return result;
        }

        void startLogging()
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

                        if (!buffer.empty() && bufferFlushSize() <= buffer.size())
                        {
                            const auto begin        { buffer.begin() };
                            const auto secondToEnd  { --(buffer.end()) };

                            // Doesn't require synchronization.
                            // Since this thread stays within the range gotten when locked
                            // and other threads only add after second to end, unlocking is fine.
                            lock.unlock();

                            // Since other threads can add logs, don't wait when done.
                            shouldWait = false;

                            const auto result{ writeBufferToFile(
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
