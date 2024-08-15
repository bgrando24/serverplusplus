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
};

#endif // ARGUMENT_HANDLER_H