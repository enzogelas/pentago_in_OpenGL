# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.24

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Qt\Tools\CMake_64\bin\cmake.exe

# The command to remove a file.
RM = C:\Qt\Tools\CMake_64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\pentago_OpenGL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\pentago_OpenGL\build

# Include any dependencies generated for this target.
include dep/glfw/tests/CMakeFiles/inputlag.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include dep/glfw/tests/CMakeFiles/inputlag.dir/compiler_depend.make

# Include the progress variables for this target.
include dep/glfw/tests/CMakeFiles/inputlag.dir/progress.make

# Include the compile flags for this target's objects.
include dep/glfw/tests/CMakeFiles/inputlag.dir/flags.make

dep/glfw/tests/CMakeFiles/inputlag.dir/inputlag.c.obj: dep/glfw/tests/CMakeFiles/inputlag.dir/flags.make
dep/glfw/tests/CMakeFiles/inputlag.dir/inputlag.c.obj: dep/glfw/tests/CMakeFiles/inputlag.dir/includes_C.rsp
dep/glfw/tests/CMakeFiles/inputlag.dir/inputlag.c.obj: C:/pentago_OpenGL/dep/glfw/tests/inputlag.c
dep/glfw/tests/CMakeFiles/inputlag.dir/inputlag.c.obj: dep/glfw/tests/CMakeFiles/inputlag.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\pentago_OpenGL\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object dep/glfw/tests/CMakeFiles/inputlag.dir/inputlag.c.obj"
	cd /d C:\pentago_OpenGL\build\dep\glfw\tests && C:\Qt\Tools\mingw1120_64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dep/glfw/tests/CMakeFiles/inputlag.dir/inputlag.c.obj -MF CMakeFiles\inputlag.dir\inputlag.c.obj.d -o CMakeFiles\inputlag.dir\inputlag.c.obj -c C:\pentago_OpenGL\dep\glfw\tests\inputlag.c

dep/glfw/tests/CMakeFiles/inputlag.dir/inputlag.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/inputlag.dir/inputlag.c.i"
	cd /d C:\pentago_OpenGL\build\dep\glfw\tests && C:\Qt\Tools\mingw1120_64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\pentago_OpenGL\dep\glfw\tests\inputlag.c > CMakeFiles\inputlag.dir\inputlag.c.i

dep/glfw/tests/CMakeFiles/inputlag.dir/inputlag.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/inputlag.dir/inputlag.c.s"
	cd /d C:\pentago_OpenGL\build\dep\glfw\tests && C:\Qt\Tools\mingw1120_64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\pentago_OpenGL\dep\glfw\tests\inputlag.c -o CMakeFiles\inputlag.dir\inputlag.c.s

dep/glfw/tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.obj: dep/glfw/tests/CMakeFiles/inputlag.dir/flags.make
dep/glfw/tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.obj: dep/glfw/tests/CMakeFiles/inputlag.dir/includes_C.rsp
dep/glfw/tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.obj: C:/pentago_OpenGL/dep/glfw/deps/getopt.c
dep/glfw/tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.obj: dep/glfw/tests/CMakeFiles/inputlag.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\pentago_OpenGL\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object dep/glfw/tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.obj"
	cd /d C:\pentago_OpenGL\build\dep\glfw\tests && C:\Qt\Tools\mingw1120_64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dep/glfw/tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.obj -MF CMakeFiles\inputlag.dir\__\deps\getopt.c.obj.d -o CMakeFiles\inputlag.dir\__\deps\getopt.c.obj -c C:\pentago_OpenGL\dep\glfw\deps\getopt.c

dep/glfw/tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/inputlag.dir/__/deps/getopt.c.i"
	cd /d C:\pentago_OpenGL\build\dep\glfw\tests && C:\Qt\Tools\mingw1120_64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\pentago_OpenGL\dep\glfw\deps\getopt.c > CMakeFiles\inputlag.dir\__\deps\getopt.c.i

dep/glfw/tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/inputlag.dir/__/deps/getopt.c.s"
	cd /d C:\pentago_OpenGL\build\dep\glfw\tests && C:\Qt\Tools\mingw1120_64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\pentago_OpenGL\dep\glfw\deps\getopt.c -o CMakeFiles\inputlag.dir\__\deps\getopt.c.s

