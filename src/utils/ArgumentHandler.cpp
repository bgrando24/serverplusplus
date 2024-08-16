#include "ArgumentHandler.h"
#include "../engines/logging/Logger.h"
#include <iostream>
#include <unordered_map>

/**
 * @brief The available command line arguments
 */
const std::string ArgumentHandler::CLIArguments[] = {"--help", "--log-level", "--delay"};

/**
 * @brief The available command line arguments description
 */
const std::string ArgumentHandler::CLIArgumentsDescription[] = {
    "Prints the available command line arguments",
    "Sets the log level: DEBUG, INFO, WARN, ERROR - default is WARN",
    "Sets the delay between processes in seconds - default is zero"};

/**
 * @brief Handles the --help argument
 */
void ArgumentHandler::HandleHelpArgument()
{
    std::cout << "Available command line arguments:" << std::endl;
    for (int i = 0; i < 3; i++)
    {
        std::cout << CLIArguments[i] << " - " << CLIArgumentsDescription[i] << std::endl;
    }
    // exit program
    exit(0);
}

/**
 * @brief Handles the --log-level argument
 * @param logLevel The desired log level
 */
void ArgumentHandler::HandleLogLevelArgument(const std::string &logLevel)
{
    static const std::unordered_map<std::string, LogLevel> logLevelMap = {
        {"DEBUG", LogLevel::DEBUG},
        {"INFO", LogLevel::INFO},
        {"WARN", LogLevel::WARN},
        {"ERROR", LogLevel::ERROR}};

    auto it = logLevelMap.find(logLevel);
    if (it != logLevelMap.end())
    {
        Logger::GetInstance().SetLogLevel(it->second);
        LOG("Log level set to: " + logLevel, LogLevel::INFO);
    }
    else
    {
        LOG("Invalid log level: " + logLevel, LogLevel::ERROR);
    }
}

/**
 * @brief Handles the --delay argument
 * @param delay The desired delay
 */
void ArgumentHandler::HandleDelayArgument(const std::string &delay)
{
    // TBA
}

/**
 * @brief Calls the appropriate handler for any recognised CLI arguments
 */
void ArgumentHandler::ProcessArgumentHandlers(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        if (argv[i] == CLIArguments[0])
        {
            LOG("--help argument found, calling handler", LogLevel::DEBUG);
            HandleHelpArgument();
        }
        else if (argv[i] == CLIArguments[1])
        {
            if (i + 1 < argc)
            {
                LOG("--log-level argument found, calling handler", LogLevel::DEBUG);
                HandleLogLevelArgument(argv[i + 1]);
                i++; // Skip next argument as it is the value for --log-level
            }
            else
            {
                LOG("Missing value for --log-level argument", LogLevel::ERROR);
            }
        }
        else if (argv[i] == CLIArguments[2])
        {
            if (i + 1 < argc)
            {
                LOG("--delay argument found, calling handler", LogLevel::DEBUG);
                HandleDelayArgument(argv[i + 1]);
                i++; // Skip next argument as it is the value for --delay
            }
            else
            {
                LOG("Missing value for --delay argument", LogLevel::ERROR);
            }
        }
        else
        {
            LOG("Unrecognised command line argument: " + std::string(argv[i]), LogLevel::ERROR);
        }
    }
}