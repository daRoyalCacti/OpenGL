# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_SOURCE_DIR = /home/george/Documents/Projects/OpenGl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/george/Documents/Projects/OpenGl/build

# Include any dependencies generated for this target.
include CMakeFiles/Generate.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Generate.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Generate.dir/flags.make

CMakeFiles/Generate.dir/main.cpp.o: CMakeFiles/Generate.dir/flags.make
CMakeFiles/Generate.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/george/Documents/Projects/OpenGl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Generate.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Generate.dir/main.cpp.o -c /home/george/Documents/Projects/OpenGl/main.cpp

CMakeFiles/Generate.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Generate.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/george/Documents/Projects/OpenGl/main.cpp > CMakeFiles/Generate.dir/main.cpp.i

CMakeFiles/Generate.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Generate.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/george/Documents/Projects/OpenGl/main.cpp -o CMakeFiles/Generate.dir/main.cpp.s

# Object files for target Generate
Generate_OBJECTS = \
"CMakeFiles/Generate.dir/main.cpp.o"

# External object files for target Generate
Generate_EXTERNAL_OBJECTS =

Generate: CMakeFiles/Generate.dir/main.cpp.o
Generate: CMakeFiles/Generate.dir/build.make
Generate: libGLAD.a
Generate: /usr/lib/libglfw.so.3.3
Generate: /usr/lib/libGL.so
Generate: CMakeFiles/Generate.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/george/Documents/Projects/OpenGl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Generate"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Generate.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Generate.dir/build: Generate

.PHONY : CMakeFiles/Generate.dir/build

CMakeFiles/Generate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Generate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Generate.dir/clean

CMakeFiles/Generate.dir/depend:
	cd /home/george/Documents/Projects/OpenGl/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/george/Documents/Projects/OpenGl /home/george/Documents/Projects/OpenGl /home/george/Documents/Projects/OpenGl/build /home/george/Documents/Projects/OpenGl/build /home/george/Documents/Projects/OpenGl/build/CMakeFiles/Generate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Generate.dir/depend

