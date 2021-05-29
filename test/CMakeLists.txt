cmake_minimum_required(VERSION 3.15)

include_directories(
    ${PROJECT_SOURCE_DIR/vendor/gtest/include}
    ${PROJECT_SOURCE_DIR/src}
)

add_executable(
  gem-raider-test
  player_test.cpp
)

target_link_libraries(
  gem-raider-test
  gtest_main
)

add_test(gem-raider-test gem-raider-test)
