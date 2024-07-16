#include "Event.h"
#include <functional>
#include <map>
#include <list>
/**
 * @brief The EventBus is the central mechanism for managing publishing and subscribing to events in Server++
 */
class EventBus
{
public:
    /**
     * Constructor
     */
    EventBus();

    /**
     * Destructor
     */
    ~EventBus();

    /**
     * The EventHandler is a callback function that is called in response to an appropriate event.
     *
     * @param event The event that triggered the callback
     */
    using EventHandler = std::function<void(const Event &)>;

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
     */
    void Subscribe(std::string type, std::function<void(Event)> callback);

    /**
     * Unsubscribe from an event
     * @param type The type of event to unsubscribe from
     * @param callback The callback function to unsubscribe
     */
    void Unsubscribe(std::string type, std::function<void(Event)> callback);

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
     * @return True if event handler was called successfully, false otherwise
     */
    bool ProcessNextEvent();

    /**
     * Flag an event as processed. Will offload the event to the m_processedEvents vector for later storage to disk
     */
    void FlagEventAsProcessed();

    /**
     * Save the processed events to disk, clears the m_processedEvents vector
     */
    void SaveToDisk();

    /**
     * Load the processed events from disk
     */
    void LoadFromDisk();

    /**
     * Get the EventBus instance
     * @return The current EventBus instance
     */
    static EventBus *GetInstance();

private:
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