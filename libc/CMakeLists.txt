cmake_minimum_required(VERSION 3.10)


add_custom_target(install_lib_headers COMMENT "Install libc headers")
add_dependencies(install_headers install_lib_headers)


file(GLOB_RECURSE LIBC_HEADERS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" CONFIGURE_DEPENDS "*.h")

# Copy LibC's headers into the sysroot to satisfy libc++'s include priority requirements.
foreach(RELATIVE_HEADER_PATH IN LISTS LIBC_HEADERS)
    get_filename_component(directory ${RELATIVE_HEADER_PATH} DIRECTORY)
    string(REPLACE "../" "" subdirectory "${directory}")
    add_custom_command(
        COMMAND "${CMAKE_COMMAND}" -E make_directory "${SYSROOT}/${PREFIX}/${subdirectory}"
        OUTPUT "${SYSROOT}/${PREFIX}/${subdirectory}"
        VERBATIM
    )
    add_custom_command(
        TARGET install_lib_headers
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${RELATIVE_HEADER_PATH}" "${SYSROOT}/${PREFIX}/${subdirectory}"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        DEPENDS "${RELATIVE_HEADER_PATH}"
        VERBATIM
    )
endforeach()


add_compile_options(-D__is_libc -Iinclude -D__is_libk)
# Include the architecture-specific settings

# Add definitions based on the architecture-specific settings
add_compile_definitions(${ARCH_CFLAGS})
add_compile_definitions(${ARCH_CPPFLAGS})
add_compile_definitions(${KERNEL_ARCH_CFLAGS})
add_compile_definitions(${KERNEL_ARCH_CPPFLAGS})

# Source files
file(GLOB LIBC_SOURCES "stdio/*.cpp" "stdlib/*.cpp" "string/*.cpp")
set(LIBK_OBJECTS ${LIBC_SOURCES})

# Convert FREEOBJS to object library

add_library(libk STATIC ${LIBK_OBJECTS})
add_dependencies(libk install_headers)

install(TARGETS libk ARCHIVE DESTINATION ${SYSROOT}/usr/lib)
