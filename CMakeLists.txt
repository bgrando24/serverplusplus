cmake_minimum_required(VERSION 3.10)
project(ServerPlusPlus)

# Specify C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add executable
add_executable(serverplusplus src/Main.cpp src/engines/event/EventBus.cpp src/engines/logging/Logger.cpp)

# Include directories
target_include_directories(serverplusplus PRIVATE ${PROJECT_SOURCE_DIR}/src)

# Set the output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
