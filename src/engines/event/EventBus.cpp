#include "EventBus.h"
#include <iostream>

// Constructor
// Need to use singleton pattern for EventBus, only one instance should exist
// GetInstance will return the current instance, we need to assign the new instance to static member variable m_instance
// Dependencies: DiskIO utility? Disk path? 
EventBus::EventBus()
{
    // DiskIO Utility reference

    // set instance
    m_instance = this;
}

// Destructor
// Need to investigate the usage of destructors in C++
EventBus::~EventBus()
{
    // Save any remaining events to disk
    SaveToDisk();
}

// **NOTE** This may be redundant, but keeping it for until EventEngine is fully functional
// Initialize the EventBus, setup the event queue and event handlers
// Declare event queue, processed events, event handlers data structures (if required)
// Dependencies: m_eventQueue, m_processedEvents, m_eventHandlers(?)
void EventBus::Init()
{
    return;
}

// Register a new event type available to be published or subscribed to in the m_eventTypes map
// Dependencies: m_eventTypes map
void EventBus::RegisterNewEvent(std::string type)
{
    // add event type to m_eventTypes vector
    m_eventTypes.push_back(type);
}

// Publish an event to the event queue
// Push event to the m_eventQueue
// Dependencies: m_eventQueue
void EventBus::Publish(Event event)
{
    // push event to m_eventQueue
    m_eventQueue.push_back(event);
}


// NOTES
/*
    Need to consider how to uniquely identify subscribers
    If we just use the event type string as the key, when it comes to unsubscribing we may have issues

    We need to set up a way to either manually define the UUID, or auto assign (maybe based on where the subscription comes from)
    We also need a way of getting the UUID of the subscription, to use for reference in unsubscribing

    Perhaps we can alter the EventHandler structure to hold the UUID, event type, and event handler callback function, 
        that way in m_eventSubscribers the UUID is the key and the EventHandler structure is the value
*/



// Subscribe an event handler to an event type
// Add the event handler to the m_eventHandlers map, map stores the applicable event type and handler (pointer to handler?)
// Dependencies: m_eventHandlers, m_eventTypes
void EventBus::Subscribe(std::string type, std::function<void(Event)> callback)
{
    // check if event type exists
    if (std::find(m_eventTypes.begin(), m_eventTypes.end(), type) != m_eventTypes.end())
    {
        // add event handler to m_eventHandlers map, use type as key
        m_eventHandlers[type].push_back(callback);
    }
    else
    {
        // event type does not exist
        // log error
        std::cout << "[ERROR] [EventBus::Subscribe] Event type does not exist" << std::endl;
    }
}

// Unsubscribe an event handler from an event type
// Remove the event handler from the m_eventHandlers map
// Dependencies: m_eventHandlers
void EventBus::Unsubscribe(std::string type, std::function<void(Event)> callback)
{
    
}

// Run the event queue -> begin receiving and monitoring
// Event received from publishing, check for new event subscriptions, call event handlers, process and flag events, continue
// this will need to continuously check for events, background loop? Need to investigate best way of doing this
// Could run this in a separate process but need to implement multithreading for this
void EventBus::RunQueue()
{
}



// ------------------ Event Queue helper functions ------------------

// Process any new incoming event subscriptions
// Part of the event queue loop, check for new event subscriptions
// Dependencies: m_newEventSubscribers
void EventBus::ProcessNewSubscriptions()
{
}

// Process the next event from the event queue
// Check the event queue for the next event, call the appropriate event handler, flag the event as processed
// Dependencies: m_eventQueue, m_eventHandlers, m_processedEvents
bool EventBus::ProcessNextEvent()
{
}

// Flag an event as processed
// If event handler successfully called, flag the event as processed, offload to the m_processedEvents vector for later storage to disk
// Dependencies: result from ProcessNextEvent, m_eventQueue, m_processedEvents
void EventBus::FlagEventAsProcessed()
{
}

// Dump the processed events to disk
// Save the processed events to disk, clears the m_processedEvents vector
// Need to determine when this happens, how often, how to handle disk IO
// Do we do this continually or at end of program?
// Dependencies: DiskIO utility, m_processedEvents
void EventBus::SaveToDisk()
{
}

// Load previously processed events from disk
// Used when replay mode is activated, load previously processed events from disk for given process
// Dependencies: DiskIO utility
void EventBus::LoadFromDisk()
{
}

// Get the instance of the EventBus -> singleton pattern
// Return the instance of the EventBus
EventBus *EventBus::GetInstance()
{
    return nullptr;
}