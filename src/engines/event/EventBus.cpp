#include "EventBus.h"
#include "EventHandler.h"
#include "../../engines/logging/Logger.h"
#include <iostream>
#include <algorithm>
#include <unistd.h>

// Enforces singleton pattern for EventBus
EventBus &EventBus::GetInstance()
{
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
    // std::cout << "[INFO] [EventBus::Init] Initialising EventBus" << std::endl;
    LOG("Initialising", DEBUG);
    return;
}

// Register a new event type available to be published or subscribed to in the m_eventTypes map
// Dependencies: m_eventTypes map
void EventBus::RegisterNewEvent(std::string type)
{
    // debugging
    LOG("Registering new event type: " + type, INFO);
    // add event type to m_eventTypes vector
    m_eventTypes.push_back(type);
}

// Publish an event to the event queue
// Push event to the m_eventQueue
// Dependencies: m_eventQueue
void EventBus::Publish(Event event)
{
    // debugging
    LOG("Publishing new event: " + std::to_string(event.uuid), INFO);

    // push event to m_eventQueue
    m_eventQueue.push_back(event);
}

// Subscribe an event handler to an event type
// Add the event handler to the m_eventHandlers map, map stores the applicable event type and handler (pointer to handler?)
// Dependencies: m_eventHandlers, m_eventTypes
bool EventBus::Subscribe(std::string subscribedEvenType, std::function<void(Event)> callback)
{
    // debugging
    LOG("Subscribing to event type: " + subscribedEvenType, DEBUG);
    // check if event type exists
    if (std::find(m_eventTypes.begin(), m_eventTypes.end(), subscribedEvenType) != m_eventTypes.end())
    {
        // debugging
        LOG("Event type exists, subscribing to " + subscribedEvenType, INFO);
        // build new EventHandler
        EventHandler handler = EventHandler(subscribedEvenType, callback);

        // add event handler to m_eventHandlers map, use type as key, return true if successful
        try
        {
            // debugging
            LOG("Event handler " + handler.uuid + "added to m_eventHandlers", INFO);
            m_eventHandlers[subscribedEvenType].push_back(handler);
            return true;
        }
        catch (const std::exception &e)
        {
            LOG("Error adding event handler to m_eventHandlers: " + (std::string)e.what(), ERROR);
            return false;
        }
    }
    else
    {
        // event type does not exist
        LOG("Event type " + subscribedEvenType + " does not exist", WARN);
        return false;
    }
}

// Unsubscribe an event handler from an event type
// Remove the event handler from the m_eventHandlers map
// Dependencies: m_eventHandlers
bool EventBus::Unsubscribe(std::string eventHandlerUUID)
{
    // debugging
    LOG("Unsubscribing event handler: " + eventHandlerUUID, DEBUG);

    // find event handler in m_eventHandlers map and remove if exists
    for (auto &eventHandler : m_eventHandlers)
    {
        for (auto it = eventHandler.second.begin(); it != eventHandler.second.end(); ++it)
        {
            if (it->uuid == eventHandlerUUID)
            {
                // debugging
                LOG("Event handler " + eventHandlerUUID + " found, removing from m_eventHandlers", INFO);
                // remove event handler
                eventHandler.second.erase(it);
                return true;
            }
            else
            {
                // event handler not found
                // log error
                LOG("Event handler " + eventHandlerUUID + " not found in m_eventHandlers", WARN);
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
    LOG("Processing new event subscriptions", DEBUG);
    // loop through new event subscriptions
    for (auto &subscription : m_newEventSubscribers)
    {
        // debugging
        LOG("New subscriber found. Subscribing to event type: " + subscription.type, INFO);
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
    LOG("Processing next event in queue", DEBUG);
    try
    {
        // check if event queue is empty
        if (m_eventQueue.empty())
        {
            // debugging
            LOG("No events in queue", INFO);
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
                LOG("Event handler found for event type: " + event.type, INFO);
                // call event handler
                for (auto &handler : eventHandler.second)
                {
                    handler.callback(event);
                }

                // event processed, return event UUID
                LOG("Event processed successfully", INFO);
                return event.uuid;
            }
        }
        // no event handler found
        LOG("No event handler found for event type: " + event.type, WARN);
        return -1;
    }
    catch (const std::exception &e)
    {
        LOG("Error processing next event: " + (std::string)e.what(), ERROR);
        return -1;
    }
}

// Flag an event as processed
// If event handler successfully called, flag the event as processed, offload to the m_processedEvents vector for later storage to disk
// Dependencies: result from ProcessNextEvent, m_eventQueue, m_processedEvents
void EventBus::FlagEventAsProcessed(int eventId)
{
    // debugging
    LOG("Flagging event as processed: " + std::to_string(eventId), DEBUG);
    // find event in event queue
    for (auto e = m_eventQueue.begin(); e != m_eventQueue.end(); ++e)
    {
        if (e->uuid == eventId)
        {
            // debugging
            LOG("Event handler UUID matched, flagging as processed", INFO);
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