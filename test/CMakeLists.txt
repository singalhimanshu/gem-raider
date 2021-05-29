cmake_minimum_required(VERSION 3.15)

add_executable(
    gem-raider-test
    player_test.cpp)

target_include_directories(
    gem-raider-test PUBLIC ${PROJECT_SOURCE_DIR}/vendor/googletest/googletest/include
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(gem-raider-test PUBLIC gtest_main)
