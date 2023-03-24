cmake_minimum_required(VERSION 3.5)

set(project_path "${CMAKE_CURRENT_SOURCE_DIR}/")
set(input_path "${project_path}input/")
set(output_path "${project_path}output/")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config/config.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/code/config.h")

project(CAGD LANGUAGES CXX)

find_package(Eigen3 CONFIG REQUIRED)

add_subdirectory(code)