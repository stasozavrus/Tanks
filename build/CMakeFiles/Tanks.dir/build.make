# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/stasozavrus/Programs/VisualCode/Tanks

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/stasozavrus/Programs/VisualCode/Tanks/build

# Include any dependencies generated for this target.
include CMakeFiles/Tanks.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Tanks.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Tanks.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Tanks.dir/flags.make

CMakeFiles/Tanks.dir/Tanks.cpp.o: CMakeFiles/Tanks.dir/flags.make
CMakeFiles/Tanks.dir/Tanks.cpp.o: /home/stasozavrus/Programs/VisualCode/Tanks/Tanks.cpp
CMakeFiles/Tanks.dir/Tanks.cpp.o: CMakeFiles/Tanks.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stasozavrus/Programs/VisualCode/Tanks/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Tanks.dir/Tanks.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Tanks.dir/Tanks.cpp.o -MF CMakeFiles/Tanks.dir/Tanks.cpp.o.d -o CMakeFiles/Tanks.dir/Tanks.cpp.o -c /home/stasozavrus/Programs/VisualCode/Tanks/Tanks.cpp

CMakeFiles/Tanks.dir/Tanks.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tanks.dir/Tanks.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stasozavrus/Programs/VisualCode/Tanks/Tanks.cpp > CMakeFiles/Tanks.dir/Tanks.cpp.i

CMakeFiles/Tanks.dir/Tanks.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tanks.dir/Tanks.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stasozavrus/Programs/VisualCode/Tanks/Tanks.cpp -o CMakeFiles/Tanks.dir/Tanks.cpp.s

# Object files for target Tanks
Tanks_OBJECTS = \
"CMakeFiles/Tanks.dir/Tanks.cpp.o"

# External object files for target Tanks
Tanks_EXTERNAL_OBJECTS =

Tanks: CMakeFiles/Tanks.dir/Tanks.cpp.o
Tanks: CMakeFiles/Tanks.dir/build.make
Tanks: _deps/sfml-build/lib/libsfml-graphics-d.so.2.5.1
Tanks: _deps/sfml-build/lib/libsfml-window-d.so.2.5.1
Tanks: _deps/sfml-build/lib/libsfml-system-d.so.2.5.1
Tanks: CMakeFiles/Tanks.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/stasozavrus/Programs/VisualCode/Tanks/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Tanks"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Tanks.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Tanks.dir/build: Tanks
.PHONY : CMakeFiles/Tanks.dir/build

CMakeFiles/Tanks.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Tanks.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Tanks.dir/clean

CMakeFiles/Tanks.dir/depend:
	cd /home/stasozavrus/Programs/VisualCode/Tanks/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/stasozavrus/Programs/VisualCode/Tanks /home/stasozavrus/Programs/VisualCode/Tanks /home/stasozavrus/Programs/VisualCode/Tanks/build /home/stasozavrus/Programs/VisualCode/Tanks/build /home/stasozavrus/Programs/VisualCode/Tanks/build/CMakeFiles/Tanks.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Tanks.dir/depend

