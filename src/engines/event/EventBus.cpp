#include "EventBus.h"
#include "EventHandler.h"
#include <iostream>
#include <algorithm>
#include <unistd.h>

// Enforces singleton pattern for EventBus
EventBus &EventBus::GetInstance()
{
    std::cout << "[INFO] [EventBus::GetInstance] EventBus instance created" << std::endl;
    static EventBus instance; // Guaranteed to be destroyed. Instantiated on first use.
    return instance;
}

// Constructor
// Need to use singleton pattern for EventBus, only one instance should exist
// GetInstance will return the current instance, we need to assign the new instance to static member variable m_instance
// Dependencies: DiskIO utility? Disk path?
EventBus::EventBus()
{
    // DiskIO Utility reference
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
    // debugging
    std::cout << "[INFO] [EventBus::Init] Initialising EventBus" << std::endl;
    return;
}

// Register a new event type available to be published or subscribed to in the m_eventTypes map
// Dependencies: m_eventTypes map
void EventBus::RegisterNewEvent(std::string type)
{
    // debugging
    std::cout << "[INFO] [EventBus::RegisterNewEvent] Registering new event type: " << type << std::endl;
    // add event type to m_eventTypes vector
    m_eventTypes.push_back(type);
}

// Publish an event to the event queue
// Push event to the m_eventQueue
// Dependencies: m_eventQueue
void EventBus::Publish(Event event)
{
    // debugging
    std::cout << "[INFO] [EventBus::Publish] Publishing event: " << event.type << std::endl;

    // push event to m_eventQueue
    m_eventQueue.push_back(event);
}

// Subscribe an event handler to an event type
// Add the event handler to the m_eventHandlers map, map stores the applicable event type and handler (pointer to handler?)
// Dependencies: m_eventHandlers, m_eventTypes
bool EventBus::Subscribe(std::string subscribedEvenType, std::function<void(Event)> callback)
{
    // debugging
    std::cout << "[INFO] [EventBus::Subscribe] Subscribing to event type: " << subscribedEvenType << std::endl;
    // check if event type exists
    if (std::find(m_eventTypes.begin(), m_eventTypes.end(), subscribedEvenType) != m_eventTypes.end())
    {
        // debugging
        std::cout << "[INFO] [EventBus::Subscribe] Event type " << subscribedEvenType << " exists, building event handler" << std::endl;
        // build new EventHandler
        EventHandler handler = EventHandler(subscribedEvenType, callback);

        // add event handler to m_eventHandlers map, use type as key, return true if successful
        try
        {
            // debugging
            std::cout << "[INFO] [EventBus::Subscribe] Adding event handler to m_eventHandlers map" << std::endl;
            m_eventHandlers[subscribedEvenType].push_back(handler);
            return true;
        }
        catch (const std::exception &e)
        {
            std::cerr << "[ERROR] [EventBus::Subscribe] - " << e.what() << '\n';
            return false;
        }
    }
    else
    {
        // event type does not exist
        std::cout << "[ERROR] [EventBus::Subscribe] Event type does not exist" << std::endl;
        return false;
    }
}

// Unsubscribe an event handler from an event type
// Remove the event handler from the m_eventHandlers map
// Dependencies: m_eventHandlers
bool EventBus::Unsubscribe(std::string eventHandlerUUID)
{
    // debugging
    std::cout << "[INFO] [EventBus::Unsubscribe] Unsubscribing event handler: " << eventHandlerUUID << std::endl;
    // find event handler in m_eventHandlers map and remove if exists
    for (auto &eventHandler : m_eventHandlers)
    {
        for (auto it = eventHandler.second.begin(); it != eventHandler.second.end(); ++it)
        {
            if (it->uuid == eventHandlerUUID)
            {
                // debugging
                std::cout << "[INFO] [EventBus::Unsubscribe] Event handler found, removing: " << eventHandlerUUID << std::endl;
                // remove event handler
                eventHandler.second.erase(it);
                return true;
            }
            else
            {
                // event handler not found
                // log error
                std::cout << "[ERROR] [EventBus::Unsubscribe] Event handler not found" << std::endl;
                return false;
            }
        }
    }
    // event handler not found
    return false;
}

