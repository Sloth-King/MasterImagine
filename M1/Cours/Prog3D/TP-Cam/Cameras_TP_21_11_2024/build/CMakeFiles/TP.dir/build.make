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
CMAKE_SOURCE_DIR = /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/build

# Include any dependencies generated for this target.
include CMakeFiles/TP.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/TP.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/TP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TP.dir/flags.make

CMakeFiles/TP.dir/TP/TP.cpp.o: CMakeFiles/TP.dir/flags.make
CMakeFiles/TP.dir/TP/TP.cpp.o: ../TP/TP.cpp
CMakeFiles/TP.dir/TP/TP.cpp.o: CMakeFiles/TP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TP.dir/TP/TP.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TP.dir/TP/TP.cpp.o -MF CMakeFiles/TP.dir/TP/TP.cpp.o.d -o CMakeFiles/TP.dir/TP/TP.cpp.o -c /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/TP/TP.cpp

CMakeFiles/TP.dir/TP/TP.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP.dir/TP/TP.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/TP/TP.cpp > CMakeFiles/TP.dir/TP/TP.cpp.i

CMakeFiles/TP.dir/TP/TP.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP.dir/TP/TP.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/TP/TP.cpp -o CMakeFiles/TP.dir/TP/TP.cpp.s

CMakeFiles/TP.dir/common/shader.cpp.o: CMakeFiles/TP.dir/flags.make
CMakeFiles/TP.dir/common/shader.cpp.o: ../common/shader.cpp
CMakeFiles/TP.dir/common/shader.cpp.o: CMakeFiles/TP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TP.dir/common/shader.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TP.dir/common/shader.cpp.o -MF CMakeFiles/TP.dir/common/shader.cpp.o.d -o CMakeFiles/TP.dir/common/shader.cpp.o -c /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/common/shader.cpp

CMakeFiles/TP.dir/common/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP.dir/common/shader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/common/shader.cpp > CMakeFiles/TP.dir/common/shader.cpp.i

CMakeFiles/TP.dir/common/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP.dir/common/shader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/common/shader.cpp -o CMakeFiles/TP.dir/common/shader.cpp.s

CMakeFiles/TP.dir/common/controls.cpp.o: CMakeFiles/TP.dir/flags.make
CMakeFiles/TP.dir/common/controls.cpp.o: ../common/controls.cpp
CMakeFiles/TP.dir/common/controls.cpp.o: CMakeFiles/TP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/TP.dir/common/controls.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TP.dir/common/controls.cpp.o -MF CMakeFiles/TP.dir/common/controls.cpp.o.d -o CMakeFiles/TP.dir/common/controls.cpp.o -c /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/common/controls.cpp

CMakeFiles/TP.dir/common/controls.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP.dir/common/controls.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/common/controls.cpp > CMakeFiles/TP.dir/common/controls.cpp.i

CMakeFiles/TP.dir/common/controls.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP.dir/common/controls.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/common/controls.cpp -o CMakeFiles/TP.dir/common/controls.cpp.s

CMakeFiles/TP.dir/common/texture.cpp.o: CMakeFiles/TP.dir/flags.make
CMakeFiles/TP.dir/common/texture.cpp.o: ../common/texture.cpp
CMakeFiles/TP.dir/common/texture.cpp.o: CMakeFiles/TP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/TP.dir/common/texture.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TP.dir/common/texture.cpp.o -MF CMakeFiles/TP.dir/common/texture.cpp.o.d -o CMakeFiles/TP.dir/common/texture.cpp.o -c /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/common/texture.cpp

CMakeFiles/TP.dir/common/texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP.dir/common/texture.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/common/texture.cpp > CMakeFiles/TP.dir/common/texture.cpp.i

CMakeFiles/TP.dir/common/texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP.dir/common/texture.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/common/texture.cpp -o CMakeFiles/TP.dir/common/texture.cpp.s

CMakeFiles/TP.dir/common/objloader.cpp.o: CMakeFiles/TP.dir/flags.make
CMakeFiles/TP.dir/common/objloader.cpp.o: ../common/objloader.cpp
CMakeFiles/TP.dir/common/objloader.cpp.o: CMakeFiles/TP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/TP.dir/common/objloader.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TP.dir/common/objloader.cpp.o -MF CMakeFiles/TP.dir/common/objloader.cpp.o.d -o CMakeFiles/TP.dir/common/objloader.cpp.o -c /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/common/objloader.cpp

