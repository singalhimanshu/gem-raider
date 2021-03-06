#pragma once

#include <SDL2/SDL.h>

#include <iostream>
#include <string>
#include <vector>

#include "tile.hpp"

namespace gem_raider {

class Board {
 public:
  bool dest_reached{false};
  Board() = default;

  virtual ~Board() = default;

  Board(const Board &board) = default;
  Board &operator=(const Board &board) = default;

  Board(Board &&other) noexcept = default;
  Board &operator=(Board &&board) noexcept = default;

  void init() noexcept;
  void fill() noexcept;
  [[nodiscard]] bool draw(SDL_Renderer *renderer);
  Type getTileType(std::uint8_t row, std::uint8_t col);
  [[nodiscard]] bool moveTile(std::uint8_t row, std::uint8_t col,
                              Direction direction);
  [[nodiscard]] Direction isLevelCompleted(std::uint8_t row, std::uint8_t col);
  void reset() { this->fill(); }
  void movePlayer(Direction direction);
  void levelCompleted(std::uint8_t gem_row, std::uint8_t gem_col);

  friend std::ostream &operator<<(std::ostream &out, const Board &board);

 private:
  [[nodiscard]] bool m_isOutOfBounds(std::uint8_t row, std::uint8_t col) {
    return ((row >= this->m_tiles.size()) && (col >= this->m_tiles[0].size()));
  }
  void m_movePlayerHelper(std::uint8_t row_neigh_offset,
                          std::uint8_t col_neigh_offset, Direction direction);
  [[nodiscard]] bool m_moveTileHelper(std::uint8_t row, std::uint8_t col,
                                      std::uint8_t new_row,
                                      std::uint8_t new_col) {
    if (this->m_isOutOfBounds(new_row, new_col) ||
        getTileType(new_row, new_col) != Type::empty) {
      return false;
    }
    std::swap(this->m_tiles[row][col], this->m_tiles[new_row][new_col]);
    return true;
  }
  [[nodiscard]] bool m_isTileMoveable(std::uint8_t row, std::uint8_t col) {
    Type tile_type = this->getTileType(row, col);
    if (tile_type == Type::player || tile_type == Type::gem) {
      return true;
    }
    return false;
  }
  std::vector<std::vector<Tile>> m_tiles;
  std::uint8_t m_player_row{0};
  std::uint8_t m_player_col{0};
};
}  // namespace gem_raider
