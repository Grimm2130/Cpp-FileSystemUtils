cmake_minimum_required(VERSION 3.0.0)

option(RUN_TESTS "Flag is set if tests are to be run" FALSE)

set(LIB_FILE_SYS_UTILS_FILE "FileSystemUtils_File")
set(LIB_FILE_SYS_UTILS_DIRECTORY "FileSystemUtils_Directory")
set(CPP_TEMPLATES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ExternalModules/Templates")

project(FileSystemUtils)

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/Inc"
    ${CPP_TEMPLATES_DIR}
)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Src")

if(RUN_TESTS)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Tests")
endif(RUN_TESTS)
