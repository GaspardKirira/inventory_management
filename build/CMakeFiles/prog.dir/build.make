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
CMAKE_SOURCE_DIR = /home/softadastra/Documents/cpp/softadastra

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/softadastra/Documents/cpp/softadastra/build

# Include any dependencies generated for this target.
include CMakeFiles/prog.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/prog.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/prog.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/prog.dir/flags.make

CMakeFiles/prog.dir/src/config/Config.cpp.o: CMakeFiles/prog.dir/flags.make
CMakeFiles/prog.dir/src/config/Config.cpp.o: /home/softadastra/Documents/cpp/softadastra/src/config/Config.cpp
CMakeFiles/prog.dir/src/config/Config.cpp.o: CMakeFiles/prog.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/softadastra/Documents/cpp/softadastra/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/prog.dir/src/config/Config.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/prog.dir/src/config/Config.cpp.o -MF CMakeFiles/prog.dir/src/config/Config.cpp.o.d -o CMakeFiles/prog.dir/src/config/Config.cpp.o -c /home/softadastra/Documents/cpp/softadastra/src/config/Config.cpp

CMakeFiles/prog.dir/src/config/Config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/prog.dir/src/config/Config.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/softadastra/Documents/cpp/softadastra/src/config/Config.cpp > CMakeFiles/prog.dir/src/config/Config.cpp.i

CMakeFiles/prog.dir/src/config/Config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/prog.dir/src/config/Config.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/softadastra/Documents/cpp/softadastra/src/config/Config.cpp -o CMakeFiles/prog.dir/src/config/Config.cpp.s

CMakeFiles/prog.dir/src/kernel/DynamicRequestHandler.cpp.o: CMakeFiles/prog.dir/flags.make
CMakeFiles/prog.dir/src/kernel/DynamicRequestHandler.cpp.o: /home/softadastra/Documents/cpp/softadastra/src/kernel/DynamicRequestHandler.cpp
CMakeFiles/prog.dir/src/kernel/DynamicRequestHandler.cpp.o: CMakeFiles/prog.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/softadastra/Documents/cpp/softadastra/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/prog.dir/src/kernel/DynamicRequestHandler.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/prog.dir/src/kernel/DynamicRequestHandler.cpp.o -MF CMakeFiles/prog.dir/src/kernel/DynamicRequestHandler.cpp.o.d -o CMakeFiles/prog.dir/src/kernel/DynamicRequestHandler.cpp.o -c /home/softadastra/Documents/cpp/softadastra/src/kernel/DynamicRequestHandler.cpp

CMakeFiles/prog.dir/src/kernel/DynamicRequestHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/prog.dir/src/kernel/DynamicRequestHandler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/softadastra/Documents/cpp/softadastra/src/kernel/DynamicRequestHandler.cpp > CMakeFiles/prog.dir/src/kernel/DynamicRequestHandler.cpp.i

CMakeFiles/prog.dir/src/kernel/DynamicRequestHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/prog.dir/src/kernel/DynamicRequestHandler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/softadastra/Documents/cpp/softadastra/src/kernel/DynamicRequestHandler.cpp -o CMakeFiles/prog.dir/src/kernel/DynamicRequestHandler.cpp.s

CMakeFiles/prog.dir/src/kernel/HTTPServer.cpp.o: CMakeFiles/prog.dir/flags.make
CMakeFiles/prog.dir/src/kernel/HTTPServer.cpp.o: /home/softadastra/Documents/cpp/softadastra/src/kernel/HTTPServer.cpp
CMakeFiles/prog.dir/src/kernel/HTTPServer.cpp.o: CMakeFiles/prog.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/softadastra/Documents/cpp/softadastra/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/prog.dir/src/kernel/HTTPServer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/prog.dir/src/kernel/HTTPServer.cpp.o -MF CMakeFiles/prog.dir/src/kernel/HTTPServer.cpp.o.d -o CMakeFiles/prog.dir/src/kernel/HTTPServer.cpp.o -c /home/softadastra/Documents/cpp/softadastra/src/kernel/HTTPServer.cpp

CMakeFiles/prog.dir/src/kernel/HTTPServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/prog.dir/src/kernel/HTTPServer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/softadastra/Documents/cpp/softadastra/src/kernel/HTTPServer.cpp > CMakeFiles/prog.dir/src/kernel/HTTPServer.cpp.i

CMakeFiles/prog.dir/src/kernel/HTTPServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/prog.dir/src/kernel/HTTPServer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/softadastra/Documents/cpp/softadastra/src/kernel/HTTPServer.cpp -o CMakeFiles/prog.dir/src/kernel/HTTPServer.cpp.s

