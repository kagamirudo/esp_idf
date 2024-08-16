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
include esp-idf/rt/CMakeFiles/__idf_rt.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include esp-idf/rt/CMakeFiles/__idf_rt.dir/compiler_depend.make

# Include the progress variables for this target.
include esp-idf/rt/CMakeFiles/__idf_rt.dir/progress.make

# Include the compile flags for this target's objects.
include esp-idf/rt/CMakeFiles/__idf_rt.dir/flags.make

esp-idf/rt/CMakeFiles/__idf_rt.dir/FreeRTOS_POSIX_mqueue.c.obj: esp-idf/rt/CMakeFiles/__idf_rt.dir/flags.make
esp-idf/rt/CMakeFiles/__idf_rt.dir/FreeRTOS_POSIX_mqueue.c.obj: ../../../components/rt/FreeRTOS_POSIX_mqueue.c
esp-idf/rt/CMakeFiles/__idf_rt.dir/FreeRTOS_POSIX_mqueue.c.obj: esp-idf/rt/CMakeFiles/__idf_rt.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kagamirudo/esp-idf/projects/01/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object esp-idf/rt/CMakeFiles/__idf_rt.dir/FreeRTOS_POSIX_mqueue.c.obj"
	cd /home/kagamirudo/esp-idf/projects/01/build/esp-idf/rt && /home/kagamirudo/.espressif/tools/xtensa-esp-elf/esp-13.2.0_20240530/xtensa-esp-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT esp-idf/rt/CMakeFiles/__idf_rt.dir/FreeRTOS_POSIX_mqueue.c.obj -MF CMakeFiles/__idf_rt.dir/FreeRTOS_POSIX_mqueue.c.obj.d -o CMakeFiles/__idf_rt.dir/FreeRTOS_POSIX_mqueue.c.obj -c /home/kagamirudo/esp-idf/components/rt/FreeRTOS_POSIX_mqueue.c

esp-idf/rt/CMakeFiles/__idf_rt.dir/FreeRTOS_POSIX_mqueue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_rt.dir/FreeRTOS_POSIX_mqueue.c.i"
	cd /home/kagamirudo/esp-idf/projects/01/build/esp-idf/rt && /home/kagamirudo/.espressif/tools/xtensa-esp-elf/esp-13.2.0_20240530/xtensa-esp-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kagamirudo/esp-idf/components/rt/FreeRTOS_POSIX_mqueue.c > CMakeFiles/__idf_rt.dir/FreeRTOS_POSIX_mqueue.c.i

esp-idf/rt/CMakeFiles/__idf_rt.dir/FreeRTOS_POSIX_mqueue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_rt.dir/FreeRTOS_POSIX_mqueue.c.s"
	cd /home/kagamirudo/esp-idf/projects/01/build/esp-idf/rt && /home/kagamirudo/.espressif/tools/xtensa-esp-elf/esp-13.2.0_20240530/xtensa-esp-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kagamirudo/esp-idf/components/rt/FreeRTOS_POSIX_mqueue.c -o CMakeFiles/__idf_rt.dir/FreeRTOS_POSIX_mqueue.c.s

esp-idf/rt/CMakeFiles/__idf_rt.dir/FreeRTOS_POSIX_utils.c.obj: esp-idf/rt/CMakeFiles/__idf_rt.dir/flags.make
esp-idf/rt/CMakeFiles/__idf_rt.dir/FreeRTOS_POSIX_utils.c.obj: ../../../components/rt/FreeRTOS_POSIX_utils.c
esp-idf/rt/CMakeFiles/__idf_rt.dir/FreeRTOS_POSIX_utils.c.obj: esp-idf/rt/CMakeFiles/__idf_rt.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kagamirudo/esp-idf/projects/01/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object esp-idf/rt/CMakeFiles/__idf_rt.dir/FreeRTOS_POSIX_utils.c.obj"
	cd /home/kagamirudo/esp-idf/projects/01/build/esp-idf/rt && /home/kagamirudo/.espressif/tools/xtensa-esp-elf/esp-13.2.0_20240530/xtensa-esp-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT esp-idf/rt/CMakeFiles/__idf_rt.dir/FreeRTOS_POSIX_utils.c.obj -MF CMakeFiles/__idf_rt.dir/FreeRTOS_POSIX_utils.c.obj.d -o CMakeFiles/__idf_rt.dir/FreeRTOS_POSIX_utils.c.obj -c /home/kagamirudo/esp-idf/components/rt/FreeRTOS_POSIX_utils.c

