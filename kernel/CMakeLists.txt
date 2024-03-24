cmake_minimum_required(VERSION 3.10)

# Set the project name and version
#project(MyOS VERSION 1.0 CXX ASM)

# Specify the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)


# Compiler flags
add_compile_options(-D__is_kernel -Iinclude)

# Linker flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostdlib -lgcc")

# Architecture-specific settings
set(HOSTARCH i386)
include_directories("arch/${HOSTARCH}")

# Add architecture-specific source files
file(GLOB ARCH_SOURCES "arch/${HOSTARCH}/*.c" "arch/${HOSTARCH}/*.cpp" "arch/${HOSTARCH}/*.S")

set(KERNEL_SOURCES kernel/kernel.cpp)

# Combine all source files
set(SOURCES ${ARCH_SOURCES} ${KERNEL_SOURCES})

# Add executable target
add_executable(myos.kernel ${SOURCES} )
target_link_libraries(myos.kernel PUBLIC libk)
add_dependencies(myos.kernel install_all_headers)


# Set linker script
set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/kernel/arch/${HOSTARCH}/linker.ld")
set_target_properties(myos.kernel PROPERTIES LINK_FLAGS "-T ${LINKER_SCRIPT}")
# Install rules
set(CMAKE_INSTALL_PREFIX "${ROOT_DIR}/build")

install(TARGETS myos.kernel DESTINATION "${SYSROOT}/boot")
install(TARGETS myos.kernel DESTINATION "${SYSROOT}/boot")
add_custom_target(install_kernel_binary  COMMENT "Installing kernel binary")
add_dependencies(install_kernel_binary myos.kernel)

file(MAKE_DIRECTORY "${SYSROOT}/${BOOTDIR}")
add_custom_command(
    TARGET install_kernel_binary
    POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${CMAKE_BINARY_DIR}/kernel/myos.kernel" "${SYSROOT}/${BOOTDIR}/myos.kernel"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    DEPENDS myos.kernel
    VERBATIM
)

# Custom target for header installation (optional)
add_custom_target(install_kernel_headers  COMMENT "Installing kernel headers")
file(GLOB_RECURSE KERNEL_HEADERS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" CONFIGURE_DEPENDS "*.h")
foreach(RELATIVE_HEADER_PATH IN LISTS KERNEL_HEADERS)
    get_filename_component(directory ${RELATIVE_HEADER_PATH} DIRECTORY)
    string(REPLACE "../" "" subdirectory "${directory}")
    file(MAKE_DIRECTORY "${SYSROOT}/${INCLUDEDIR}/kernel")
    add_custom_command(
        TARGET install_kernel_headers
        PRE_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${RELATIVE_HEADER_PATH}" "${SYSROOT}/${INCLUDEDIR}/kernel"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        VERBATIM
    )
endforeach()
