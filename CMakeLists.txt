cmake_minimum_required(VERSION 3.16)
project(showip)

set(CMAKE_C_STANDARD 11)

file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.c
)

add_executable(showip   
    ${SOURCES}
)