# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/mfattoru/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/173.4674.29/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/mfattoru/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/173.4674.29/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/mfattoru/MEGA/1 - NIU UNIVERSITY/CSCI 631/assign4"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/mfattoru/MEGA/1 - NIU UNIVERSITY/CSCI 631/assign4/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/assign4cli.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/assign4cli.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/assign4cli.dir/flags.make

CMakeFiles/assign4cli.dir/prog4cli.c.o: CMakeFiles/assign4cli.dir/flags.make
CMakeFiles/assign4cli.dir/prog4cli.c.o: ../prog4cli.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/mfattoru/MEGA/1 - NIU UNIVERSITY/CSCI 631/assign4/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/assign4cli.dir/prog4cli.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/assign4cli.dir/prog4cli.c.o   -c "/home/mfattoru/MEGA/1 - NIU UNIVERSITY/CSCI 631/assign4/prog4cli.c"

CMakeFiles/assign4cli.dir/prog4cli.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/assign4cli.dir/prog4cli.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/mfattoru/MEGA/1 - NIU UNIVERSITY/CSCI 631/assign4/prog4cli.c" > CMakeFiles/assign4cli.dir/prog4cli.c.i

CMakeFiles/assign4cli.dir/prog4cli.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/assign4cli.dir/prog4cli.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/mfattoru/MEGA/1 - NIU UNIVERSITY/CSCI 631/assign4/prog4cli.c" -o CMakeFiles/assign4cli.dir/prog4cli.c.s

CMakeFiles/assign4cli.dir/prog4cli.c.o.requires:

.PHONY : CMakeFiles/assign4cli.dir/prog4cli.c.o.requires

CMakeFiles/assign4cli.dir/prog4cli.c.o.provides: CMakeFiles/assign4cli.dir/prog4cli.c.o.requires
	$(MAKE) -f CMakeFiles/assign4cli.dir/build.make CMakeFiles/assign4cli.dir/prog4cli.c.o.provides.build
.PHONY : CMakeFiles/assign4cli.dir/prog4cli.c.o.provides

CMakeFiles/assign4cli.dir/prog4cli.c.o.provides.build: CMakeFiles/assign4cli.dir/prog4cli.c.o


CMakeFiles/assign4cli.dir/wrap4cli.c.o: CMakeFiles/assign4cli.dir/flags.make
CMakeFiles/assign4cli.dir/wrap4cli.c.o: ../wrap4cli.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/mfattoru/MEGA/1 - NIU UNIVERSITY/CSCI 631/assign4/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/assign4cli.dir/wrap4cli.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/assign4cli.dir/wrap4cli.c.o   -c "/home/mfattoru/MEGA/1 - NIU UNIVERSITY/CSCI 631/assign4/wrap4cli.c"

CMakeFiles/assign4cli.dir/wrap4cli.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/assign4cli.dir/wrap4cli.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/mfattoru/MEGA/1 - NIU UNIVERSITY/CSCI 631/assign4/wrap4cli.c" > CMakeFiles/assign4cli.dir/wrap4cli.c.i

CMakeFiles/assign4cli.dir/wrap4cli.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/assign4cli.dir/wrap4cli.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/mfattoru/MEGA/1 - NIU UNIVERSITY/CSCI 631/assign4/wrap4cli.c" -o CMakeFiles/assign4cli.dir/wrap4cli.c.s

CMakeFiles/assign4cli.dir/wrap4cli.c.o.requires:

.PHONY : CMakeFiles/assign4cli.dir/wrap4cli.c.o.requires

CMakeFiles/assign4cli.dir/wrap4cli.c.o.provides: CMakeFiles/assign4cli.dir/wrap4cli.c.o.requires
	$(MAKE) -f CMakeFiles/assign4cli.dir/build.make CMakeFiles/assign4cli.dir/wrap4cli.c.o.provides.build
.PHONY : CMakeFiles/assign4cli.dir/wrap4cli.c.o.provides

CMakeFiles/assign4cli.dir/wrap4cli.c.o.provides.build: CMakeFiles/assign4cli.dir/wrap4cli.c.o


