#include "./engines/event/EventBus.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

// -------------------- Create a server socket --------------------
int createSocket() { return -1; }

int main()
{
    std::cout << "Testing the EventBus" << std::endl;

    // get eventbus instance
    EventBus &eventBus = EventBus::GetInstance();
    // initialise
    eventBus.Init();
    // register test events
    eventBus.RegisterNewEvent("test_event");
    eventBus.RegisterNewEvent("test_event2");

    eventBus.RunQueue();
    return 0;
}