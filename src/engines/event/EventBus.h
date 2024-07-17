#ifndef EVENTBUS_H
#define EVENTBUS_H

#include "Event.h"
#include "EventHandler.h"
#include <functional>
#include <map>
#include <list>
/**
 * @brief The EventBus is the central mechanism for managing publishing and subscribing to events in Server++
 */
class EventBus
{
public:
    // Delete copy constructor and copy assignment operator
    EventBus(const EventBus &) = delete;
    EventBus &operator=(const EventBus &) = delete;

    /**
     * Get the EventBus instance
     * @return The current EventBus instance
     */
    static EventBus &GetInstance();

    /**
     * Destructor
     */
    ~EventBus();

    /**
     * Initialize the EventBus, setup the event queue and event handlers
     */
    void Init();

    /**
     * Register a new event type available to be published or subscribed to
     * @param type The type of event to register
     */
    void RegisterNewEvent(std::string type);

    /**
     * Provides a method for publishing a new an event
     * @param event The event to publish
     */
    void Publish(Event event);

    /**
     * Subscribe to an event type
     * @param type The type of event to subscribe to
     * @param callback The callback function to call when the event is published
     * @return True if the event handler was successfully subscribed, false otherwise
     */
    bool Subscribe(std::string subscribedEvenType, std::function<void(Event)> callback);

    /**
     * Unsubscribe from an event
     * @param type The type of event to unsubscribe from
     * @param callback The callback function to unsubscribe
     * @return True if the event handler was successfully unsubscribed, false otherwise
     */
    bool Unsubscribe(std::string eventHandlerUUID);

    /**
     * Run the event queue
     */
    void RunQueue();

    /**
     * Process new subscribers
     */
    void ProcessNewSubscriptions();

    /**
     * Process the next chronological event in the EventQueue
     * @return The numerical UUID if an event was processed, 0 if no events to process, -1 if an error occurred
     */
    int ProcessNextEvent();

    /**
     * Flag an event as processed. Will offload the event to the m_processedEvents vector for later storage to disk
     * @param eventId The UUID of the event to flag as processed
     */
    void FlagEventAsProcessed(int eventId);

    /**
     * Save the processed events to disk, clears the m_processedEvents vector
     */
    void SaveToDisk();

    /**
     * Load the processed events from disk
     */
    void LoadFromDisk();

private:
    /**
     * Constructor - Private to enforce Singleton pattern
     */
    EventBus();

    /**
     * The EventBus instance
     */
    static EventBus *m_instance;

    /**
     * Available event types
     */
    std::vector<std::string> m_eventTypes;

    /**
     * New event subscribers that haven't been processed yet
     */
    std::vector<EventHandler> m_newEventSubscribers;

    /**
     * The event queue - uses a list data structure
     */
    std::list<Event> m_eventQueue;

    /**
     * Events already processed - offloaded from the main queue but kept in memory until stored to disk
     */
    std::vector<Event> m_processedEvents;

    /**
     * The event handlers map
     */
    std::map<std::string, std::vector<EventHandler>> m_eventHandlers; // redundant? Need to investigate

    /**
     * The event subscribers
     */
    std::map<std::string, std::vector<EventHandler>> m_eventSubscribers;
};

#endif // EVENTBUS_H