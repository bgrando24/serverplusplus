#include "Logger.h"

Logger &Logger::GetInstance()
{
    static Logger instance;
    return instance;
}

void Logger::Log(const std::string &message, LogLevel level, const std::string &functionName)
{
    if (level < this->logLevel)
        return;

    std::lock_guard<std::mutex> lock(logMutex);
    std::string logMessage = "[" + GetLogLevelString(level) + "] " + (functionName.empty() ? "" : "[" + functionName + "] ") + message;

    if (logFile.is_open())
    {
        logFile << logMessage << std::endl;
    }
    else
    {
        std::cout << logMessage << std::endl;
    }
}

void Logger::SetLogFile(const std::string &fileName)
{
    std::lock_guard<std::mutex> lock(logMutex);
    if (logFile.is_open())
    {
        logFile.close();
    }
    logFile.open(fileName, std::ios::out | std::ios::app);
}

void Logger::SetLogLevel(LogLevel level)
{
    std::lock_guard<std::mutex> lock(logMutex);
    this->logLevel = level;
}

std::string Logger::GetLogLevelString(LogLevel level)
{
    switch (level)
    {
    case DEBUG:
        return "DEBUG";
    case INFO:
        return "INFO";
    case WARN:
        return "WARN";
    case ERROR:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}

Logger::~Logger()
{
    if (logFile.is_open())
    {
        logFile.close();
    }
}