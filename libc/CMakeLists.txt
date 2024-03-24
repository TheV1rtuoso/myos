cmake_minimum_required(VERSION 3.10)
#project(MyLibrary VERSION 1.0)

# Set the default host if not specified
if(NOT DEFINED TARGET_ARCH)
  execute_process(
    COMMAND ../default-host.sh
    OUTPUT_VARIABLE TARGET_ARCH
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
endif()

# Determine the host architecture
execute_process(
  COMMAND ../target-triplet-to-arch.sh ${TARGET_ARCH}
  OUTPUT_VARIABLE HOSTARCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(NOT DEFINED HOST_ARCH)
    set(HOSTARCH i386)
endif()

file(GLOB_RECURSE LIBC_HEADERS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" CONFIGURE_DEPENDS "*.h")

add_custom_target(install_libc_headers)

# Copy LibC's headers into the sysroot to satisfy libc++'s include priority requirements.
foreach(RELATIVE_HEADER_PATH IN LISTS LIBC_HEADERS)
    get_filename_component(directory ${RELATIVE_HEADER_PATH} DIRECTORY)
    string(REPLACE "../" "" subdirectory "${directory}")
    file(MAKE_DIRECTORY "${SYSROOT}/${PREFIX}/${subdirectory}")
    add_custom_command(
        TARGET install_libc_headers
        PRE_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${RELATIVE_HEADER_PATH}" "${SYSROOT}/${PREFIX}/${subdirectory}"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
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
set(FREEOBJS
  stdio/putchar.c
  stdio/puts.c
  stdlib/abort.c
  string/memcmp.c
  string/memcpy.c
  string/memmove.c
  string/memset.c
  string/strlen.cpp
  stdio/printf.cpp
)

# Convert FREEOBJS to object library
add_library(freeobjs OBJECT ${FREEOBJS})
target_compile_options(freeobjs PUBLIC ${CMAKE_C_FLAGS} ${CPPFLAGS})

# LIBK objects
set(LIBK_OBJS ${FREEOBJS})

add_library(libk OBJECT ${LIBK_OBJS})
target_compile_options(libk PUBLIC ${LIBK_CFLAGS} ${LIBK_CPPFLAGS})

# Create the libk.a static library
add_library(libk_static STATIC ${FREEOBJS})
add_dependencies(libk install_all_headers)
add_dependencies(libk_static install_all_headers)
add_dependencies(freeobjs install_all_headers)
set_target_properties(libk_static PROPERTIES OUTPUT_NAME "libk")
install(TARGETS libk_static ARCHIVE DESTINATION ${SYSROOT}/usr/lib)
