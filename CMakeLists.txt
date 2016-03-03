cmake_minimum_required(VERSION 3.0)

project(MatrixBench VERSION 0.1 LANGUAGES CXX)
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install")

include_directories("lib/tclap-1.2.1/include")

add_subdirectory(src)
