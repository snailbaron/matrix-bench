configure_file(config.h.in config.h)
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_executable(bench main.cpp bench.hpp simple.cpp "${CMAKE_CURRENT_BINARY_DIR}/config.h")
