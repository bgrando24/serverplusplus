#ifndef IDGEN_H
#define IDGEN_H

#include <string>
/**
 * IdGen is a utility class that generates unique ids of varying lengths or requirements for UUIDs.
 */
class IdGen
{
public:
    /**
     * Generate a unique numerical id of a specified length.
     * @param length The length of the id to generate.
     * @return A unique id of the specified length.
     */
    static std::string GetNumId(int length)
    {
        std::string id = "";
        for (int i = 0; i < length; i++)
        {
            id += std::to_string(rand() % 10);
        }
        return id;
    }

    /**
     * Generate a unique alpha-numerical id of a specified length.
     * @param length The length of the id to generate.
     * @return A unique id of the specified length.
     */
    static std::string GetAlphaNumId(int length)
    {
        std::string id = "";
        static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        int alphanumLength = sizeof(alphanum) - 1;
        for (int i = 0; i < length; i++)
        {
            id += alphanum[rand() % alphanumLength];
        }
        return id;
    }
};

#endif // IDGEN_H