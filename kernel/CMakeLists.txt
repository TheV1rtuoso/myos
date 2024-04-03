cmake_minimum_required(VERSION 3.10)

# Set the project name and version
#project(MyOS VERSION 1.0 CXX ASM)

# Specify the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)


add_custom_target(install_kernel_headers COMMENT "Install libc headers")
add_dependencies(install_headers install_kernel_headers)

add_compile_options(-D__is_kernel -Iinclude)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostdlib -lgcc")

# Architecture-specific settings
set(HOSTARCH i386)
include_directories("arch/${HOSTARCH}")

# Add architecture-specific source files
file(GLOB ARCH_SOURCES "arch/${HOSTARCH}/*.c" "arch/${HOSTARCH}/*.cpp" "arch/${HOSTARCH}/*.S")
file(GLOB MEMORY_SOURCES "kernel/Memory/*.cpp")
file(GLOB DEVICE_SOURCES "kernel/Devices/*.cpp")
file(GLOB KERNEL_SOURCES "kernel/*.cpp")

set(KERNEL_SOURCES ${KERNEL_SOURCES} ${MEMORY_SOURCES} ${DEVICE_SOURCES})

# Combine all source files
set(SOURCES ${ARCH_SOURCES} ${KERNEL_SOURCES})

# Add executable target
add_executable(myos.kernel ${SOURCES})
target_link_libraries(myos.kernel PUBLIC libk)
add_dependencies(myos.kernel install_headers)


# Set linker script
set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/kernel/arch/${HOSTARCH}/linker.ld")
set_target_properties(myos.kernel PROPERTIES LINK_FLAGS "-T ${LINKER_SCRIPT}")
# Install rules
set(CMAKE_INSTALL_PREFIX "${ROOT_DIR}/build")

install(TARGETS myos.kernel DESTINATION "${SYSROOT}/boot")

add_custom_target(install_kernel_binary
        COMMAND "${CMAKE_COMMAND}" -E make_directory "${SYSROOT}/${BOOTDIR}/"
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${CMAKE_BINARY_DIR}/kernel/myos.kernel" "${SYSROOT}/${BOOTDIR}/myos.kernel"
        DEPENDS myos.kernel
        VERBATIM
)
add_dependencies(create_isodir install_kernel_binary)
file(GLOB_RECURSE KERNEL_HEADERS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/include" CONFIGURE_DEPENDS "*.h")
foreach (RELATIVE_HEADER_PATH IN LISTS KERNEL_HEADERS)
    add_custom_command(
            TARGET install_kernel_headers
            DEPENDS "${RELATIVE_HEADER_PATH}"
            COMMAND "${CMAKE_COMMAND}" -E make_directory "${SYSROOT}/${INCLUDEDIR}/kernel"
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${RELATIVE_HEADER_PATH}" "${SYSROOT}/${INCLUDEDIR}/${RELATIVE_HEADER_PATH}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include"
            VERBATIM
    )
endforeach ()
