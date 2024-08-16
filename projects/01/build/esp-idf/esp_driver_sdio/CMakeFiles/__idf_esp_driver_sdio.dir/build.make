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
include esp-idf/esp_driver_sdio/CMakeFiles/__idf_esp_driver_sdio.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include esp-idf/esp_driver_sdio/CMakeFiles/__idf_esp_driver_sdio.dir/compiler_depend.make

# Include the progress variables for this target.
include esp-idf/esp_driver_sdio/CMakeFiles/__idf_esp_driver_sdio.dir/progress.make

# Include the compile flags for this target's objects.
include esp-idf/esp_driver_sdio/CMakeFiles/__idf_esp_driver_sdio.dir/flags.make

esp-idf/esp_driver_sdio/CMakeFiles/__idf_esp_driver_sdio.dir/src/sdio_slave.c.obj: esp-idf/esp_driver_sdio/CMakeFiles/__idf_esp_driver_sdio.dir/flags.make
esp-idf/esp_driver_sdio/CMakeFiles/__idf_esp_driver_sdio.dir/src/sdio_slave.c.obj: ../../../components/esp_driver_sdio/src/sdio_slave.c
esp-idf/esp_driver_sdio/CMakeFiles/__idf_esp_driver_sdio.dir/src/sdio_slave.c.obj: esp-idf/esp_driver_sdio/CMakeFiles/__idf_esp_driver_sdio.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kagamirudo/esp-idf/projects/01/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object esp-idf/esp_driver_sdio/CMakeFiles/__idf_esp_driver_sdio.dir/src/sdio_slave.c.obj"
	cd /home/kagamirudo/esp-idf/projects/01/build/esp-idf/esp_driver_sdio && /home/kagamirudo/.espressif/tools/xtensa-esp-elf/esp-13.2.0_20240530/xtensa-esp-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT esp-idf/esp_driver_sdio/CMakeFiles/__idf_esp_driver_sdio.dir/src/sdio_slave.c.obj -MF CMakeFiles/__idf_esp_driver_sdio.dir/src/sdio_slave.c.obj.d -o CMakeFiles/__idf_esp_driver_sdio.dir/src/sdio_slave.c.obj -c /home/kagamirudo/esp-idf/components/esp_driver_sdio/src/sdio_slave.c

esp-idf/esp_driver_sdio/CMakeFiles/__idf_esp_driver_sdio.dir/src/sdio_slave.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_esp_driver_sdio.dir/src/sdio_slave.c.i"
	cd /home/kagamirudo/esp-idf/projects/01/build/esp-idf/esp_driver_sdio && /home/kagamirudo/.espressif/tools/xtensa-esp-elf/esp-13.2.0_20240530/xtensa-esp-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kagamirudo/esp-idf/components/esp_driver_sdio/src/sdio_slave.c > CMakeFiles/__idf_esp_driver_sdio.dir/src/sdio_slave.c.i

esp-idf/esp_driver_sdio/CMakeFiles/__idf_esp_driver_sdio.dir/src/sdio_slave.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_esp_driver_sdio.dir/src/sdio_slave.c.s"
	cd /home/kagamirudo/esp-idf/projects/01/build/esp-idf/esp_driver_sdio && /home/kagamirudo/.espressif/tools/xtensa-esp-elf/esp-13.2.0_20240530/xtensa-esp-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kagamirudo/esp-idf/components/esp_driver_sdio/src/sdio_slave.c -o CMakeFiles/__idf_esp_driver_sdio.dir/src/sdio_slave.c.s

# Object files for target __idf_esp_driver_sdio
__idf_esp_driver_sdio_OBJECTS = \
"CMakeFiles/__idf_esp_driver_sdio.dir/src/sdio_slave.c.obj"

# External object files for target __idf_esp_driver_sdio
__idf_esp_driver_sdio_EXTERNAL_OBJECTS =

esp-idf/esp_driver_sdio/libesp_driver_sdio.a: esp-idf/esp_driver_sdio/CMakeFiles/__idf_esp_driver_sdio.dir/src/sdio_slave.c.obj
esp-idf/esp_driver_sdio/libesp_driver_sdio.a: esp-idf/esp_driver_sdio/CMakeFiles/__idf_esp_driver_sdio.dir/build.make
esp-idf/esp_driver_sdio/libesp_driver_sdio.a: esp-idf/esp_driver_sdio/CMakeFiles/__idf_esp_driver_sdio.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kagamirudo/esp-idf/projects/01/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libesp_driver_sdio.a"
	cd /home/kagamirudo/esp-idf/projects/01/build/esp-idf/esp_driver_sdio && $(CMAKE_COMMAND) -P CMakeFiles/__idf_esp_driver_sdio.dir/cmake_clean_target.cmake
	cd /home/kagamirudo/esp-idf/projects/01/build/esp-idf/esp_driver_sdio && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/__idf_esp_driver_sdio.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
esp-idf/esp_driver_sdio/CMakeFiles/__idf_esp_driver_sdio.dir/build: esp-idf/esp_driver_sdio/libesp_driver_sdio.a
.PHONY : esp-idf/esp_driver_sdio/CMakeFiles/__idf_esp_driver_sdio.dir/build

esp-idf/esp_driver_sdio/CMakeFiles/__idf_esp_driver_sdio.dir/clean:
	cd /home/kagamirudo/esp-idf/projects/01/build/esp-idf/esp_driver_sdio && $(CMAKE_COMMAND) -P CMakeFiles/__idf_esp_driver_sdio.dir/cmake_clean.cmake
.PHONY : esp-idf/esp_driver_sdio/CMakeFiles/__idf_esp_driver_sdio.dir/clean

esp-idf/esp_driver_sdio/CMakeFiles/__idf_esp_driver_sdio.dir/depend:
	cd /home/kagamirudo/esp-idf/projects/01/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kagamirudo/esp-idf/projects/01 /home/kagamirudo/esp-idf/components/esp_driver_sdio /home/kagamirudo/esp-idf/projects/01/build /home/kagamirudo/esp-idf/projects/01/build/esp-idf/esp_driver_sdio /home/kagamirudo/esp-idf/projects/01/build/esp-idf/esp_driver_sdio/CMakeFiles/__idf_esp_driver_sdio.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : esp-idf/esp_driver_sdio/CMakeFiles/__idf_esp_driver_sdio.dir/depend

