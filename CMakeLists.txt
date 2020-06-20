cmake_minimum_required(VERSION 3.14)
project(TimSort_C C)

set(CMAKE_C_STANDARD 11)

add_executable(TimSort_C src/main.c src/timsort.c src/timsort.h)