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
CMAKE_SOURCE_DIR = /home/kagamirudo/esp-idf/projects/01

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kagamirudo/esp-idf/projects/01/build

# Include any dependencies generated for this target.
include esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/compiler_depend.make

# Include the progress variables for this target.
include esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/progress.make

# Include the compile flags for this target's objects.
include esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/flags.make

esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/default_event_loop.c.obj: esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/flags.make
esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/default_event_loop.c.obj: ../../../components/esp_event/default_event_loop.c
esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/default_event_loop.c.obj: esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kagamirudo/esp-idf/projects/01/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/default_event_loop.c.obj"
	cd /home/kagamirudo/esp-idf/projects/01/build/esp-idf/esp_event && /home/kagamirudo/.espressif/tools/xtensa-esp-elf/esp-13.2.0_20240530/xtensa-esp-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/default_event_loop.c.obj -MF CMakeFiles/__idf_esp_event.dir/default_event_loop.c.obj.d -o CMakeFiles/__idf_esp_event.dir/default_event_loop.c.obj -c /home/kagamirudo/esp-idf/components/esp_event/default_event_loop.c

esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/default_event_loop.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_esp_event.dir/default_event_loop.c.i"
	cd /home/kagamirudo/esp-idf/projects/01/build/esp-idf/esp_event && /home/kagamirudo/.espressif/tools/xtensa-esp-elf/esp-13.2.0_20240530/xtensa-esp-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kagamirudo/esp-idf/components/esp_event/default_event_loop.c > CMakeFiles/__idf_esp_event.dir/default_event_loop.c.i

esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/default_event_loop.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_esp_event.dir/default_event_loop.c.s"
	cd /home/kagamirudo/esp-idf/projects/01/build/esp-idf/esp_event && /home/kagamirudo/.espressif/tools/xtensa-esp-elf/esp-13.2.0_20240530/xtensa-esp-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kagamirudo/esp-idf/components/esp_event/default_event_loop.c -o CMakeFiles/__idf_esp_event.dir/default_event_loop.c.s

esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/esp_event.c.obj: esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/flags.make
esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/esp_event.c.obj: ../../../components/esp_event/esp_event.c
esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/esp_event.c.obj: esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kagamirudo/esp-idf/projects/01/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/esp_event.c.obj"
	cd /home/kagamirudo/esp-idf/projects/01/build/esp-idf/esp_event && /home/kagamirudo/.espressif/tools/xtensa-esp-elf/esp-13.2.0_20240530/xtensa-esp-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/esp_event.c.obj -MF CMakeFiles/__idf_esp_event.dir/esp_event.c.obj.d -o CMakeFiles/__idf_esp_event.dir/esp_event.c.obj -c /home/kagamirudo/esp-idf/components/esp_event/esp_event.c

esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/esp_event.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_esp_event.dir/esp_event.c.i"
	cd /home/kagamirudo/esp-idf/projects/01/build/esp-idf/esp_event && /home/kagamirudo/.espressif/tools/xtensa-esp-elf/esp-13.2.0_20240530/xtensa-esp-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kagamirudo/esp-idf/components/esp_event/esp_event.c > CMakeFiles/__idf_esp_event.dir/esp_event.c.i

esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/esp_event.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_esp_event.dir/esp_event.c.s"
	cd /home/kagamirudo/esp-idf/projects/01/build/esp-idf/esp_event && /home/kagamirudo/.espressif/tools/xtensa-esp-elf/esp-13.2.0_20240530/xtensa-esp-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kagamirudo/esp-idf/components/esp_event/esp_event.c -o CMakeFiles/__idf_esp_event.dir/esp_event.c.s

esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/esp_event_private.c.obj: esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/flags.make
esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/esp_event_private.c.obj: ../../../components/esp_event/esp_event_private.c
esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/esp_event_private.c.obj: esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kagamirudo/esp-idf/projects/01/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/esp_event_private.c.obj"
	cd /home/kagamirudo/esp-idf/projects/01/build/esp-idf/esp_event && /home/kagamirudo/.espressif/tools/xtensa-esp-elf/esp-13.2.0_20240530/xtensa-esp-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/esp_event_private.c.obj -MF CMakeFiles/__idf_esp_event.dir/esp_event_private.c.obj.d -o CMakeFiles/__idf_esp_event.dir/esp_event_private.c.obj -c /home/kagamirudo/esp-idf/components/esp_event/esp_event_private.c

esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/esp_event_private.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_esp_event.dir/esp_event_private.c.i"
	cd /home/kagamirudo/esp-idf/projects/01/build/esp-idf/esp_event && /home/kagamirudo/.espressif/tools/xtensa-esp-elf/esp-13.2.0_20240530/xtensa-esp-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kagamirudo/esp-idf/components/esp_event/esp_event_private.c > CMakeFiles/__idf_esp_event.dir/esp_event_private.c.i

esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/esp_event_private.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_esp_event.dir/esp_event_private.c.s"
	cd /home/kagamirudo/esp-idf/projects/01/build/esp-idf/esp_event && /home/kagamirudo/.espressif/tools/xtensa-esp-elf/esp-13.2.0_20240530/xtensa-esp-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kagamirudo/esp-idf/components/esp_event/esp_event_private.c -o CMakeFiles/__idf_esp_event.dir/esp_event_private.c.s

# Object files for target __idf_esp_event
__idf_esp_event_OBJECTS = \
"CMakeFiles/__idf_esp_event.dir/default_event_loop.c.obj" \
"CMakeFiles/__idf_esp_event.dir/esp_event.c.obj" \
"CMakeFiles/__idf_esp_event.dir/esp_event_private.c.obj"

# External object files for target __idf_esp_event
__idf_esp_event_EXTERNAL_OBJECTS =

esp-idf/esp_event/libesp_event.a: esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/default_event_loop.c.obj
esp-idf/esp_event/libesp_event.a: esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/esp_event.c.obj
esp-idf/esp_event/libesp_event.a: esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/esp_event_private.c.obj
esp-idf/esp_event/libesp_event.a: esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/build.make
esp-idf/esp_event/libesp_event.a: esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kagamirudo/esp-idf/projects/01/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C static library libesp_event.a"
	cd /home/kagamirudo/esp-idf/projects/01/build/esp-idf/esp_event && $(CMAKE_COMMAND) -P CMakeFiles/__idf_esp_event.dir/cmake_clean_target.cmake
	cd /home/kagamirudo/esp-idf/projects/01/build/esp-idf/esp_event && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/__idf_esp_event.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/build: esp-idf/esp_event/libesp_event.a
.PHONY : esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/build

esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/clean:
	cd /home/kagamirudo/esp-idf/projects/01/build/esp-idf/esp_event && $(CMAKE_COMMAND) -P CMakeFiles/__idf_esp_event.dir/cmake_clean.cmake
.PHONY : esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/clean

esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/depend:
	cd /home/kagamirudo/esp-idf/projects/01/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kagamirudo/esp-idf/projects/01 /home/kagamirudo/esp-idf/components/esp_event /home/kagamirudo/esp-idf/projects/01/build /home/kagamirudo/esp-idf/projects/01/build/esp-idf/esp_event /home/kagamirudo/esp-idf/projects/01/build/esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : esp-idf/esp_event/CMakeFiles/__idf_esp_event.dir/depend

