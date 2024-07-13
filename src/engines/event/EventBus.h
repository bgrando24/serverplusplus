#include "Event.h"
#include <functional>
#include <map>
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
     * Process a new event that has been published to the EventQueue
     * @return True if event handler was called successfully, false otherwise
     */
    bool ProcessNewEvent();

    /**
     * Flag an event as processed
     */
    void FlagEventAsProcessed();

    /**
     * Get the EventBus instance
     * @return The EventBus instance
     */
    static EventBus *GetInstance();

private:
    /**
     * The event queue
     */
    std::vector<Event> m_eventQueue;

    /**
     * The event handlers
     */
    std::map<std::string, std::vector<EventHandler>> m_eventHandlers; // redundant? Need to investigate

    /**
     * The event subscribers
     */
    std::map<std::string, std::vector<EventHandler>> m_eventSubscribers;
};