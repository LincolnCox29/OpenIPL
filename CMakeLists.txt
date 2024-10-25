cmake_minimum_required(VERSION 3.10)

project(ImgLib)

set(CMAKE_C_STANDARD 99)

set(SOURCE_DIR Z:/Projects/ImgLib/src)

# Список всех исходников в директории
file(GLOB_RECURSE SOURCE_FILES
    ${SOURCE_DIR}/*.c
)

add_library(ImgLib STATIC ${SOURCE_FILES})

# Добавляем директории для поиска заголовочных файлов
target_include_directories(ImgLib PUBLIC ${SOURCE_DIR})
target_include_directories(ImgLib PUBLIC ${SOURCE_DIR}/operations)