CMakeFiles/TP.dir/common/objloader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP.dir/common/objloader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/common/objloader.cpp > CMakeFiles/TP.dir/common/objloader.cpp.i

CMakeFiles/TP.dir/common/objloader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP.dir/common/objloader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/common/objloader.cpp -o CMakeFiles/TP.dir/common/objloader.cpp.s

CMakeFiles/TP.dir/common/vboindexer.cpp.o: CMakeFiles/TP.dir/flags.make
CMakeFiles/TP.dir/common/vboindexer.cpp.o: ../common/vboindexer.cpp
CMakeFiles/TP.dir/common/vboindexer.cpp.o: CMakeFiles/TP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/TP.dir/common/vboindexer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TP.dir/common/vboindexer.cpp.o -MF CMakeFiles/TP.dir/common/vboindexer.cpp.o.d -o CMakeFiles/TP.dir/common/vboindexer.cpp.o -c /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/common/vboindexer.cpp

CMakeFiles/TP.dir/common/vboindexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP.dir/common/vboindexer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/common/vboindexer.cpp > CMakeFiles/TP.dir/common/vboindexer.cpp.i

CMakeFiles/TP.dir/common/vboindexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP.dir/common/vboindexer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/common/vboindexer.cpp -o CMakeFiles/TP.dir/common/vboindexer.cpp.s

CMakeFiles/TP.dir/common/quaternion_utils.cpp.o: CMakeFiles/TP.dir/flags.make
CMakeFiles/TP.dir/common/quaternion_utils.cpp.o: ../common/quaternion_utils.cpp
CMakeFiles/TP.dir/common/quaternion_utils.cpp.o: CMakeFiles/TP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/TP.dir/common/quaternion_utils.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TP.dir/common/quaternion_utils.cpp.o -MF CMakeFiles/TP.dir/common/quaternion_utils.cpp.o.d -o CMakeFiles/TP.dir/common/quaternion_utils.cpp.o -c /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/common/quaternion_utils.cpp

CMakeFiles/TP.dir/common/quaternion_utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP.dir/common/quaternion_utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/common/quaternion_utils.cpp > CMakeFiles/TP.dir/common/quaternion_utils.cpp.i

CMakeFiles/TP.dir/common/quaternion_utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP.dir/common/quaternion_utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/common/quaternion_utils.cpp -o CMakeFiles/TP.dir/common/quaternion_utils.cpp.s

CMakeFiles/TP.dir/TP/Actor/Actor.cpp.o: CMakeFiles/TP.dir/flags.make
CMakeFiles/TP.dir/TP/Actor/Actor.cpp.o: ../TP/Actor/Actor.cpp
CMakeFiles/TP.dir/TP/Actor/Actor.cpp.o: CMakeFiles/TP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/TP.dir/TP/Actor/Actor.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TP.dir/TP/Actor/Actor.cpp.o -MF CMakeFiles/TP.dir/TP/Actor/Actor.cpp.o.d -o CMakeFiles/TP.dir/TP/Actor/Actor.cpp.o -c /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/TP/Actor/Actor.cpp

CMakeFiles/TP.dir/TP/Actor/Actor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP.dir/TP/Actor/Actor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/TP/Actor/Actor.cpp > CMakeFiles/TP.dir/TP/Actor/Actor.cpp.i

CMakeFiles/TP.dir/TP/Actor/Actor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP.dir/TP/Actor/Actor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/TP/Actor/Actor.cpp -o CMakeFiles/TP.dir/TP/Actor/Actor.cpp.s

CMakeFiles/TP.dir/TP/Camera/Camera.cpp.o: CMakeFiles/TP.dir/flags.make
CMakeFiles/TP.dir/TP/Camera/Camera.cpp.o: ../TP/Camera/Camera.cpp
CMakeFiles/TP.dir/TP/Camera/Camera.cpp.o: CMakeFiles/TP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/TP.dir/TP/Camera/Camera.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TP.dir/TP/Camera/Camera.cpp.o -MF CMakeFiles/TP.dir/TP/Camera/Camera.cpp.o.d -o CMakeFiles/TP.dir/TP/Camera/Camera.cpp.o -c /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/TP/Camera/Camera.cpp

