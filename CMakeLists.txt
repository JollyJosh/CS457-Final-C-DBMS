cmake_minimum_required(VERSION 3.8)
project(Final)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c recordAttribute.c recordAttribute.h)
add_executable(Final ${SOURCE_FILES})