CMakeFiles/prog.dir/src/kernel/ResponseSender.cpp.o: CMakeFiles/prog.dir/flags.make
CMakeFiles/prog.dir/src/kernel/ResponseSender.cpp.o: /home/softadastra/Documents/cpp/softadastra/src/kernel/ResponseSender.cpp
CMakeFiles/prog.dir/src/kernel/ResponseSender.cpp.o: CMakeFiles/prog.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/softadastra/Documents/cpp/softadastra/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/prog.dir/src/kernel/ResponseSender.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/prog.dir/src/kernel/ResponseSender.cpp.o -MF CMakeFiles/prog.dir/src/kernel/ResponseSender.cpp.o.d -o CMakeFiles/prog.dir/src/kernel/ResponseSender.cpp.o -c /home/softadastra/Documents/cpp/softadastra/src/kernel/ResponseSender.cpp

CMakeFiles/prog.dir/src/kernel/ResponseSender.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/prog.dir/src/kernel/ResponseSender.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/softadastra/Documents/cpp/softadastra/src/kernel/ResponseSender.cpp > CMakeFiles/prog.dir/src/kernel/ResponseSender.cpp.i

CMakeFiles/prog.dir/src/kernel/ResponseSender.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/prog.dir/src/kernel/ResponseSender.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/softadastra/Documents/cpp/softadastra/src/kernel/ResponseSender.cpp -o CMakeFiles/prog.dir/src/kernel/ResponseSender.cpp.s

CMakeFiles/prog.dir/src/kernel/Router.cpp.o: CMakeFiles/prog.dir/flags.make
CMakeFiles/prog.dir/src/kernel/Router.cpp.o: /home/softadastra/Documents/cpp/softadastra/src/kernel/Router.cpp
CMakeFiles/prog.dir/src/kernel/Router.cpp.o: CMakeFiles/prog.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/softadastra/Documents/cpp/softadastra/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/prog.dir/src/kernel/Router.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/prog.dir/src/kernel/Router.cpp.o -MF CMakeFiles/prog.dir/src/kernel/Router.cpp.o.d -o CMakeFiles/prog.dir/src/kernel/Router.cpp.o -c /home/softadastra/Documents/cpp/softadastra/src/kernel/Router.cpp

CMakeFiles/prog.dir/src/kernel/Router.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/prog.dir/src/kernel/Router.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/softadastra/Documents/cpp/softadastra/src/kernel/Router.cpp > CMakeFiles/prog.dir/src/kernel/Router.cpp.i

CMakeFiles/prog.dir/src/kernel/Router.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/prog.dir/src/kernel/Router.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/softadastra/Documents/cpp/softadastra/src/kernel/Router.cpp -o CMakeFiles/prog.dir/src/kernel/Router.cpp.s

CMakeFiles/prog.dir/src/kernel/Session.cpp.o: CMakeFiles/prog.dir/flags.make
CMakeFiles/prog.dir/src/kernel/Session.cpp.o: /home/softadastra/Documents/cpp/softadastra/src/kernel/Session.cpp
CMakeFiles/prog.dir/src/kernel/Session.cpp.o: CMakeFiles/prog.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/softadastra/Documents/cpp/softadastra/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/prog.dir/src/kernel/Session.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/prog.dir/src/kernel/Session.cpp.o -MF CMakeFiles/prog.dir/src/kernel/Session.cpp.o.d -o CMakeFiles/prog.dir/src/kernel/Session.cpp.o -c /home/softadastra/Documents/cpp/softadastra/src/kernel/Session.cpp

CMakeFiles/prog.dir/src/kernel/Session.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/prog.dir/src/kernel/Session.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/softadastra/Documents/cpp/softadastra/src/kernel/Session.cpp > CMakeFiles/prog.dir/src/kernel/Session.cpp.i

CMakeFiles/prog.dir/src/kernel/Session.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/prog.dir/src/kernel/Session.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/softadastra/Documents/cpp/softadastra/src/kernel/Session.cpp -o CMakeFiles/prog.dir/src/kernel/Session.cpp.s

