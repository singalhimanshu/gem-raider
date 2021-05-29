cmake_minimum_required(VERSION 3.15)

set (CMAKE_CXX_STANDARD 17)

project(gem-raider CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(vendor/googletest)

file(COPY res DESTINATION ${CMAKE_BINARY_DIR})
