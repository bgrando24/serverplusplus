cmake_minimum_required(VERSION 3.10)
project(ServerPP)

set(CMAKE_CXX_STANDARD 17)

# Ensure build directory is used for binary output
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(serverplusplus src/main.cpp)