CMakeFiles/TP.dir/TP/Camera/Camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP.dir/TP/Camera/Camera.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/TP/Camera/Camera.cpp > CMakeFiles/TP.dir/TP/Camera/Camera.cpp.i

CMakeFiles/TP.dir/TP/Camera/Camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP.dir/TP/Camera/Camera.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/TP/Camera/Camera.cpp -o CMakeFiles/TP.dir/TP/Camera/Camera.cpp.s

CMakeFiles/TP.dir/TP/Camera/Camera_Helper.cpp.o: CMakeFiles/TP.dir/flags.make
CMakeFiles/TP.dir/TP/Camera/Camera_Helper.cpp.o: ../TP/Camera/Camera_Helper.cpp
CMakeFiles/TP.dir/TP/Camera/Camera_Helper.cpp.o: CMakeFiles/TP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/TP.dir/TP/Camera/Camera_Helper.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TP.dir/TP/Camera/Camera_Helper.cpp.o -MF CMakeFiles/TP.dir/TP/Camera/Camera_Helper.cpp.o.d -o CMakeFiles/TP.dir/TP/Camera/Camera_Helper.cpp.o -c /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/TP/Camera/Camera_Helper.cpp

CMakeFiles/TP.dir/TP/Camera/Camera_Helper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP.dir/TP/Camera/Camera_Helper.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/TP/Camera/Camera_Helper.cpp > CMakeFiles/TP.dir/TP/Camera/Camera_Helper.cpp.i

CMakeFiles/TP.dir/TP/Camera/Camera_Helper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP.dir/TP/Camera/Camera_Helper.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/TP/Camera/Camera_Helper.cpp -o CMakeFiles/TP.dir/TP/Camera/Camera_Helper.cpp.s

CMakeFiles/TP.dir/TP/Actor/ObjController.cpp.o: CMakeFiles/TP.dir/flags.make
CMakeFiles/TP.dir/TP/Actor/ObjController.cpp.o: ../TP/Actor/ObjController.cpp
CMakeFiles/TP.dir/TP/Actor/ObjController.cpp.o: CMakeFiles/TP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/TP.dir/TP/Actor/ObjController.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TP.dir/TP/Actor/ObjController.cpp.o -MF CMakeFiles/TP.dir/TP/Actor/ObjController.cpp.o.d -o CMakeFiles/TP.dir/TP/Actor/ObjController.cpp.o -c /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/TP/Actor/ObjController.cpp

CMakeFiles/TP.dir/TP/Actor/ObjController.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP.dir/TP/Actor/ObjController.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/TP/Actor/ObjController.cpp > CMakeFiles/TP.dir/TP/Actor/ObjController.cpp.i

CMakeFiles/TP.dir/TP/Actor/ObjController.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP.dir/TP/Actor/ObjController.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/TP/Actor/ObjController.cpp -o CMakeFiles/TP.dir/TP/Actor/ObjController.cpp.s

CMakeFiles/TP.dir/imgui/imgui.cpp.o: CMakeFiles/TP.dir/flags.make
CMakeFiles/TP.dir/imgui/imgui.cpp.o: ../imgui/imgui.cpp
CMakeFiles/TP.dir/imgui/imgui.cpp.o: CMakeFiles/TP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/TP.dir/imgui/imgui.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TP.dir/imgui/imgui.cpp.o -MF CMakeFiles/TP.dir/imgui/imgui.cpp.o.d -o CMakeFiles/TP.dir/imgui/imgui.cpp.o -c /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/imgui/imgui.cpp

CMakeFiles/TP.dir/imgui/imgui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP.dir/imgui/imgui.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/imgui/imgui.cpp > CMakeFiles/TP.dir/imgui/imgui.cpp.i

CMakeFiles/TP.dir/imgui/imgui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP.dir/imgui/imgui.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/imgui/imgui.cpp -o CMakeFiles/TP.dir/imgui/imgui.cpp.s

