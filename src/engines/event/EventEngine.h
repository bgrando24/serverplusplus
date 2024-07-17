#ifndef EVENTENGINE_H
#define EVENTENGINE_H

/**
 * @brief The EventEngine class is responsible for managing the Event-Driven Architecture system in Server++
 */
class EventEngine
{
public:
    /**
     * Constructor
     */
    EventEngine();

    /**
     * Destructor
     */
    ~EventEngine();

    /**
     * Initialise the Event Engine
     */
    void Init();

    /**
     * Start the Event Engine
     */
    void Start();

    /**
     * Stop the Event Engine
     */
    void Stop();

    /**
     * Get the Event Engine instance
     * @return The Event Engine instance
     */
    static EventEngine *GetInstance();
};

#endif // EVENTENGINE_H