# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /Users/smorphet/.brew/Cellar/cmake/3.27.7/bin/cmake

# The command to remove a file.
RM = /Users/smorphet/.brew/Cellar/cmake/3.27.7/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/smorphet/Desktop/42-scop/libs/glfw-3.4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/smorphet/Desktop/42-scop/libs/glfw-3.4

# Include any dependencies generated for this target.
include tests/CMakeFiles/window.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/window.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/window.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/window.dir/flags.make

tests/CMakeFiles/window.dir/window.c.o: tests/CMakeFiles/window.dir/flags.make
tests/CMakeFiles/window.dir/window.c.o: tests/window.c
tests/CMakeFiles/window.dir/window.c.o: tests/CMakeFiles/window.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/smorphet/Desktop/42-scop/libs/glfw-3.4/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/window.dir/window.c.o"
	cd /Users/smorphet/Desktop/42-scop/libs/glfw-3.4/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/CMakeFiles/window.dir/window.c.o -MF CMakeFiles/window.dir/window.c.o.d -o CMakeFiles/window.dir/window.c.o -c /Users/smorphet/Desktop/42-scop/libs/glfw-3.4/tests/window.c

tests/CMakeFiles/window.dir/window.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/window.dir/window.c.i"
	cd /Users/smorphet/Desktop/42-scop/libs/glfw-3.4/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/smorphet/Desktop/42-scop/libs/glfw-3.4/tests/window.c > CMakeFiles/window.dir/window.c.i

tests/CMakeFiles/window.dir/window.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/window.dir/window.c.s"
	cd /Users/smorphet/Desktop/42-scop/libs/glfw-3.4/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/smorphet/Desktop/42-scop/libs/glfw-3.4/tests/window.c -o CMakeFiles/window.dir/window.c.s

# Object files for target window
window_OBJECTS = \
"CMakeFiles/window.dir/window.c.o"

# External object files for target window
window_EXTERNAL_OBJECTS =

tests/window.app/Contents/MacOS/window: tests/CMakeFiles/window.dir/window.c.o
tests/window.app/Contents/MacOS/window: tests/CMakeFiles/window.dir/build.make
tests/window.app/Contents/MacOS/window: src/libglfw3.a
tests/window.app/Contents/MacOS/window: tests/CMakeFiles/window.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/smorphet/Desktop/42-scop/libs/glfw-3.4/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable window.app/Contents/MacOS/window"
	cd /Users/smorphet/Desktop/42-scop/libs/glfw-3.4/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/window.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/window.dir/build: tests/window.app/Contents/MacOS/window
.PHONY : tests/CMakeFiles/window.dir/build

tests/CMakeFiles/window.dir/clean:
	cd /Users/smorphet/Desktop/42-scop/libs/glfw-3.4/tests && $(CMAKE_COMMAND) -P CMakeFiles/window.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/window.dir/clean

tests/CMakeFiles/window.dir/depend:
	cd /Users/smorphet/Desktop/42-scop/libs/glfw-3.4 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/smorphet/Desktop/42-scop/libs/glfw-3.4 /Users/smorphet/Desktop/42-scop/libs/glfw-3.4/tests /Users/smorphet/Desktop/42-scop/libs/glfw-3.4 /Users/smorphet/Desktop/42-scop/libs/glfw-3.4/tests /Users/smorphet/Desktop/42-scop/libs/glfw-3.4/tests/CMakeFiles/window.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : tests/CMakeFiles/window.dir/depend