// Run the event queue -> begin receiving and monitoring
// Event received from publishing, check for new event subscriptions, call event handlers, process and flag events, continue
// this will need to continuously check for events, background loop? Need to investigate best way of doing this
// Could run this in a separate process but need to implement multithreading for this
void EventBus::RunQueue()
{
    // loop indefinitely
    while (true)
    {
        // process new event subscriptions
        ProcessNewSubscriptions();
        // pause for a second
        sleep(1);

        // process next event in queue
        int eventId = ProcessNextEvent();
        // pause for a second
        sleep(1);
        if (eventId > 0)
        {
            // flag event as processed
            FlagEventAsProcessed(eventId);
        }
    }
}

// ------------------ Event Queue helper functions ------------------

// Process any new incoming event subscriptions
// Part of the event queue loop, check for new event subscriptions
// Dependencies: m_newEventSubscribers
void EventBus::ProcessNewSubscriptions()
{
    // debugging
    std::cout << "[INFO] [EventBus::ProcessNewSubscriptions] Processing new event subscriptions" << std::endl;
    // loop through new event subscriptions
    for (auto &subscription : m_newEventSubscribers)
    {
        // debugging
        std::cout << "[INFO] [EventBus::ProcessNewSubscriptions] New subscriber found. Subscribing to event type: " << subscription.type << std::endl;
        // subscribe event handler
        EventBus::Subscribe(subscription.type, subscription.callback);
    }

    // clear new event subscriptions
    m_newEventSubscribers.clear();
}

// Process the next event from the event queue
// Check the event queue for the next event, call the appropriate event handler, flag the event as processed
// Dependencies: m_eventQueue, m_eventHandlers, m_processedEvents
int EventBus::ProcessNextEvent()
{
    // debugging
    std::cout << "[INFO] [EventBus::ProcessNextEvent] Processing next event" << std::endl;
    try
    {
        // check if event queue is empty
        if (m_eventQueue.empty())
        {
            // debugging
            std::cout << "[INFO] [EventBus::ProcessNextEvent] No events in queue" << std::endl;
            // no events in queue
            return 0;
        }

        // get next event
        Event event = m_eventQueue.front();

        // find event handler
        for (auto &eventHandler : m_eventHandlers)
        {
            if (eventHandler.first == event.type)
            {
                // debugging
                std::cout << "[INFO] [EventBus::ProcessNextEvent] Event handler found for event type: " << event.type << std::endl;
                // call event handler
                for (auto &handler : eventHandler.second)
                {
                    handler.callback(event);
                }

                // event processed, return event UUID
                std::cout << "[INFO] [EventBus::ProcessNextEvent] Event processed successfully" << std::endl;
                return event.uuid;
            }
        }
        // no event handler found
        std::cout << "[ERROR] [EventBus::ProcessNextEvent] No event handler found for event type: " << event.type << std::endl;
        return -1;
    }
    catch (const std::exception &e)
    {
        std::cerr << "[ERROR] [EventBus::ProcessNextEvent] - " << e.what() << '\n';
        return -1;
    }
}

// Flag an event as processed
// If event handler successfully called, flag the event as processed, offload to the m_processedEvents vector for later storage to disk
// Dependencies: result from ProcessNextEvent, m_eventQueue, m_processedEvents
void EventBus::FlagEventAsProcessed(int eventId)
{
    // debugging
    std::cout << "[INFO] [EventBus::FlagEventAsProcessed] Flagging event as processed: " << eventId << std::endl;
    // find event in event queue
    for (auto e = m_eventQueue.begin(); e != m_eventQueue.end(); ++e)
    {
        if (e->uuid == eventId)
        {
            // debugging
            std::cout << "[INFO] [EventBus::FlagEventAsProcessed] Event handler UUID matched, flagging as processed" << std::endl;
            // flag event status as processed
            e->status = "PROCESSED_SUCCESSFUL";

            // add event to processed events
            m_processedEvents.push_back(*e);

            // remove event from event queue
            m_eventQueue.erase(e);
        }
    }
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