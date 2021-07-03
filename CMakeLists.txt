cmake_minimum_required(VERSION 3.15)

if (cxx_std_20 IN_LIST CMAKE_CXX_COMPILE_FEATURES)
  set (CMAKE_CXX_STANDARD 20)
else ()
  set (CMAKE_CXX_STANDARD 17)
endif ()

project(gem-raider CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(vendor/googletest)

file(COPY res DESTINATION ${CMAKE_BINARY_DIR})
