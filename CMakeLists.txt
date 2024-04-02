cmake_minimum_required(VERSION 3.10)

if (NOT CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_LIST_DIR}/toolchain-i686-elf.cmake)
endif()

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
add_compile_options(--sysroot=${SYSROOT} -isystem=${INCLUDEDIR})
# Compiler flags
add_compile_options(-Wall -Wextra -Werror -g -O2)

#disable RTTI, Exceptions
#add_compile_options(-fno-exceptions -fno-rtti)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti")


#TODO sanatizer implementation
#add_compile_options(-fsanitize=undefined -fno-sanitize=vptr)
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=undefined -fno-sanitize=vptr")

add_custom_target(install_headers  COMMENT "Installing kernel headers")
add_custom_target(create_isodir)

foreach(PROJECT IN LISTS PROJECTS)
  add_subdirectory(${PROJECT})
endforeach()



add_custom_target(build_iso)

add_custom_target(run-qemu
  DEPENDS myos.kernel
  COMMAND qemu-system-i386 -kernel "${CMAKE_CURRENT_BINARY_DIR}/kernel/myos.kernel"
  COMMENT "Run kernel binary in qemu with -kernel"
)

add_custom_target(run-qemu-iso
  DEPENDS build_iso
  COMMAND qemu-system-i386 -cdrom myos.iso -serial file:${CMAKE_CURRENT_BINARY_DIR}/output.txt
  COMMENT "Run kernel image in qemu"
)

add_custom_target(run-bochs
  DEPENDS build_iso
  COMMAND bochs -q -f bochsrc.txt
  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
  COMMENT "Run kernel image in bochs"
)

add_custom_target(debug-kernel-qemu
  DEPENDS myos.kernel
  COMMAND qemu-system-i386 -s -S -kernel "${CMAKE_CURRENT_BINARY_DIR}/kernel/myos.kernel" & gdb kernel/myos.kernel
  COMMENT "Debug kernel binary in qemu with -kernel"
)

add_dependencies(build_iso create_isodir)

add_custom_command(TARGET create_isodir
    COMMAND ${CMAKE_COMMAND} -E make_directory "isodir/boot/"
    COMMAND ${CMAKE_COMMAND} -E make_directory "isodir/boot/grub"
    COMMAND ${CMAKE_COMMAND} -E copy "${SYSROOT}/boot/myos.kernel" "isodir/boot/myos.kernel"
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_LIST_DIR}/grub.cfg" "isodir/boot/grub/grub.cfg"
    DEPENDS "${CMAKE_CURRENT_LIST_DIR}/grub.cfg"
    COMMENT "Creating isodir structure, copy kernel"
)

add_custom_command(TARGET build_iso
    COMMAND grub-mkrescue -o "myos.iso" "isodir"
    COMMENT "Creating ISO image"
)

set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
    "${SYSROOT}"
    "${CMAKE_CURRENT_BINARY_DIR}/myos.iso"
    "${CMAKE_CURRENT_BINARY_DIR}/isodir"
)
