#ifndef ARGUMENT_HANDLER_H
#define ARGUMENT_HANDLER_H

#include <string>
/**
 * @brief ArgumentHandler class defines the available command line arguments, and handles their desired functionality
 */
class ArgumentHandler
{
public:
    /**
     * @brief The available command line arguments
     */
    static const std::string CLIArguments[3];

    /**
     * @brief The available command line arguments description
     */
    static const std::string CLIArgumentsDescription[3];

    /**
     * @brief Handles the --help argument
     */
    static void HandleHelpArgument();

    /**
     * @brief Handles the --log-level argument
     * @param logLevel The desired log level
     */
    static void HandleLogLevelArgument(const std::string &logLevel);

    /**
     * @brief Handles the --delay argument
     * @param delay The desired delay
     */
    static void HandleDelayArgument(const std::string &delay);

    /**
     * @brief Calls the appropriate handler for any recognised CLI arguments
     */
    static void ProcessArgumentHandlers(int argc, char *argv[]);
};

#endif // ARGUMENT_HANDLER_H