CMakeFiles/TP.dir/imgui/imgui_demo.cpp.o: CMakeFiles/TP.dir/flags.make
CMakeFiles/TP.dir/imgui/imgui_demo.cpp.o: ../imgui/imgui_demo.cpp
CMakeFiles/TP.dir/imgui/imgui_demo.cpp.o: CMakeFiles/TP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/TP.dir/imgui/imgui_demo.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TP.dir/imgui/imgui_demo.cpp.o -MF CMakeFiles/TP.dir/imgui/imgui_demo.cpp.o.d -o CMakeFiles/TP.dir/imgui/imgui_demo.cpp.o -c /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/imgui/imgui_demo.cpp

CMakeFiles/TP.dir/imgui/imgui_demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP.dir/imgui/imgui_demo.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/imgui/imgui_demo.cpp > CMakeFiles/TP.dir/imgui/imgui_demo.cpp.i

CMakeFiles/TP.dir/imgui/imgui_demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP.dir/imgui/imgui_demo.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/imgui/imgui_demo.cpp -o CMakeFiles/TP.dir/imgui/imgui_demo.cpp.s

CMakeFiles/TP.dir/imgui/imgui_draw.cpp.o: CMakeFiles/TP.dir/flags.make
CMakeFiles/TP.dir/imgui/imgui_draw.cpp.o: ../imgui/imgui_draw.cpp
CMakeFiles/TP.dir/imgui/imgui_draw.cpp.o: CMakeFiles/TP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/TP.dir/imgui/imgui_draw.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TP.dir/imgui/imgui_draw.cpp.o -MF CMakeFiles/TP.dir/imgui/imgui_draw.cpp.o.d -o CMakeFiles/TP.dir/imgui/imgui_draw.cpp.o -c /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/imgui/imgui_draw.cpp

CMakeFiles/TP.dir/imgui/imgui_draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP.dir/imgui/imgui_draw.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/imgui/imgui_draw.cpp > CMakeFiles/TP.dir/imgui/imgui_draw.cpp.i

CMakeFiles/TP.dir/imgui/imgui_draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP.dir/imgui/imgui_draw.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/imgui/imgui_draw.cpp -o CMakeFiles/TP.dir/imgui/imgui_draw.cpp.s

CMakeFiles/TP.dir/imgui/imgui_impl_glfw.cpp.o: CMakeFiles/TP.dir/flags.make
CMakeFiles/TP.dir/imgui/imgui_impl_glfw.cpp.o: ../imgui/imgui_impl_glfw.cpp
CMakeFiles/TP.dir/imgui/imgui_impl_glfw.cpp.o: CMakeFiles/TP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/TP.dir/imgui/imgui_impl_glfw.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TP.dir/imgui/imgui_impl_glfw.cpp.o -MF CMakeFiles/TP.dir/imgui/imgui_impl_glfw.cpp.o.d -o CMakeFiles/TP.dir/imgui/imgui_impl_glfw.cpp.o -c /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/imgui/imgui_impl_glfw.cpp

CMakeFiles/TP.dir/imgui/imgui_impl_glfw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP.dir/imgui/imgui_impl_glfw.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/imgui/imgui_impl_glfw.cpp > CMakeFiles/TP.dir/imgui/imgui_impl_glfw.cpp.i

CMakeFiles/TP.dir/imgui/imgui_impl_glfw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP.dir/imgui/imgui_impl_glfw.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/imgui/imgui_impl_glfw.cpp -o CMakeFiles/TP.dir/imgui/imgui_impl_glfw.cpp.s

CMakeFiles/TP.dir/imgui/imgui_impl_opengl3.cpp.o: CMakeFiles/TP.dir/flags.make
CMakeFiles/TP.dir/imgui/imgui_impl_opengl3.cpp.o: ../imgui/imgui_impl_opengl3.cpp
CMakeFiles/TP.dir/imgui/imgui_impl_opengl3.cpp.o: CMakeFiles/TP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/TP.dir/imgui/imgui_impl_opengl3.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TP.dir/imgui/imgui_impl_opengl3.cpp.o -MF CMakeFiles/TP.dir/imgui/imgui_impl_opengl3.cpp.o.d -o CMakeFiles/TP.dir/imgui/imgui_impl_opengl3.cpp.o -c /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/imgui/imgui_impl_opengl3.cpp

