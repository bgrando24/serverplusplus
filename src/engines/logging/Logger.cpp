#include "Logger.h"

Logger &Logger::GetInstance()
{
    static Logger instance;
    return instance;
}

void Logger::Log(const std::string &message, LogLevel level, const std::string &functionName)
{
    // if (level < logLevel)
    //     return;

    std::lock_guard<std::mutex> lock(logMutex);
    std::string logMessage = "[" + GetLogLevelString(level) + "]: " + (functionName.empty() ? "" : "[" + functionName + "] - ") + message;

    if (logFile.is_open())
    {
        logFile << logMessage << std::endl;
    }
    else
    {
        std::cout << logMessage << std::endl;
    }
}

void Logger::SetLogFile(const std::string &filename)
{
    std::lock_guard<std::mutex> lock(logMutex);
    if (logFile.is_open())
    {
        logFile.close();
    }
    logFile.open(filename, std::ios::app);
}

void Logger::SetLogLevel(LogLevel level)
{
    logLevel = level;
}

Logger::~Logger()
{
    if (logFile.is_open())
    {
        logFile.close();
    }
}

std::string Logger::GetLogLevelString(LogLevel level)
{
    switch (level)
    {
    case INFO:
        return "INFO";
    case WARN:
        return "WARN";
    case ERROR:
        return "ERROR";
    case DEBUG:
        return "DEBUG";
    default:
        return "UNKNOWN";
    }
}
