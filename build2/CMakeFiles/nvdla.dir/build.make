# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/ILAng/build/ila_model_NVDLA_CMAC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/ILAng/build/ila_model_NVDLA_CMAC/build2

# Include any dependencies generated for this target.
include CMakeFiles/nvdla.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/nvdla.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/nvdla.dir/flags.make

CMakeFiles/nvdla.dir/app/main.cc.o: CMakeFiles/nvdla.dir/flags.make
CMakeFiles/nvdla.dir/app/main.cc.o: ../app/main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/ILAng/build/ila_model_NVDLA_CMAC/build2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/nvdla.dir/app/main.cc.o"
	g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/nvdla.dir/app/main.cc.o -c /root/ILAng/build/ila_model_NVDLA_CMAC/app/main.cc

CMakeFiles/nvdla.dir/app/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nvdla.dir/app/main.cc.i"
	g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/ILAng/build/ila_model_NVDLA_CMAC/app/main.cc > CMakeFiles/nvdla.dir/app/main.cc.i

CMakeFiles/nvdla.dir/app/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nvdla.dir/app/main.cc.s"
	g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/ILAng/build/ila_model_NVDLA_CMAC/app/main.cc -o CMakeFiles/nvdla.dir/app/main.cc.s

CMakeFiles/nvdla.dir/app/main.cc.o.requires:

.PHONY : CMakeFiles/nvdla.dir/app/main.cc.o.requires

CMakeFiles/nvdla.dir/app/main.cc.o.provides: CMakeFiles/nvdla.dir/app/main.cc.o.requires
	$(MAKE) -f CMakeFiles/nvdla.dir/build.make CMakeFiles/nvdla.dir/app/main.cc.o.provides.build
.PHONY : CMakeFiles/nvdla.dir/app/main.cc.o.provides

CMakeFiles/nvdla.dir/app/main.cc.o.provides.build: CMakeFiles/nvdla.dir/app/main.cc.o


# Object files for target nvdla
nvdla_OBJECTS = \
"CMakeFiles/nvdla.dir/app/main.cc.o"

# External object files for target nvdla
nvdla_EXTERNAL_OBJECTS =

nvdla: CMakeFiles/nvdla.dir/app/main.cc.o
nvdla: CMakeFiles/nvdla.dir/build.make
nvdla: libnvdlaila.a
nvdla: /usr/local/lib/libilang.so
nvdla: /usr/lib/x86_64-linux-gnu/libz3.so
nvdla: /usr/local/lib/libglog.so.0.4.0
nvdla: /usr/local/lib/libfmt.so.6.1.2
nvdla: /usr/local/lib/libverilogparser.so
nvdla: /usr/local/lib/libvcdparser.so
nvdla: /usr/local/lib/libsmtparser.so
nvdla: CMakeFiles/nvdla.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/ILAng/build/ila_model_NVDLA_CMAC/build2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable nvdla"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/nvdla.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/nvdla.dir/build: nvdla

.PHONY : CMakeFiles/nvdla.dir/build

CMakeFiles/nvdla.dir/requires: CMakeFiles/nvdla.dir/app/main.cc.o.requires

.PHONY : CMakeFiles/nvdla.dir/requires

CMakeFiles/nvdla.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/nvdla.dir/cmake_clean.cmake
.PHONY : CMakeFiles/nvdla.dir/clean

CMakeFiles/nvdla.dir/depend:
	cd /root/ILAng/build/ila_model_NVDLA_CMAC/build2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/ILAng/build/ila_model_NVDLA_CMAC /root/ILAng/build/ila_model_NVDLA_CMAC /root/ILAng/build/ila_model_NVDLA_CMAC/build2 /root/ILAng/build/ila_model_NVDLA_CMAC/build2 /root/ILAng/build/ila_model_NVDLA_CMAC/build2/CMakeFiles/nvdla.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/nvdla.dir/depend

