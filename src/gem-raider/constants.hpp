#pragma once
#include <string>

namespace constants {

namespace window {
constexpr inline int height = 640;
constexpr inline int width = 480;
}  // namespace window

namespace player {
constexpr inline int height = 32;
constexpr inline int width = 32;
}  // namespace player

namespace tile {
constexpr inline int rows = window::height / player::height;
constexpr inline int cols = window::width / player::width;
constexpr inline int size = rows * cols;
constexpr inline int height = 32;
constexpr inline int width = 32;
}  // namespace tile

namespace board {
const std::string raw_board =
    "111111111111111\
100000000000001\
100000000000001\
100000000000001\
100111000111001\
100111000111001\
100111000111001\
100111000111001\
100111000111001\
100111030111001\
100111000111001\
100111000111001\
100111000111001\
100111000111001\
100111000111001\
100000000000001\
100000000000001\
100000000000001\
100000000000001\
111111141111111";
}
}  // namespace constants
