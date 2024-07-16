#include "Event.h"
#include <string>
#include <functional>
/**
 * @brief The EventHandler struct represents a callback function that is called in response to an appropriate event, as well
 * as other info regarding the event handler (UUID, event type to handle, etc)
 */
struct EventHandler
{
    /**
     * @brief The UUID of the event handler - used to identify a speific event handler
     */
    std::string uuid;

    /**
     * @brief The type of event to handle
     */
    std::string type;

    /**
     * @brief The callback function to call when the event is published
     */
    std::function<void(const Event &)> callback;

    /**
     * @brief Constructor
     * @param uuid The UUID of the event handler
     * @param type The type of event to handle
     * @param callback The callback function to call when the event is published
     */
    EventHandler(std::string type, std::function<void(Event)> callback)
        : type(type), callback(callback) {}
};