CMakeFiles/TP.dir/imgui/imgui_impl_opengl3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP.dir/imgui/imgui_impl_opengl3.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/imgui/imgui_impl_opengl3.cpp > CMakeFiles/TP.dir/imgui/imgui_impl_opengl3.cpp.i

CMakeFiles/TP.dir/imgui/imgui_impl_opengl3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP.dir/imgui/imgui_impl_opengl3.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/imgui/imgui_impl_opengl3.cpp -o CMakeFiles/TP.dir/imgui/imgui_impl_opengl3.cpp.s

CMakeFiles/TP.dir/imgui/imgui_tables.cpp.o: CMakeFiles/TP.dir/flags.make
CMakeFiles/TP.dir/imgui/imgui_tables.cpp.o: ../imgui/imgui_tables.cpp
CMakeFiles/TP.dir/imgui/imgui_tables.cpp.o: CMakeFiles/TP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object CMakeFiles/TP.dir/imgui/imgui_tables.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TP.dir/imgui/imgui_tables.cpp.o -MF CMakeFiles/TP.dir/imgui/imgui_tables.cpp.o.d -o CMakeFiles/TP.dir/imgui/imgui_tables.cpp.o -c /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/imgui/imgui_tables.cpp

CMakeFiles/TP.dir/imgui/imgui_tables.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP.dir/imgui/imgui_tables.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/imgui/imgui_tables.cpp > CMakeFiles/TP.dir/imgui/imgui_tables.cpp.i

CMakeFiles/TP.dir/imgui/imgui_tables.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP.dir/imgui/imgui_tables.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/imgui/imgui_tables.cpp -o CMakeFiles/TP.dir/imgui/imgui_tables.cpp.s

CMakeFiles/TP.dir/imgui/imgui_widgets.cpp.o: CMakeFiles/TP.dir/flags.make
CMakeFiles/TP.dir/imgui/imgui_widgets.cpp.o: ../imgui/imgui_widgets.cpp
CMakeFiles/TP.dir/imgui/imgui_widgets.cpp.o: CMakeFiles/TP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Building CXX object CMakeFiles/TP.dir/imgui/imgui_widgets.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TP.dir/imgui/imgui_widgets.cpp.o -MF CMakeFiles/TP.dir/imgui/imgui_widgets.cpp.o.d -o CMakeFiles/TP.dir/imgui/imgui_widgets.cpp.o -c /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/imgui/imgui_widgets.cpp

CMakeFiles/TP.dir/imgui/imgui_widgets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP.dir/imgui/imgui_widgets.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/imgui/imgui_widgets.cpp > CMakeFiles/TP.dir/imgui/imgui_widgets.cpp.i

CMakeFiles/TP.dir/imgui/imgui_widgets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP.dir/imgui/imgui_widgets.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/imgui/imgui_widgets.cpp -o CMakeFiles/TP.dir/imgui/imgui_widgets.cpp.s

# Object files for target TP
TP_OBJECTS = \
"CMakeFiles/TP.dir/TP/TP.cpp.o" \
"CMakeFiles/TP.dir/common/shader.cpp.o" \
"CMakeFiles/TP.dir/common/controls.cpp.o" \
"CMakeFiles/TP.dir/common/texture.cpp.o" \
"CMakeFiles/TP.dir/common/objloader.cpp.o" \
"CMakeFiles/TP.dir/common/vboindexer.cpp.o" \
"CMakeFiles/TP.dir/common/quaternion_utils.cpp.o" \
"CMakeFiles/TP.dir/TP/Actor/Actor.cpp.o" \
"CMakeFiles/TP.dir/TP/Camera/Camera.cpp.o" \
"CMakeFiles/TP.dir/TP/Camera/Camera_Helper.cpp.o" \
"CMakeFiles/TP.dir/TP/Actor/ObjController.cpp.o" \
"CMakeFiles/TP.dir/imgui/imgui.cpp.o" \
"CMakeFiles/TP.dir/imgui/imgui_demo.cpp.o" \
"CMakeFiles/TP.dir/imgui/imgui_draw.cpp.o" \
"CMakeFiles/TP.dir/imgui/imgui_impl_glfw.cpp.o" \
"CMakeFiles/TP.dir/imgui/imgui_impl_opengl3.cpp.o" \
"CMakeFiles/TP.dir/imgui/imgui_tables.cpp.o" \
"CMakeFiles/TP.dir/imgui/imgui_widgets.cpp.o"