CMakeFiles/prog.dir/src/kernel/SimpleRequestHandler.cpp.o: CMakeFiles/prog.dir/flags.make
CMakeFiles/prog.dir/src/kernel/SimpleRequestHandler.cpp.o: /home/softadastra/Documents/cpp/softadastra/src/kernel/SimpleRequestHandler.cpp
CMakeFiles/prog.dir/src/kernel/SimpleRequestHandler.cpp.o: CMakeFiles/prog.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/softadastra/Documents/cpp/softadastra/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/prog.dir/src/kernel/SimpleRequestHandler.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/prog.dir/src/kernel/SimpleRequestHandler.cpp.o -MF CMakeFiles/prog.dir/src/kernel/SimpleRequestHandler.cpp.o.d -o CMakeFiles/prog.dir/src/kernel/SimpleRequestHandler.cpp.o -c /home/softadastra/Documents/cpp/softadastra/src/kernel/SimpleRequestHandler.cpp

CMakeFiles/prog.dir/src/kernel/SimpleRequestHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/prog.dir/src/kernel/SimpleRequestHandler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/softadastra/Documents/cpp/softadastra/src/kernel/SimpleRequestHandler.cpp > CMakeFiles/prog.dir/src/kernel/SimpleRequestHandler.cpp.i

CMakeFiles/prog.dir/src/kernel/SimpleRequestHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/prog.dir/src/kernel/SimpleRequestHandler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/softadastra/Documents/cpp/softadastra/src/kernel/SimpleRequestHandler.cpp -o CMakeFiles/prog.dir/src/kernel/SimpleRequestHandler.cpp.s

CMakeFiles/prog.dir/src/main.cpp.o: CMakeFiles/prog.dir/flags.make
CMakeFiles/prog.dir/src/main.cpp.o: /home/softadastra/Documents/cpp/softadastra/src/main.cpp
CMakeFiles/prog.dir/src/main.cpp.o: CMakeFiles/prog.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/softadastra/Documents/cpp/softadastra/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/prog.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/prog.dir/src/main.cpp.o -MF CMakeFiles/prog.dir/src/main.cpp.o.d -o CMakeFiles/prog.dir/src/main.cpp.o -c /home/softadastra/Documents/cpp/softadastra/src/main.cpp

CMakeFiles/prog.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/prog.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/softadastra/Documents/cpp/softadastra/src/main.cpp > CMakeFiles/prog.dir/src/main.cpp.i

CMakeFiles/prog.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/prog.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/softadastra/Documents/cpp/softadastra/src/main.cpp -o CMakeFiles/prog.dir/src/main.cpp.s

# Object files for target prog
prog_OBJECTS = \
"CMakeFiles/prog.dir/src/config/Config.cpp.o" \
"CMakeFiles/prog.dir/src/kernel/DynamicRequestHandler.cpp.o" \
"CMakeFiles/prog.dir/src/kernel/HTTPServer.cpp.o" \
"CMakeFiles/prog.dir/src/kernel/ResponseSender.cpp.o" \
"CMakeFiles/prog.dir/src/kernel/Router.cpp.o" \
"CMakeFiles/prog.dir/src/kernel/Session.cpp.o" \
"CMakeFiles/prog.dir/src/kernel/SimpleRequestHandler.cpp.o" \
"CMakeFiles/prog.dir/src/main.cpp.o"

# External object files for target prog
prog_EXTERNAL_OBJECTS =

prog: CMakeFiles/prog.dir/src/config/Config.cpp.o
prog: CMakeFiles/prog.dir/src/kernel/DynamicRequestHandler.cpp.o
prog: CMakeFiles/prog.dir/src/kernel/HTTPServer.cpp.o
prog: CMakeFiles/prog.dir/src/kernel/ResponseSender.cpp.o
prog: CMakeFiles/prog.dir/src/kernel/Router.cpp.o
prog: CMakeFiles/prog.dir/src/kernel/Session.cpp.o
prog: CMakeFiles/prog.dir/src/kernel/SimpleRequestHandler.cpp.o
prog: CMakeFiles/prog.dir/src/main.cpp.o
prog: CMakeFiles/prog.dir/build.make
prog: /usr/lib/x86_64-linux-gnu/libssl.so
prog: /usr/lib/x86_64-linux-gnu/libcrypto.so
prog: CMakeFiles/prog.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/softadastra/Documents/cpp/softadastra/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable prog"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/prog.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/prog.dir/build: prog
.PHONY : CMakeFiles/prog.dir/build

CMakeFiles/prog.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/prog.dir/cmake_clean.cmake
.PHONY : CMakeFiles/prog.dir/clean

CMakeFiles/prog.dir/depend:
	cd /home/softadastra/Documents/cpp/softadastra/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/softadastra/Documents/cpp/softadastra /home/softadastra/Documents/cpp/softadastra /home/softadastra/Documents/cpp/softadastra/build /home/softadastra/Documents/cpp/softadastra/build /home/softadastra/Documents/cpp/softadastra/build/CMakeFiles/prog.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/prog.dir/depend

