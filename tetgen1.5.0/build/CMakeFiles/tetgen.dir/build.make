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
CMAKE_SOURCE_DIR = /home/dexternation/Downloads/tetgen1.5.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dexternation/Downloads/tetgen1.5.0/build

# Include any dependencies generated for this target.
include CMakeFiles/tetgen.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tetgen.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tetgen.dir/flags.make

CMakeFiles/tetgen.dir/tetgen.cxx.o: CMakeFiles/tetgen.dir/flags.make
CMakeFiles/tetgen.dir/tetgen.cxx.o: ../tetgen.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dexternation/Downloads/tetgen1.5.0/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/tetgen.dir/tetgen.cxx.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tetgen.dir/tetgen.cxx.o -c /home/dexternation/Downloads/tetgen1.5.0/tetgen.cxx

CMakeFiles/tetgen.dir/tetgen.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tetgen.dir/tetgen.cxx.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dexternation/Downloads/tetgen1.5.0/tetgen.cxx > CMakeFiles/tetgen.dir/tetgen.cxx.i

CMakeFiles/tetgen.dir/tetgen.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tetgen.dir/tetgen.cxx.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dexternation/Downloads/tetgen1.5.0/tetgen.cxx -o CMakeFiles/tetgen.dir/tetgen.cxx.s

CMakeFiles/tetgen.dir/tetgen.cxx.o.requires:
.PHONY : CMakeFiles/tetgen.dir/tetgen.cxx.o.requires

CMakeFiles/tetgen.dir/tetgen.cxx.o.provides: CMakeFiles/tetgen.dir/tetgen.cxx.o.requires
	$(MAKE) -f CMakeFiles/tetgen.dir/build.make CMakeFiles/tetgen.dir/tetgen.cxx.o.provides.build
.PHONY : CMakeFiles/tetgen.dir/tetgen.cxx.o.provides

CMakeFiles/tetgen.dir/tetgen.cxx.o.provides.build: CMakeFiles/tetgen.dir/tetgen.cxx.o

CMakeFiles/tetgen.dir/predicates.cxx.o: CMakeFiles/tetgen.dir/flags.make
CMakeFiles/tetgen.dir/predicates.cxx.o: ../predicates.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dexternation/Downloads/tetgen1.5.0/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/tetgen.dir/predicates.cxx.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tetgen.dir/predicates.cxx.o -c /home/dexternation/Downloads/tetgen1.5.0/predicates.cxx

CMakeFiles/tetgen.dir/predicates.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tetgen.dir/predicates.cxx.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dexternation/Downloads/tetgen1.5.0/predicates.cxx > CMakeFiles/tetgen.dir/predicates.cxx.i

CMakeFiles/tetgen.dir/predicates.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tetgen.dir/predicates.cxx.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dexternation/Downloads/tetgen1.5.0/predicates.cxx -o CMakeFiles/tetgen.dir/predicates.cxx.s

CMakeFiles/tetgen.dir/predicates.cxx.o.requires:
.PHONY : CMakeFiles/tetgen.dir/predicates.cxx.o.requires

CMakeFiles/tetgen.dir/predicates.cxx.o.provides: CMakeFiles/tetgen.dir/predicates.cxx.o.requires
	$(MAKE) -f CMakeFiles/tetgen.dir/build.make CMakeFiles/tetgen.dir/predicates.cxx.o.provides.build
.PHONY : CMakeFiles/tetgen.dir/predicates.cxx.o.provides

CMakeFiles/tetgen.dir/predicates.cxx.o.provides.build: CMakeFiles/tetgen.dir/predicates.cxx.o

# Object files for target tetgen
tetgen_OBJECTS = \
"CMakeFiles/tetgen.dir/tetgen.cxx.o" \
"CMakeFiles/tetgen.dir/predicates.cxx.o"

# External object files for target tetgen
tetgen_EXTERNAL_OBJECTS =

tetgen: CMakeFiles/tetgen.dir/tetgen.cxx.o
tetgen: CMakeFiles/tetgen.dir/predicates.cxx.o
tetgen: CMakeFiles/tetgen.dir/build.make
tetgen: CMakeFiles/tetgen.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable tetgen"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tetgen.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tetgen.dir/build: tetgen
.PHONY : CMakeFiles/tetgen.dir/build

CMakeFiles/tetgen.dir/requires: CMakeFiles/tetgen.dir/tetgen.cxx.o.requires
CMakeFiles/tetgen.dir/requires: CMakeFiles/tetgen.dir/predicates.cxx.o.requires
.PHONY : CMakeFiles/tetgen.dir/requires

CMakeFiles/tetgen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tetgen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tetgen.dir/clean

CMakeFiles/tetgen.dir/depend:
	cd /home/dexternation/Downloads/tetgen1.5.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dexternation/Downloads/tetgen1.5.0 /home/dexternation/Downloads/tetgen1.5.0 /home/dexternation/Downloads/tetgen1.5.0/build /home/dexternation/Downloads/tetgen1.5.0/build /home/dexternation/Downloads/tetgen1.5.0/build/CMakeFiles/tetgen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tetgen.dir/depend

