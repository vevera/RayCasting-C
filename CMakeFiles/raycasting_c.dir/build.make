# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/vevera/repos/RayCasting-C

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vevera/repos/RayCasting-C

# Include any dependencies generated for this target.
include CMakeFiles/raycasting_c.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/raycasting_c.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/raycasting_c.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/raycasting_c.dir/flags.make

CMakeFiles/raycasting_c.dir/main.c.o: CMakeFiles/raycasting_c.dir/flags.make
CMakeFiles/raycasting_c.dir/main.c.o: main.c
CMakeFiles/raycasting_c.dir/main.c.o: CMakeFiles/raycasting_c.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vevera/repos/RayCasting-C/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/raycasting_c.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/raycasting_c.dir/main.c.o -MF CMakeFiles/raycasting_c.dir/main.c.o.d -o CMakeFiles/raycasting_c.dir/main.c.o -c /home/vevera/repos/RayCasting-C/main.c

CMakeFiles/raycasting_c.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/raycasting_c.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vevera/repos/RayCasting-C/main.c > CMakeFiles/raycasting_c.dir/main.c.i

CMakeFiles/raycasting_c.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/raycasting_c.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vevera/repos/RayCasting-C/main.c -o CMakeFiles/raycasting_c.dir/main.c.s

# Object files for target raycasting_c
raycasting_c_OBJECTS = \
"CMakeFiles/raycasting_c.dir/main.c.o"

# External object files for target raycasting_c
raycasting_c_EXTERNAL_OBJECTS =

raycasting_c: CMakeFiles/raycasting_c.dir/main.c.o
raycasting_c: CMakeFiles/raycasting_c.dir/build.make
raycasting_c: CMakeFiles/raycasting_c.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vevera/repos/RayCasting-C/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable raycasting_c"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/raycasting_c.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/raycasting_c.dir/build: raycasting_c
.PHONY : CMakeFiles/raycasting_c.dir/build

CMakeFiles/raycasting_c.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/raycasting_c.dir/cmake_clean.cmake
.PHONY : CMakeFiles/raycasting_c.dir/clean

CMakeFiles/raycasting_c.dir/depend:
	cd /home/vevera/repos/RayCasting-C && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vevera/repos/RayCasting-C /home/vevera/repos/RayCasting-C /home/vevera/repos/RayCasting-C /home/vevera/repos/RayCasting-C /home/vevera/repos/RayCasting-C/CMakeFiles/raycasting_c.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/raycasting_c.dir/depend

