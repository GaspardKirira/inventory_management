# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/softadastra/Documents/cpp/softadastra/src/entities/tests

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/softadastra/Documents/cpp/softadastra/src/entities/tests/build

# Include any dependencies generated for this target.
include CMakeFiles/prog.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/prog.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/prog.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/prog.dir/flags.make

CMakeFiles/prog.dir/test_main.cpp.o: CMakeFiles/prog.dir/flags.make
CMakeFiles/prog.dir/test_main.cpp.o: /home/softadastra/Documents/cpp/softadastra/src/entities/tests/test_main.cpp
CMakeFiles/prog.dir/test_main.cpp.o: CMakeFiles/prog.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/softadastra/Documents/cpp/softadastra/src/entities/tests/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/prog.dir/test_main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/prog.dir/test_main.cpp.o -MF CMakeFiles/prog.dir/test_main.cpp.o.d -o CMakeFiles/prog.dir/test_main.cpp.o -c /home/softadastra/Documents/cpp/softadastra/src/entities/tests/test_main.cpp

CMakeFiles/prog.dir/test_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/prog.dir/test_main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/softadastra/Documents/cpp/softadastra/src/entities/tests/test_main.cpp > CMakeFiles/prog.dir/test_main.cpp.i

CMakeFiles/prog.dir/test_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/prog.dir/test_main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/softadastra/Documents/cpp/softadastra/src/entities/tests/test_main.cpp -o CMakeFiles/prog.dir/test_main.cpp.s

# Object files for target prog
prog_OBJECTS = \
"CMakeFiles/prog.dir/test_main.cpp.o"

# External object files for target prog
prog_EXTERNAL_OBJECTS =

prog: CMakeFiles/prog.dir/test_main.cpp.o
prog: CMakeFiles/prog.dir/build.make
prog: /usr/local/lib/libgtest.a
prog: /usr/local/lib/libgtest_main.a
prog: CMakeFiles/prog.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/softadastra/Documents/cpp/softadastra/src/entities/tests/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable prog"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/prog.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/prog.dir/build: prog
.PHONY : CMakeFiles/prog.dir/build

CMakeFiles/prog.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/prog.dir/cmake_clean.cmake
.PHONY : CMakeFiles/prog.dir/clean

CMakeFiles/prog.dir/depend:
	cd /home/softadastra/Documents/cpp/softadastra/src/entities/tests/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/softadastra/Documents/cpp/softadastra/src/entities/tests /home/softadastra/Documents/cpp/softadastra/src/entities/tests /home/softadastra/Documents/cpp/softadastra/src/entities/tests/build /home/softadastra/Documents/cpp/softadastra/src/entities/tests/build /home/softadastra/Documents/cpp/softadastra/src/entities/tests/build/CMakeFiles/prog.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/prog.dir/depend

