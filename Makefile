# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.21.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.21.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/brandongrando/Documents/CPP/Server++

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/brandongrando/Documents/CPP/Server++

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/opt/homebrew/Cellar/cmake/3.21.3/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/opt/homebrew/Cellar/cmake/3.21.3/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/brandongrando/Documents/CPP/Server++/CMakeFiles /Users/brandongrando/Documents/CPP/Server++//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/brandongrando/Documents/CPP/Server++/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named serverplusplus

# Build rule for target.
serverplusplus: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 serverplusplus
.PHONY : serverplusplus

# fast build rule for target.
serverplusplus/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/serverplusplus.dir/build.make CMakeFiles/serverplusplus.dir/build
.PHONY : serverplusplus/fast

src/Main.o: src/Main.cpp.o
.PHONY : src/Main.o

# target to build an object file
src/Main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/serverplusplus.dir/build.make CMakeFiles/serverplusplus.dir/src/Main.cpp.o
.PHONY : src/Main.cpp.o

src/Main.i: src/Main.cpp.i
.PHONY : src/Main.i

# target to preprocess a source file
src/Main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/serverplusplus.dir/build.make CMakeFiles/serverplusplus.dir/src/Main.cpp.i
.PHONY : src/Main.cpp.i

src/Main.s: src/Main.cpp.s
.PHONY : src/Main.s

# target to generate assembly for a file
src/Main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/serverplusplus.dir/build.make CMakeFiles/serverplusplus.dir/src/Main.cpp.s
.PHONY : src/Main.cpp.s

src/engines/event/EventBus.o: src/engines/event/EventBus.cpp.o
.PHONY : src/engines/event/EventBus.o

# target to build an object file
src/engines/event/EventBus.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/serverplusplus.dir/build.make CMakeFiles/serverplusplus.dir/src/engines/event/EventBus.cpp.o
.PHONY : src/engines/event/EventBus.cpp.o

src/engines/event/EventBus.i: src/engines/event/EventBus.cpp.i
.PHONY : src/engines/event/EventBus.i

# target to preprocess a source file
src/engines/event/EventBus.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/serverplusplus.dir/build.make CMakeFiles/serverplusplus.dir/src/engines/event/EventBus.cpp.i
.PHONY : src/engines/event/EventBus.cpp.i

src/engines/event/EventBus.s: src/engines/event/EventBus.cpp.s
.PHONY : src/engines/event/EventBus.s

# target to generate assembly for a file
src/engines/event/EventBus.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/serverplusplus.dir/build.make CMakeFiles/serverplusplus.dir/src/engines/event/EventBus.cpp.s
.PHONY : src/engines/event/EventBus.cpp.s

src/engines/logging/Logger.o: src/engines/logging/Logger.cpp.o
.PHONY : src/engines/logging/Logger.o

# target to build an object file
src/engines/logging/Logger.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/serverplusplus.dir/build.make CMakeFiles/serverplusplus.dir/src/engines/logging/Logger.cpp.o
.PHONY : src/engines/logging/Logger.cpp.o

src/engines/logging/Logger.i: src/engines/logging/Logger.cpp.i
.PHONY : src/engines/logging/Logger.i

# target to preprocess a source file
src/engines/logging/Logger.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/serverplusplus.dir/build.make CMakeFiles/serverplusplus.dir/src/engines/logging/Logger.cpp.i
.PHONY : src/engines/logging/Logger.cpp.i

src/engines/logging/Logger.s: src/engines/logging/Logger.cpp.s
.PHONY : src/engines/logging/Logger.s

# target to generate assembly for a file
src/engines/logging/Logger.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/serverplusplus.dir/build.make CMakeFiles/serverplusplus.dir/src/engines/logging/Logger.cpp.s
.PHONY : src/engines/logging/Logger.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... serverplusplus"
	@echo "... src/Main.o"
	@echo "... src/Main.i"
	@echo "... src/Main.s"
	@echo "... src/engines/event/EventBus.o"
	@echo "... src/engines/event/EventBus.i"
	@echo "... src/engines/event/EventBus.s"
	@echo "... src/engines/logging/Logger.o"
	@echo "... src/engines/logging/Logger.i"
	@echo "... src/engines/logging/Logger.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

