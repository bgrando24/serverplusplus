#include "EventHandler.h"
#include "IdGen.h"

// Set prefix used for event handler UUIDs
const std::string UUID_PREFIX = "handler_";

// constructor
EventHandler::EventHandler(std::string type, std::function<void(Event)> callback)
    : type(type), callback(callback)
{
    // generate random UUID
    this->uuid = UUID_PREFIX + type + "_" + IdGen().GetAlphaNumId(8);
}