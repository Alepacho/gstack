cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME "gstack")
project(${PROJECT_NAME} LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -pedantic")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")

set(SOURCES
    "src/main.c"
    "src/vm.c"
    "src/stack.c"
    "src/ram.c"
)

add_executable(${PROJECT_NAME} ${SOURCES})
