#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <any>
/**
 * @brief The Event struct is a data structure representing an Event in Server++
 *
 * In Server++ an Event is any action that requires a response from the system
 */
struct Event
{
    int uuid;
    std::string type;
    std::any data;
    long timestamp;
    std::string status;
};

#endif // EVENT_H