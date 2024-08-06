#include "./engines/event/EventBus.h"
#include "./engines/event/EventHandler.h"
#include "engines/logging/Logger.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <thread> // multi-threading

// -------------------- Create a server socket --------------------
int createSocket() { return -1; }

int main()
{
    std::cout << "\nTesting the EventBus" << std::endl;

    // get eventbus instance
    EventBus &eventBus = EventBus::GetInstance();
    // initialise
    eventBus.Init();

    // register new event type 'random'
    eventBus.RegisterNewEvent("random");

    // build event handler
    EventHandler randomEventHandler("random", [](Event event)
                                    {
        std::cout << "Received new random event" << std::endl;
        std::cout << "Event UUID: " << event.uuid << std::endl;
        std::cout << "Event Type: " << event.type << std::endl;
        std::cout << "Event Data: " << std::any_cast<std::string>(event.data) << std::endl;
        std::cout << "Event Timestamp: " << event.timestamp << std::endl;
        std::cout << "Event Status: " << event.status << std::endl; });

    // subscribe handler to event type 'random'
    eventBus.Subscribe("random", randomEventHandler.callback);

    // multithreading
    std::thread eventBusThread(&EventBus::RunQueue, &eventBus);
    eventBusThread.detach(); // detached means the main thread will not wait for this thread to finish

    // struct Event
    // {
    //     int uuid;
    //     std::string type;
    //     std::any data;
    //     long timestamp;
    //     std::string status;
    // };

    std::thread mainThread([&eventBus]()
                           {
        while (true) {
        // randomly publish event
        int randomNumber = rand(); // generate a random number

        if (randomNumber % 2 == 0) {
            Event event;
            event.uuid = randomNumber;
            event.type = "random";
            event.data = std::string("This is a random event");
            event.timestamp = time(0);
            event.status = "pending";

            eventBus.Publish(event);
        }
        std::cout << "New random event published" << std::endl;
        sleep(2);
        } });
    mainThread.join(); // join means the main thread will wait for this thread to finish

    return 0;
}