dep/glfw/tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.obj: dep/glfw/tests/CMakeFiles/inputlag.dir/flags.make
dep/glfw/tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.obj: dep/glfw/tests/CMakeFiles/inputlag.dir/includes_C.rsp
dep/glfw/tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.obj: C:/pentago_OpenGL/dep/glfw/deps/glad_gl.c
dep/glfw/tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.obj: dep/glfw/tests/CMakeFiles/inputlag.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\pentago_OpenGL\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object dep/glfw/tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.obj"
	cd /d C:\pentago_OpenGL\build\dep\glfw\tests && C:\Qt\Tools\mingw1120_64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dep/glfw/tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.obj -MF CMakeFiles\inputlag.dir\__\deps\glad_gl.c.obj.d -o CMakeFiles\inputlag.dir\__\deps\glad_gl.c.obj -c C:\pentago_OpenGL\dep\glfw\deps\glad_gl.c

dep/glfw/tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/inputlag.dir/__/deps/glad_gl.c.i"
	cd /d C:\pentago_OpenGL\build\dep\glfw\tests && C:\Qt\Tools\mingw1120_64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\pentago_OpenGL\dep\glfw\deps\glad_gl.c > CMakeFiles\inputlag.dir\__\deps\glad_gl.c.i

dep/glfw/tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/inputlag.dir/__/deps/glad_gl.c.s"
	cd /d C:\pentago_OpenGL\build\dep\glfw\tests && C:\Qt\Tools\mingw1120_64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\pentago_OpenGL\dep\glfw\deps\glad_gl.c -o CMakeFiles\inputlag.dir\__\deps\glad_gl.c.s

# Object files for target inputlag
inputlag_OBJECTS = \
"CMakeFiles/inputlag.dir/inputlag.c.obj" \
"CMakeFiles/inputlag.dir/__/deps/getopt.c.obj" \
"CMakeFiles/inputlag.dir/__/deps/glad_gl.c.obj"

# External object files for target inputlag
inputlag_EXTERNAL_OBJECTS =

dep/glfw/tests/inputlag.exe: dep/glfw/tests/CMakeFiles/inputlag.dir/inputlag.c.obj
dep/glfw/tests/inputlag.exe: dep/glfw/tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.obj
dep/glfw/tests/inputlag.exe: dep/glfw/tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.obj
dep/glfw/tests/inputlag.exe: dep/glfw/tests/CMakeFiles/inputlag.dir/build.make
dep/glfw/tests/inputlag.exe: dep/glfw/src/libglfw3.a
dep/glfw/tests/inputlag.exe: dep/glfw/tests/CMakeFiles/inputlag.dir/linklibs.rsp
dep/glfw/tests/inputlag.exe: dep/glfw/tests/CMakeFiles/inputlag.dir/objects1.rsp
dep/glfw/tests/inputlag.exe: dep/glfw/tests/CMakeFiles/inputlag.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\pentago_OpenGL\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable inputlag.exe"
	cd /d C:\pentago_OpenGL\build\dep\glfw\tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\inputlag.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
dep/glfw/tests/CMakeFiles/inputlag.dir/build: dep/glfw/tests/inputlag.exe
.PHONY : dep/glfw/tests/CMakeFiles/inputlag.dir/build

dep/glfw/tests/CMakeFiles/inputlag.dir/clean:
	cd /d C:\pentago_OpenGL\build\dep\glfw\tests && $(CMAKE_COMMAND) -P CMakeFiles\inputlag.dir\cmake_clean.cmake
.PHONY : dep/glfw/tests/CMakeFiles/inputlag.dir/clean

dep/glfw/tests/CMakeFiles/inputlag.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\pentago_OpenGL C:\pentago_OpenGL\dep\glfw\tests C:\pentago_OpenGL\build C:\pentago_OpenGL\build\dep\glfw\tests C:\pentago_OpenGL\build\dep\glfw\tests\CMakeFiles\inputlag.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : dep/glfw/tests/CMakeFiles/inputlag.dir/depend

