# toolchain-i686-elf.cmake

# Specify the target system name (Linux, Windows, ...)
set(CMAKE_SYSTEM_NAME Generic)

# Specify the target processor architecture
set(TARGET_ARCH i686-elf)
set(CMAKE_SYSTEM_PROCESSOR i686)

# Specify the path to the target environment's root directory (sysroot).
# This should be adjusted to where your cross-compiler's sysroot is located.
# If your cross-compiler doesn't use a sysroot, you might not need this.


set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Specify the cross-compiler locations.
# Adjust these paths to where your cross-compiler binaries are located.
find_program(CMAKE_ASM_ATT_COMPILER NAMES i686-elf-as as)
find_program(CMAKE_C_COMPILER NAMES i686-elf-gcc gcc)
find_program(CMAKE_CXX_COMPILER NAMES i686-elf-g++ g++)

# Where to look for the target environment's executables
# set(CMAKE_FIND_ROOT_PATH /path/to/i686-elf)

# Adjust the default behaviour of the FIND_XXX() commands:
# We want to find libraries and programs in the host and target environment.
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)

# For cross-compiling, CMake assumes the CMAKE_SYSTEM_PROCESSOR variable
# to be set to the target processor. You can define it here or pass it
# on the command line.

# Linker flags
# For bare-metal, you might need to specify custom linker scripts using -T option.
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_BINARY_DIR} " CACHE STRING "Executable Linker Flags")

# If your project does not use the standard C library you may need to prevent
# the linker from using it. Uncomment the line below to do so.
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostdlib" CACHE STRING "Executable Linker Flags")

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
