configure_file(config.h.in config.h)
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_executable(bench main.cpp bench.hpp simple.cpp errors.hpp bench.cpp running_median.hpp "${CMAKE_CURRENT_BINARY_DIR}/config.h")

INSTALL(TARGETS bench DESTINATION ".")