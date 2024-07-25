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
#include <thread> // multi-threading

// -------------------- Create a server socket --------------------
int createSocket() { return -1; }

int main()
{
    std::cout << "Testing the EventBus" << std::endl;

    // get eventbus instance
    EventBus &eventBus = EventBus::GetInstance();
    // initialise
    eventBus.Init();

    // multithreading
    std::thread eventBusThread(&EventBus::RunQueue, &eventBus);
    eventBusThread.join();

    std::thread mainThread([]()
                           {
        while (true) {
        std::cout << "Main thread" << std::endl;
        sleep(1);
        } });
    mainThread.join();

    return 0;
}