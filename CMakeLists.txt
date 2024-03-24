cmake_minimum_required(VERSION 3.10)

project(MyOS VERSION 1.0 LANGUAGES CXX C ASM-ATT ASM)

set(SYSTEM_HEADER_PROJECTS "libc;kernel")
set(PROJECTS "libc;kernel")
set(ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})
set(SYSROOT "${ROOT_DIR}/sysroot")
set(CMAKE_FIND_ROOT_PATH "${SYSROOT}")

# Determine the target architecture
# Set compiler and linker settings before calling project()
if(CMAKE_SYSTEM MATCHES Windows)
   message(STATUS "Target system is Windows")
endif()

if(CMAKE_HOST_SYSTEM MATCHES Linux)
   message(STATUS "Build host runs Linux")
endif()

if(NOT CMAKE_C_COMPILER OR NOT CMAKE_CXX_COMPILER)
  message(FATAL_ERROR "Cross-compiler for ${TARGET_ARCH} not found.")
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Define the project

# Prefix, Exec Prefix, Bootdir, Libdir and Includedir definitions
set(PREFIX "/usr")
set(EXEC_PREFIX "${PREFIX}")
set(BOOTDIR "/boot")
set(LIBDIR "${EXEC_PREFIX}/lib")
set(INCLUDEDIR "${PREFIX}/include")

# Sysroot configuration
add_compile_options(--sysroot=${SYSROOT} -isystem=${INCLUDEDIR} -O2 -g)
# Compiler flags
add_compile_options(-Wall -Wextra -Werror  -O2 -g)

#TODO sanatizer implementation
#add_compile_options(-fsanitize=undefined -fno-sanitize=vptr)
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=undefined -fno-sanitize=vptr")

file(GLOB_RECURSE LIBC_HEADERS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/kernel" CONFIGURE_DEPENDS "*.h")
add_custom_target(install_all_headers  COMMENT "Installing kernel headers")

# Copy LibC's headers into the sysroot to satisfy libc++'s include priority requirements.

# Add subdirectories for each project
foreach(PROJECT IN LISTS PROJECTS)
  add_subdirectory(${PROJECT})
  add_dependencies(install_all_headers "install_${PROJECT}_headers")
endforeach()

#add_custom_target(build_iso  COMMENT "Installing kernel headers")
add_custom_target(run-qemu  COMMENT "Run kernel image in qemu")

add_dependencies(run-qemu build_iso)
# Optionally, setup install targets if your projects support installation
add_custom_target(create-isodir
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/isodir"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/isodir/boot"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/isodir/boot/grub"
    COMMENT "Creating isodir directories"
)

add_custom_command(
    OUTPUT "${CMAKE_BINARY_DIR}/isodir/boot/myos.kernel"
    COMMAND ${CMAKE_COMMAND} -E copy "${SYSROOT}/boot/myos.kernel" "${CMAKE_BINARY_DIR}/isodir/boot/myos.kernel"
    DEPENDS install_kernel_binary create-isodir
)

# Create the GRUB configuration file
file(WRITE "${CMAKE_BINARY_DIR}/isodir/boot/grub/grub.cfg"
"menuentry \"myos\" {\n\tmultiboot /boot/myos.kernel\n}\n")

# Custom target to create an ISO image using grub-mkrescue
add_custom_target(build_iso ALL
    COMMAND grub-mkrescue -o "${CMAKE_BINARY_DIR}/myos.iso" "${CMAKE_BINARY_DIR}/isodir"
    DEPENDS "${CMAKE_BINARY_DIR}/isodir/boot/myos.kernel"
    COMMENT "Creating ISO image"
)

set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
    "${SYSROOT}"
    "${CMAKE_CURRENT_BINARY_DIR}/myos.iso"
    "${CMAKE_CURRENT_BINARY_DIR}/isodir"
)
#!/bin/sh

add_custom_command(TARGET run-qemu
  DEPENDS build_iso
  COMMAND qemu-system-i386 -cdrom myos.iso
)
