cmake_minimum_required(VERSION 3.14)
project(TimSort_C LANGUAGES C)

set(SOURCE_FILES
        src/main.c
        src/timsort.c)

set(HEADER_FILES
        src/timsort.h)

set(CMAKE_C_STANDARD 11)

add_executable(TimSort_C ${SOURCE_FILES} ${HEADER_FILES})