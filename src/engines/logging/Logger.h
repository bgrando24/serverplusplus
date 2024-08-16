#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>

/**
 * @brief Log Level indicates the severity of the log message
 */
enum LogLevel
{
    DEBUG,
    INFO,
    WARN,
    ERROR
};

/**
 * @brief The Logger class is a singleton class that provides functionality for logging actions and events to the console and to file records
 */
class Logger
{
public:
    /**
     * @brief Get the Logger class instance
     */
    static Logger &GetInstance();

    /**
     * @brief Log a message to the console and to the log file
     *
     * @param message The message to log
     * @param level The log level of the message - default is INFO
     */
    void Log(const std::string &message, LogLevel level = LogLevel::INFO, const std::string &functionName = "");

    /**
     * @brief Set the log file to write log messages to
     *
     * @param fileName The name of the log file
     */
    void SetLogFile(const std::string &fileName);

    /**
     * @brief Set the log level of the logger
     *
     * @param level The log level to set
     */
    void SetLogLevel(LogLevel level);

private:
    /**
     * @brief Private constructor to enforce singleton pattern
     */
    Logger() {}

    /**
     * @brief Logger instance destructor
     */
    ~Logger();

    /**
     * @brief Enforces singleton pattern by deleting copy constructor
     */
    Logger(const Logger &) = delete;

    /**
     * @brief Enforces singleton pattern by deleting assignment operator
     */
    void operator=(const Logger &) = delete;

    /**
     * @brief The current log file
     */
    std::ofstream logFile;

    /**
     * @brief The current log level - default is WARN
     */
    LogLevel logLevel = LogLevel::WARN;

    /**
     * @brief Mutex to ensure thread safety
     */
    std::mutex logMutex;

    /**
     * @brief Get the log level string representation
     *
     * @param level The log level
     * @return std::string The log level string representation
     */
    std::string GetLogLevelString(LogLevel level);
};

/**
 * @brief Macro to log messages with the current function name
 */
#define LOG(message, level) Logger::GetInstance().Log(message, level, __FUNCTION__)

#endif // LOGGER_H