# External object files for target TP
TP_EXTERNAL_OBJECTS =

TP: CMakeFiles/TP.dir/TP/TP.cpp.o
TP: CMakeFiles/TP.dir/common/shader.cpp.o
TP: CMakeFiles/TP.dir/common/controls.cpp.o
TP: CMakeFiles/TP.dir/common/texture.cpp.o
TP: CMakeFiles/TP.dir/common/objloader.cpp.o
TP: CMakeFiles/TP.dir/common/vboindexer.cpp.o
TP: CMakeFiles/TP.dir/common/quaternion_utils.cpp.o
TP: CMakeFiles/TP.dir/TP/Actor/Actor.cpp.o
TP: CMakeFiles/TP.dir/TP/Camera/Camera.cpp.o
TP: CMakeFiles/TP.dir/TP/Camera/Camera_Helper.cpp.o
TP: CMakeFiles/TP.dir/TP/Actor/ObjController.cpp.o
TP: CMakeFiles/TP.dir/imgui/imgui.cpp.o
TP: CMakeFiles/TP.dir/imgui/imgui_demo.cpp.o
TP: CMakeFiles/TP.dir/imgui/imgui_draw.cpp.o
TP: CMakeFiles/TP.dir/imgui/imgui_impl_glfw.cpp.o
TP: CMakeFiles/TP.dir/imgui/imgui_impl_opengl3.cpp.o
TP: CMakeFiles/TP.dir/imgui/imgui_tables.cpp.o
TP: CMakeFiles/TP.dir/imgui/imgui_widgets.cpp.o
TP: CMakeFiles/TP.dir/build.make
TP: /usr/lib/x86_64-linux-gnu/libGL.so
TP: /usr/lib/x86_64-linux-gnu/libGLU.so
TP: external/glfw-3.1.2/src/libglfw3.a
TP: external/libGLEW_1130.a
TP: /usr/lib/x86_64-linux-gnu/librt.a
TP: /usr/lib/x86_64-linux-gnu/libm.so
TP: /usr/lib/x86_64-linux-gnu/libX11.so
TP: /usr/lib/x86_64-linux-gnu/libXrandr.so
TP: /usr/lib/x86_64-linux-gnu/libXinerama.so
TP: /usr/lib/x86_64-linux-gnu/libXi.so
TP: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
TP: /usr/lib/x86_64-linux-gnu/libXcursor.so
TP: /usr/lib/x86_64-linux-gnu/librt.a
TP: /usr/lib/x86_64-linux-gnu/libm.so
TP: /usr/lib/x86_64-linux-gnu/libX11.so
TP: /usr/lib/x86_64-linux-gnu/libXrandr.so
TP: /usr/lib/x86_64-linux-gnu/libXinerama.so
TP: /usr/lib/x86_64-linux-gnu/libXi.so
TP: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
TP: /usr/lib/x86_64-linux-gnu/libXcursor.so
TP: /usr/lib/x86_64-linux-gnu/libGL.so
TP: /usr/lib/x86_64-linux-gnu/libGLU.so
TP: CMakeFiles/TP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_19) "Linking CXX executable TP"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TP.dir/link.txt --verbose=$(VERBOSE)
	/usr/bin/cmake -E copy /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/build/./TP /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/TP/

# Rule to build all files generated by this target.
CMakeFiles/TP.dir/build: TP
.PHONY : CMakeFiles/TP.dir/build

CMakeFiles/TP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TP.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TP.dir/clean

CMakeFiles/TP.dir/depend:
	cd /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024 /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024 /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/build /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/build /home/andrew/Bureau/MasterInfo/M1/Cours/Prog3D/TP-Cam/Cameras_TP_21_11_2024/build/CMakeFiles/TP.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TP.dir/depend

