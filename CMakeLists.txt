cmake_minimum_required(VERSION 3.29)

project(neural_networks LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# lld cannot always parse the newest Apple SDK stubs; use the system ld64 there.
if(NOT APPLE)
  set(CMAKE_LINKER_TYPE LLD)
endif()

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

add_subdirectory(src)

option(NN_BUILD_TESTS "Build unit tests" ON)
if(NN_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
