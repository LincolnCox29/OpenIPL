cmake_minimum_required(VERSION 3.10)

project(OpenIPL)

set(CMAKE_C_STANDARD 99)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE SOURCE_FILES
    ${SOURCE_DIR}/*.c
)

add_library(OpenIPL STATIC ${SOURCE_FILES})

target_include_directories(OpenIPL PUBLIC ${SOURCE_DIR})
target_include_directories(OpenIPL PUBLIC ${SOURCE_DIR}/operations)
target_include_directories(OpenIPL PUBLIC ${SOURCE_DIR}/simde/x86)