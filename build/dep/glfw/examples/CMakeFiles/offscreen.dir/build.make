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
include dep/glfw/examples/CMakeFiles/offscreen.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include dep/glfw/examples/CMakeFiles/offscreen.dir/compiler_depend.make

# Include the progress variables for this target.
include dep/glfw/examples/CMakeFiles/offscreen.dir/progress.make

# Include the compile flags for this target's objects.
include dep/glfw/examples/CMakeFiles/offscreen.dir/flags.make

dep/glfw/examples/CMakeFiles/offscreen.dir/offscreen.c.obj: dep/glfw/examples/CMakeFiles/offscreen.dir/flags.make
dep/glfw/examples/CMakeFiles/offscreen.dir/offscreen.c.obj: dep/glfw/examples/CMakeFiles/offscreen.dir/includes_C.rsp
dep/glfw/examples/CMakeFiles/offscreen.dir/offscreen.c.obj: C:/pentago_OpenGL/dep/glfw/examples/offscreen.c
dep/glfw/examples/CMakeFiles/offscreen.dir/offscreen.c.obj: dep/glfw/examples/CMakeFiles/offscreen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\pentago_OpenGL\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object dep/glfw/examples/CMakeFiles/offscreen.dir/offscreen.c.obj"
	cd /d C:\pentago_OpenGL\build\dep\glfw\examples && C:\Qt\Tools\mingw1120_64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dep/glfw/examples/CMakeFiles/offscreen.dir/offscreen.c.obj -MF CMakeFiles\offscreen.dir\offscreen.c.obj.d -o CMakeFiles\offscreen.dir\offscreen.c.obj -c C:\pentago_OpenGL\dep\glfw\examples\offscreen.c

dep/glfw/examples/CMakeFiles/offscreen.dir/offscreen.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/offscreen.dir/offscreen.c.i"
	cd /d C:\pentago_OpenGL\build\dep\glfw\examples && C:\Qt\Tools\mingw1120_64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\pentago_OpenGL\dep\glfw\examples\offscreen.c > CMakeFiles\offscreen.dir\offscreen.c.i

dep/glfw/examples/CMakeFiles/offscreen.dir/offscreen.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/offscreen.dir/offscreen.c.s"
	cd /d C:\pentago_OpenGL\build\dep\glfw\examples && C:\Qt\Tools\mingw1120_64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\pentago_OpenGL\dep\glfw\examples\offscreen.c -o CMakeFiles\offscreen.dir\offscreen.c.s

dep/glfw/examples/CMakeFiles/offscreen.dir/glfw.rc.obj: dep/glfw/examples/CMakeFiles/offscreen.dir/flags.make
dep/glfw/examples/CMakeFiles/offscreen.dir/glfw.rc.obj: C:/pentago_OpenGL/dep/glfw/examples/glfw.rc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\pentago_OpenGL\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building RC object dep/glfw/examples/CMakeFiles/offscreen.dir/glfw.rc.obj"
	cd /d C:\pentago_OpenGL\build\dep\glfw\examples && C:\Qt\Tools\mingw1120_64\bin\windres.exe -O coff $(RC_DEFINES) $(RC_INCLUDES) $(RC_FLAGS) C:\pentago_OpenGL\dep\glfw\examples\glfw.rc CMakeFiles\offscreen.dir\glfw.rc.obj

