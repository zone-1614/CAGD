cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(project_path "${CMAKE_CURRENT_SOURCE_DIR}/")
set(input_path "${project_path}input/")
set(output_path "${project_path}output/")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config/config.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/code/config.h")

project(CAGD LANGUAGES CXX)

add_definitions(-D_USE_MATH_DEFINES)

find_package(Eigen3 CONFIG REQUIRED)
find_package(openmesh REQUIRED)

add_subdirectory(code)