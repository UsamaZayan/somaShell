# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /home/usama/clion-2020.2.5/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/usama/clion-2020.2.5/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/usama/CLionProjects/SomaShell

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/usama/CLionProjects/SomaShell/cmake-build-default

# Include any dependencies generated for this target.
include CMakeFiles/SomaShell.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SomaShell.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SomaShell.dir/flags.make

CMakeFiles/SomaShell.dir/main.c.o: CMakeFiles/SomaShell.dir/flags.make
CMakeFiles/SomaShell.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/usama/CLionProjects/SomaShell/cmake-build-default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/SomaShell.dir/main.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/SomaShell.dir/main.c.o   -c /home/usama/CLionProjects/SomaShell/main.c

CMakeFiles/SomaShell.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SomaShell.dir/main.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/usama/CLionProjects/SomaShell/main.c > CMakeFiles/SomaShell.dir/main.c.i

CMakeFiles/SomaShell.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SomaShell.dir/main.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/usama/CLionProjects/SomaShell/main.c -o CMakeFiles/SomaShell.dir/main.c.s

# Object files for target SomaShell
SomaShell_OBJECTS = \
"CMakeFiles/SomaShell.dir/main.c.o"

# External object files for target SomaShell
SomaShell_EXTERNAL_OBJECTS =

SomaShell: CMakeFiles/SomaShell.dir/main.c.o
SomaShell: CMakeFiles/SomaShell.dir/build.make
SomaShell: CMakeFiles/SomaShell.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/usama/CLionProjects/SomaShell/cmake-build-default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable SomaShell"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SomaShell.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SomaShell.dir/build: SomaShell

.PHONY : CMakeFiles/SomaShell.dir/build

CMakeFiles/SomaShell.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SomaShell.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SomaShell.dir/clean

CMakeFiles/SomaShell.dir/depend:
	cd /home/usama/CLionProjects/SomaShell/cmake-build-default && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/usama/CLionProjects/SomaShell /home/usama/CLionProjects/SomaShell /home/usama/CLionProjects/SomaShell/cmake-build-default /home/usama/CLionProjects/SomaShell/cmake-build-default /home/usama/CLionProjects/SomaShell/cmake-build-default/CMakeFiles/SomaShell.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SomaShell.dir/depend

