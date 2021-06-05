#include <gem-raider/board.hpp>

#include <gtest/gtest.h>

namespace gem_raider {
TEST(board_test, board_boundary_tile_is_of_type_brick_or_gem) {
  Board board;
  board.init();
  board.fill();
  // first row
  for (int c = 0; c < tile::cols; c++) {
    ASSERT_EQ(board.getTileType(0, c), Type::brick);
  }
  // first col
  for (int r = 0; r < tile::rows; r++) {
    ASSERT_EQ(board.getTileType(r, 0), Type::brick);
  }
  Type tile_type = Type::brick;
  // last row
  for (int c = 0; c < tile::cols; c++) {
    tile_type = board.getTileType(tile::rows - 1, c);
    EXPECT_TRUE(tile_type == Type::brick || tile_type == Type::goal);
  }
  // last col
  for (int r = 0; r < tile::rows; r++) {
    tile_type = board.getTileType(r, tile::cols - 1);
    EXPECT_TRUE(tile_type == Type::brick || tile_type == Type::goal);
  }
}
}  // namespace gem_raider