CMakeFiles/assign4cli.dir/in-out.c.o: CMakeFiles/assign4cli.dir/flags.make
CMakeFiles/assign4cli.dir/in-out.c.o: ../in-out.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/mfattoru/MEGA/1 - NIU UNIVERSITY/CSCI 631/assign4/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/assign4cli.dir/in-out.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/assign4cli.dir/in-out.c.o   -c "/home/mfattoru/MEGA/1 - NIU UNIVERSITY/CSCI 631/assign4/in-out.c"

CMakeFiles/assign4cli.dir/in-out.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/assign4cli.dir/in-out.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/mfattoru/MEGA/1 - NIU UNIVERSITY/CSCI 631/assign4/in-out.c" > CMakeFiles/assign4cli.dir/in-out.c.i

CMakeFiles/assign4cli.dir/in-out.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/assign4cli.dir/in-out.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/mfattoru/MEGA/1 - NIU UNIVERSITY/CSCI 631/assign4/in-out.c" -o CMakeFiles/assign4cli.dir/in-out.c.s

CMakeFiles/assign4cli.dir/in-out.c.o.requires:

.PHONY : CMakeFiles/assign4cli.dir/in-out.c.o.requires

CMakeFiles/assign4cli.dir/in-out.c.o.provides: CMakeFiles/assign4cli.dir/in-out.c.o.requires
	$(MAKE) -f CMakeFiles/assign4cli.dir/build.make CMakeFiles/assign4cli.dir/in-out.c.o.provides.build
.PHONY : CMakeFiles/assign4cli.dir/in-out.c.o.provides

CMakeFiles/assign4cli.dir/in-out.c.o.provides.build: CMakeFiles/assign4cli.dir/in-out.c.o


# Object files for target assign4cli
assign4cli_OBJECTS = \
"CMakeFiles/assign4cli.dir/prog4cli.c.o" \
"CMakeFiles/assign4cli.dir/wrap4cli.c.o" \
"CMakeFiles/assign4cli.dir/in-out.c.o"

# External object files for target assign4cli
assign4cli_EXTERNAL_OBJECTS =

assign4cli: CMakeFiles/assign4cli.dir/prog4cli.c.o
assign4cli: CMakeFiles/assign4cli.dir/wrap4cli.c.o
assign4cli: CMakeFiles/assign4cli.dir/in-out.c.o
assign4cli: CMakeFiles/assign4cli.dir/build.make
assign4cli: CMakeFiles/assign4cli.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/mfattoru/MEGA/1 - NIU UNIVERSITY/CSCI 631/assign4/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable assign4cli"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/assign4cli.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/assign4cli.dir/build: assign4cli

.PHONY : CMakeFiles/assign4cli.dir/build

CMakeFiles/assign4cli.dir/requires: CMakeFiles/assign4cli.dir/prog4cli.c.o.requires
CMakeFiles/assign4cli.dir/requires: CMakeFiles/assign4cli.dir/wrap4cli.c.o.requires
CMakeFiles/assign4cli.dir/requires: CMakeFiles/assign4cli.dir/in-out.c.o.requires

.PHONY : CMakeFiles/assign4cli.dir/requires

CMakeFiles/assign4cli.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/assign4cli.dir/cmake_clean.cmake
.PHONY : CMakeFiles/assign4cli.dir/clean

CMakeFiles/assign4cli.dir/depend:
	cd "/home/mfattoru/MEGA/1 - NIU UNIVERSITY/CSCI 631/assign4/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/mfattoru/MEGA/1 - NIU UNIVERSITY/CSCI 631/assign4" "/home/mfattoru/MEGA/1 - NIU UNIVERSITY/CSCI 631/assign4" "/home/mfattoru/MEGA/1 - NIU UNIVERSITY/CSCI 631/assign4/cmake-build-debug" "/home/mfattoru/MEGA/1 - NIU UNIVERSITY/CSCI 631/assign4/cmake-build-debug" "/home/mfattoru/MEGA/1 - NIU UNIVERSITY/CSCI 631/assign4/cmake-build-debug/CMakeFiles/assign4cli.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/assign4cli.dir/depend
