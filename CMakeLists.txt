cmake_minimum_required(VERSION 3.10)

project(ImgLibProject)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES
    ImgLib.h
    ImgLib.c
)

add_library(ImgLib STATIC ${SOURCE_FILES})

target_include_directories(ImgLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})