# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/user/docker-images/EE6470/midproject_tlm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/docker-images/EE6470/midproject_tlm/build

# Include any dependencies generated for this target.
include CMakeFiles/GaussianBlur.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/GaussianBlur.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GaussianBlur.dir/flags.make

CMakeFiles/GaussianBlur.dir/GaussianBlurFilter.cpp.o: CMakeFiles/GaussianBlur.dir/flags.make
CMakeFiles/GaussianBlur.dir/GaussianBlurFilter.cpp.o: ../GaussianBlurFilter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/docker-images/EE6470/midproject_tlm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/GaussianBlur.dir/GaussianBlurFilter.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GaussianBlur.dir/GaussianBlurFilter.cpp.o -c /home/user/docker-images/EE6470/midproject_tlm/GaussianBlurFilter.cpp

CMakeFiles/GaussianBlur.dir/GaussianBlurFilter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GaussianBlur.dir/GaussianBlurFilter.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/docker-images/EE6470/midproject_tlm/GaussianBlurFilter.cpp > CMakeFiles/GaussianBlur.dir/GaussianBlurFilter.cpp.i

CMakeFiles/GaussianBlur.dir/GaussianBlurFilter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GaussianBlur.dir/GaussianBlurFilter.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/docker-images/EE6470/midproject_tlm/GaussianBlurFilter.cpp -o CMakeFiles/GaussianBlur.dir/GaussianBlurFilter.cpp.s

CMakeFiles/GaussianBlur.dir/Initiator.cpp.o: CMakeFiles/GaussianBlur.dir/flags.make
CMakeFiles/GaussianBlur.dir/Initiator.cpp.o: ../Initiator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/docker-images/EE6470/midproject_tlm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/GaussianBlur.dir/Initiator.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GaussianBlur.dir/Initiator.cpp.o -c /home/user/docker-images/EE6470/midproject_tlm/Initiator.cpp

CMakeFiles/GaussianBlur.dir/Initiator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GaussianBlur.dir/Initiator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/docker-images/EE6470/midproject_tlm/Initiator.cpp > CMakeFiles/GaussianBlur.dir/Initiator.cpp.i

CMakeFiles/GaussianBlur.dir/Initiator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GaussianBlur.dir/Initiator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/docker-images/EE6470/midproject_tlm/Initiator.cpp -o CMakeFiles/GaussianBlur.dir/Initiator.cpp.s

CMakeFiles/GaussianBlur.dir/Testbench.cpp.o: CMakeFiles/GaussianBlur.dir/flags.make
CMakeFiles/GaussianBlur.dir/Testbench.cpp.o: ../Testbench.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/docker-images/EE6470/midproject_tlm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/GaussianBlur.dir/Testbench.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GaussianBlur.dir/Testbench.cpp.o -c /home/user/docker-images/EE6470/midproject_tlm/Testbench.cpp

CMakeFiles/GaussianBlur.dir/Testbench.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GaussianBlur.dir/Testbench.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/docker-images/EE6470/midproject_tlm/Testbench.cpp > CMakeFiles/GaussianBlur.dir/Testbench.cpp.i

CMakeFiles/GaussianBlur.dir/Testbench.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GaussianBlur.dir/Testbench.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/docker-images/EE6470/midproject_tlm/Testbench.cpp -o CMakeFiles/GaussianBlur.dir/Testbench.cpp.s

CMakeFiles/GaussianBlur.dir/main.cpp.o: CMakeFiles/GaussianBlur.dir/flags.make
CMakeFiles/GaussianBlur.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/docker-images/EE6470/midproject_tlm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/GaussianBlur.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GaussianBlur.dir/main.cpp.o -c /home/user/docker-images/EE6470/midproject_tlm/main.cpp

CMakeFiles/GaussianBlur.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GaussianBlur.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/docker-images/EE6470/midproject_tlm/main.cpp > CMakeFiles/GaussianBlur.dir/main.cpp.i

CMakeFiles/GaussianBlur.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GaussianBlur.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/docker-images/EE6470/midproject_tlm/main.cpp -o CMakeFiles/GaussianBlur.dir/main.cpp.s

CMakeFiles/GaussianBlur.dir/tlm_log.cpp.o: CMakeFiles/GaussianBlur.dir/flags.make
CMakeFiles/GaussianBlur.dir/tlm_log.cpp.o: ../tlm_log.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/docker-images/EE6470/midproject_tlm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/GaussianBlur.dir/tlm_log.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GaussianBlur.dir/tlm_log.cpp.o -c /home/user/docker-images/EE6470/midproject_tlm/tlm_log.cpp

CMakeFiles/GaussianBlur.dir/tlm_log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GaussianBlur.dir/tlm_log.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/docker-images/EE6470/midproject_tlm/tlm_log.cpp > CMakeFiles/GaussianBlur.dir/tlm_log.cpp.i

CMakeFiles/GaussianBlur.dir/tlm_log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GaussianBlur.dir/tlm_log.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/docker-images/EE6470/midproject_tlm/tlm_log.cpp -o CMakeFiles/GaussianBlur.dir/tlm_log.cpp.s

# Object files for target GaussianBlur
GaussianBlur_OBJECTS = \
"CMakeFiles/GaussianBlur.dir/GaussianBlurFilter.cpp.o" \
"CMakeFiles/GaussianBlur.dir/Initiator.cpp.o" \
"CMakeFiles/GaussianBlur.dir/Testbench.cpp.o" \
"CMakeFiles/GaussianBlur.dir/main.cpp.o" \
"CMakeFiles/GaussianBlur.dir/tlm_log.cpp.o"

# External object files for target GaussianBlur
GaussianBlur_EXTERNAL_OBJECTS =

GaussianBlur: CMakeFiles/GaussianBlur.dir/GaussianBlurFilter.cpp.o
GaussianBlur: CMakeFiles/GaussianBlur.dir/Initiator.cpp.o
GaussianBlur: CMakeFiles/GaussianBlur.dir/Testbench.cpp.o
GaussianBlur: CMakeFiles/GaussianBlur.dir/main.cpp.o
GaussianBlur: CMakeFiles/GaussianBlur.dir/tlm_log.cpp.o
GaussianBlur: CMakeFiles/GaussianBlur.dir/build.make
GaussianBlur: /opt/systemc/lib/libsystemc.so.2.3.3
GaussianBlur: CMakeFiles/GaussianBlur.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/user/docker-images/EE6470/midproject_tlm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable GaussianBlur"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GaussianBlur.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GaussianBlur.dir/build: GaussianBlur

.PHONY : CMakeFiles/GaussianBlur.dir/build

CMakeFiles/GaussianBlur.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/GaussianBlur.dir/cmake_clean.cmake
.PHONY : CMakeFiles/GaussianBlur.dir/clean

CMakeFiles/GaussianBlur.dir/depend:
	cd /home/user/docker-images/EE6470/midproject_tlm/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/docker-images/EE6470/midproject_tlm /home/user/docker-images/EE6470/midproject_tlm /home/user/docker-images/EE6470/midproject_tlm/build /home/user/docker-images/EE6470/midproject_tlm/build /home/user/docker-images/EE6470/midproject_tlm/build/CMakeFiles/GaussianBlur.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/GaussianBlur.dir/depend