esp-idf/rt/CMakeFiles/__idf_rt.dir/FreeRTOS_POSIX_utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_rt.dir/FreeRTOS_POSIX_utils.c.i"
	cd /home/kagamirudo/esp-idf/projects/01/build/esp-idf/rt && /home/kagamirudo/.espressif/tools/xtensa-esp-elf/esp-13.2.0_20240530/xtensa-esp-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kagamirudo/esp-idf/components/rt/FreeRTOS_POSIX_utils.c > CMakeFiles/__idf_rt.dir/FreeRTOS_POSIX_utils.c.i

esp-idf/rt/CMakeFiles/__idf_rt.dir/FreeRTOS_POSIX_utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_rt.dir/FreeRTOS_POSIX_utils.c.s"
	cd /home/kagamirudo/esp-idf/projects/01/build/esp-idf/rt && /home/kagamirudo/.espressif/tools/xtensa-esp-elf/esp-13.2.0_20240530/xtensa-esp-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kagamirudo/esp-idf/components/rt/FreeRTOS_POSIX_utils.c -o CMakeFiles/__idf_rt.dir/FreeRTOS_POSIX_utils.c.s

# Object files for target __idf_rt
__idf_rt_OBJECTS = \
"CMakeFiles/__idf_rt.dir/FreeRTOS_POSIX_mqueue.c.obj" \
"CMakeFiles/__idf_rt.dir/FreeRTOS_POSIX_utils.c.obj"

# External object files for target __idf_rt
__idf_rt_EXTERNAL_OBJECTS =

esp-idf/rt/librt.a: esp-idf/rt/CMakeFiles/__idf_rt.dir/FreeRTOS_POSIX_mqueue.c.obj
esp-idf/rt/librt.a: esp-idf/rt/CMakeFiles/__idf_rt.dir/FreeRTOS_POSIX_utils.c.obj
esp-idf/rt/librt.a: esp-idf/rt/CMakeFiles/__idf_rt.dir/build.make
esp-idf/rt/librt.a: esp-idf/rt/CMakeFiles/__idf_rt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kagamirudo/esp-idf/projects/01/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C static library librt.a"
	cd /home/kagamirudo/esp-idf/projects/01/build/esp-idf/rt && $(CMAKE_COMMAND) -P CMakeFiles/__idf_rt.dir/cmake_clean_target.cmake
	cd /home/kagamirudo/esp-idf/projects/01/build/esp-idf/rt && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/__idf_rt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
esp-idf/rt/CMakeFiles/__idf_rt.dir/build: esp-idf/rt/librt.a
.PHONY : esp-idf/rt/CMakeFiles/__idf_rt.dir/build

esp-idf/rt/CMakeFiles/__idf_rt.dir/clean:
	cd /home/kagamirudo/esp-idf/projects/01/build/esp-idf/rt && $(CMAKE_COMMAND) -P CMakeFiles/__idf_rt.dir/cmake_clean.cmake
.PHONY : esp-idf/rt/CMakeFiles/__idf_rt.dir/clean

esp-idf/rt/CMakeFiles/__idf_rt.dir/depend:
	cd /home/kagamirudo/esp-idf/projects/01/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kagamirudo/esp-idf/projects/01 /home/kagamirudo/esp-idf/components/rt /home/kagamirudo/esp-idf/projects/01/build /home/kagamirudo/esp-idf/projects/01/build/esp-idf/rt /home/kagamirudo/esp-idf/projects/01/build/esp-idf/rt/CMakeFiles/__idf_rt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : esp-idf/rt/CMakeFiles/__idf_rt.dir/depend

