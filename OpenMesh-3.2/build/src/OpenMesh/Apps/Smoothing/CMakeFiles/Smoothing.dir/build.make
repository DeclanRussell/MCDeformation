# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/dexternation/MasterClass/MCDeformation/OpenMesh-3.2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dexternation/MasterClass/MCDeformation/OpenMesh-3.2/build

# Include any dependencies generated for this target.
include src/OpenMesh/Apps/Smoothing/CMakeFiles/Smoothing.dir/depend.make

# Include the progress variables for this target.
include src/OpenMesh/Apps/Smoothing/CMakeFiles/Smoothing.dir/progress.make

# Include the compile flags for this target's objects.
include src/OpenMesh/Apps/Smoothing/CMakeFiles/Smoothing.dir/flags.make

src/OpenMesh/Apps/Smoothing/CMakeFiles/Smoothing.dir/smooth.cc.o: src/OpenMesh/Apps/Smoothing/CMakeFiles/Smoothing.dir/flags.make
src/OpenMesh/Apps/Smoothing/CMakeFiles/Smoothing.dir/smooth.cc.o: ../src/OpenMesh/Apps/Smoothing/smooth.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dexternation/MasterClass/MCDeformation/OpenMesh-3.2/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/OpenMesh/Apps/Smoothing/CMakeFiles/Smoothing.dir/smooth.cc.o"
	cd /home/dexternation/MasterClass/MCDeformation/OpenMesh-3.2/build/src/OpenMesh/Apps/Smoothing && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Smoothing.dir/smooth.cc.o -c /home/dexternation/MasterClass/MCDeformation/OpenMesh-3.2/src/OpenMesh/Apps/Smoothing/smooth.cc

src/OpenMesh/Apps/Smoothing/CMakeFiles/Smoothing.dir/smooth.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Smoothing.dir/smooth.cc.i"
	cd /home/dexternation/MasterClass/MCDeformation/OpenMesh-3.2/build/src/OpenMesh/Apps/Smoothing && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dexternation/MasterClass/MCDeformation/OpenMesh-3.2/src/OpenMesh/Apps/Smoothing/smooth.cc > CMakeFiles/Smoothing.dir/smooth.cc.i

src/OpenMesh/Apps/Smoothing/CMakeFiles/Smoothing.dir/smooth.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Smoothing.dir/smooth.cc.s"
	cd /home/dexternation/MasterClass/MCDeformation/OpenMesh-3.2/build/src/OpenMesh/Apps/Smoothing && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dexternation/MasterClass/MCDeformation/OpenMesh-3.2/src/OpenMesh/Apps/Smoothing/smooth.cc -o CMakeFiles/Smoothing.dir/smooth.cc.s

src/OpenMesh/Apps/Smoothing/CMakeFiles/Smoothing.dir/smooth.cc.o.requires:
.PHONY : src/OpenMesh/Apps/Smoothing/CMakeFiles/Smoothing.dir/smooth.cc.o.requires

src/OpenMesh/Apps/Smoothing/CMakeFiles/Smoothing.dir/smooth.cc.o.provides: src/OpenMesh/Apps/Smoothing/CMakeFiles/Smoothing.dir/smooth.cc.o.requires
	$(MAKE) -f src/OpenMesh/Apps/Smoothing/CMakeFiles/Smoothing.dir/build.make src/OpenMesh/Apps/Smoothing/CMakeFiles/Smoothing.dir/smooth.cc.o.provides.build
.PHONY : src/OpenMesh/Apps/Smoothing/CMakeFiles/Smoothing.dir/smooth.cc.o.provides

src/OpenMesh/Apps/Smoothing/CMakeFiles/Smoothing.dir/smooth.cc.o.provides.build: src/OpenMesh/Apps/Smoothing/CMakeFiles/Smoothing.dir/smooth.cc.o

# Object files for target Smoothing
Smoothing_OBJECTS = \
"CMakeFiles/Smoothing.dir/smooth.cc.o"

# External object files for target Smoothing
Smoothing_EXTERNAL_OBJECTS =

Build/bin/Smoothing: src/OpenMesh/Apps/Smoothing/CMakeFiles/Smoothing.dir/smooth.cc.o
Build/bin/Smoothing: src/OpenMesh/Apps/Smoothing/CMakeFiles/Smoothing.dir/build.make
Build/bin/Smoothing: Build/lib/OpenMesh/libOpenMeshCored.so.3.2
Build/bin/Smoothing: Build/lib/OpenMesh/libOpenMeshToolsd.so.3.2
Build/bin/Smoothing: Build/lib/OpenMesh/libOpenMeshCored.so.3.2
Build/bin/Smoothing: src/OpenMesh/Apps/Smoothing/CMakeFiles/Smoothing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../../../Build/bin/Smoothing"
	cd /home/dexternation/MasterClass/MCDeformation/OpenMesh-3.2/build/src/OpenMesh/Apps/Smoothing && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Smoothing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/OpenMesh/Apps/Smoothing/CMakeFiles/Smoothing.dir/build: Build/bin/Smoothing
.PHONY : src/OpenMesh/Apps/Smoothing/CMakeFiles/Smoothing.dir/build

src/OpenMesh/Apps/Smoothing/CMakeFiles/Smoothing.dir/requires: src/OpenMesh/Apps/Smoothing/CMakeFiles/Smoothing.dir/smooth.cc.o.requires
.PHONY : src/OpenMesh/Apps/Smoothing/CMakeFiles/Smoothing.dir/requires

src/OpenMesh/Apps/Smoothing/CMakeFiles/Smoothing.dir/clean:
	cd /home/dexternation/MasterClass/MCDeformation/OpenMesh-3.2/build/src/OpenMesh/Apps/Smoothing && $(CMAKE_COMMAND) -P CMakeFiles/Smoothing.dir/cmake_clean.cmake
.PHONY : src/OpenMesh/Apps/Smoothing/CMakeFiles/Smoothing.dir/clean

src/OpenMesh/Apps/Smoothing/CMakeFiles/Smoothing.dir/depend:
	cd /home/dexternation/MasterClass/MCDeformation/OpenMesh-3.2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dexternation/MasterClass/MCDeformation/OpenMesh-3.2 /home/dexternation/MasterClass/MCDeformation/OpenMesh-3.2/src/OpenMesh/Apps/Smoothing /home/dexternation/MasterClass/MCDeformation/OpenMesh-3.2/build /home/dexternation/MasterClass/MCDeformation/OpenMesh-3.2/build/src/OpenMesh/Apps/Smoothing /home/dexternation/MasterClass/MCDeformation/OpenMesh-3.2/build/src/OpenMesh/Apps/Smoothing/CMakeFiles/Smoothing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/OpenMesh/Apps/Smoothing/CMakeFiles/Smoothing.dir/depend

