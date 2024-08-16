cmake_minimum_required(VERSION 3.10)
project(ServerPlusPlus)

# Specify C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add all source files
set(SOURCES
    src/Main.cpp
    src/utils/ArgumentHandler.cpp
    src/engines/event/EventBus.cpp
    src/engines/event/EventHandler.cpp
    src/engines/logging/Logger.cpp
    src/utils/IdGen.h
    # Add other source files here
)

# Add executables
add_executable(serverplusplus ${SOURCES})

# Include directories
target_include_directories(serverplusplus PRIVATE ${PROJECT_SOURCE_DIR}/src)

# Set the output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
