#!/bin/bash

# Set the compiler and flags
CXX=g++
CXXFLAGS="-std=c++11 -Wall -Wextra"

# Set the source file and output executable name
SOURCE_FILE="Main.cpp"
OUTPUT_FILE="server"

# Compile the source file
$CXX $CXXFLAGS $SOURCE_FILE -o $OUTPUT_FILE

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running the program..."
    # Run the executable
    ./$OUTPUT_FILE
else
    echo "Compilation failed."
fi