dep/glfw/examples/CMakeFiles/offscreen.dir/__/deps/glad_gl.c.obj: dep/glfw/examples/CMakeFiles/offscreen.dir/flags.make
dep/glfw/examples/CMakeFiles/offscreen.dir/__/deps/glad_gl.c.obj: dep/glfw/examples/CMakeFiles/offscreen.dir/includes_C.rsp
dep/glfw/examples/CMakeFiles/offscreen.dir/__/deps/glad_gl.c.obj: C:/pentago_OpenGL/dep/glfw/deps/glad_gl.c
dep/glfw/examples/CMakeFiles/offscreen.dir/__/deps/glad_gl.c.obj: dep/glfw/examples/CMakeFiles/offscreen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\pentago_OpenGL\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object dep/glfw/examples/CMakeFiles/offscreen.dir/__/deps/glad_gl.c.obj"
	cd /d C:\pentago_OpenGL\build\dep\glfw\examples && C:\Qt\Tools\mingw1120_64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dep/glfw/examples/CMakeFiles/offscreen.dir/__/deps/glad_gl.c.obj -MF CMakeFiles\offscreen.dir\__\deps\glad_gl.c.obj.d -o CMakeFiles\offscreen.dir\__\deps\glad_gl.c.obj -c C:\pentago_OpenGL\dep\glfw\deps\glad_gl.c

dep/glfw/examples/CMakeFiles/offscreen.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/offscreen.dir/__/deps/glad_gl.c.i"
	cd /d C:\pentago_OpenGL\build\dep\glfw\examples && C:\Qt\Tools\mingw1120_64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\pentago_OpenGL\dep\glfw\deps\glad_gl.c > CMakeFiles\offscreen.dir\__\deps\glad_gl.c.i

dep/glfw/examples/CMakeFiles/offscreen.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/offscreen.dir/__/deps/glad_gl.c.s"
	cd /d C:\pentago_OpenGL\build\dep\glfw\examples && C:\Qt\Tools\mingw1120_64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\pentago_OpenGL\dep\glfw\deps\glad_gl.c -o CMakeFiles\offscreen.dir\__\deps\glad_gl.c.s

# Object files for target offscreen
offscreen_OBJECTS = \
"CMakeFiles/offscreen.dir/offscreen.c.obj" \
"CMakeFiles/offscreen.dir/glfw.rc.obj" \
"CMakeFiles/offscreen.dir/__/deps/glad_gl.c.obj"

# External object files for target offscreen
offscreen_EXTERNAL_OBJECTS =

dep/glfw/examples/offscreen.exe: dep/glfw/examples/CMakeFiles/offscreen.dir/offscreen.c.obj
dep/glfw/examples/offscreen.exe: dep/glfw/examples/CMakeFiles/offscreen.dir/glfw.rc.obj
dep/glfw/examples/offscreen.exe: dep/glfw/examples/CMakeFiles/offscreen.dir/__/deps/glad_gl.c.obj
dep/glfw/examples/offscreen.exe: dep/glfw/examples/CMakeFiles/offscreen.dir/build.make
dep/glfw/examples/offscreen.exe: dep/glfw/src/libglfw3.a
dep/glfw/examples/offscreen.exe: dep/glfw/examples/CMakeFiles/offscreen.dir/linklibs.rsp
dep/glfw/examples/offscreen.exe: dep/glfw/examples/CMakeFiles/offscreen.dir/objects1.rsp
dep/glfw/examples/offscreen.exe: dep/glfw/examples/CMakeFiles/offscreen.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\pentago_OpenGL\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable offscreen.exe"
	cd /d C:\pentago_OpenGL\build\dep\glfw\examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\offscreen.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
dep/glfw/examples/CMakeFiles/offscreen.dir/build: dep/glfw/examples/offscreen.exe
.PHONY : dep/glfw/examples/CMakeFiles/offscreen.dir/build

dep/glfw/examples/CMakeFiles/offscreen.dir/clean:
	cd /d C:\pentago_OpenGL\build\dep\glfw\examples && $(CMAKE_COMMAND) -P CMakeFiles\offscreen.dir\cmake_clean.cmake
.PHONY : dep/glfw/examples/CMakeFiles/offscreen.dir/clean

dep/glfw/examples/CMakeFiles/offscreen.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\pentago_OpenGL C:\pentago_OpenGL\dep\glfw\examples C:\pentago_OpenGL\build C:\pentago_OpenGL\build\dep\glfw\examples C:\pentago_OpenGL\build\dep\glfw\examples\CMakeFiles\offscreen.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : dep/glfw/examples/CMakeFiles/offscreen.dir/depend
