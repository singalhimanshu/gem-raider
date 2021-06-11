#include <gtest/gtest.h>

#include <gem-raider/board.hpp>

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

TEST(board_test, test_move_tile_out_of_bounds) {
  Board board;
  board.init();
  board.fill();
  // first row
  for (int c = 0; c < tile::cols; c++) {
    ASSERT_FALSE(board.moveTile(0, c, Direction::up))
        << "tile at row: 0, col: " << c << " should not be moved\n";
  }
  // first col
  for (int r = 0; r < tile::rows; r++) {
    ASSERT_FALSE(board.moveTile(r, 0, Direction::left))
        << "tile at row: " << r << "col: 0 should not be moved\n";
  }
  // last row
  for (int c = 0; c < tile::cols; c++) {
    ASSERT_FALSE(board.moveTile(tile::rows - 1, c, Direction::down))
        << "tile at row: " << tile::rows - 1 << ", col: " << c
        << " should not be moved\n";
  }
  // last col
  for (int r = 0; r < tile::rows; r++) {
    ASSERT_FALSE(board.moveTile(r, tile::cols - 1, Direction::right))
        << "tile at row: " << r << ", col: " << tile::cols - 1
        << " should not be moved\n";
  }
}
}  // namespace gem_raider
