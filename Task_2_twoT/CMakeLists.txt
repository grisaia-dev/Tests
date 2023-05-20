cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

project(MAIN LANGUAGES CXX)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/Debug)

add_subdirectory(../Catch2 Catch2-build)
add_executable(${PROJECT_NAME} main.cpp src/List.hpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2WithMain)