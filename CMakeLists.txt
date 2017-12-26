cmake_minimum_required(VERSION 3.8)
project(Final)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES src/main.c src/recordAttribute.c src/recordAttribute.h src/record.c src/record.h)
add_executable(Final ${SOURCE_FILES})