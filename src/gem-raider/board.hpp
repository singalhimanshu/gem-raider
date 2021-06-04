#pragma once

#include <SDL2/SDL.h>

#include <ostream>
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

  Board(Board &&other) noexcept : m_tiles(std::move(other.m_tiles)) {}
  Board &operator=(Board &&board) noexcept {
    if (&board != this) {
      this->m_tiles = std::move(board.m_tiles);
    }
    return *this;
  }

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
    return ((row < 0) && (col < 0) && (row >= this->m_tiles.size()) &&
            (col >= this->m_tiles[0].size()));
  }
  void m_movePlayerHelper(std::uint8_t row_neigh_offset,
                          std::uint8_t col_neigh_offset, Direction direction);
  std::vector<std::vector<Tile>> m_tiles;
  std::uint8_t m_player_row{0};
  std::uint8_t m_player_col{0};
};
}  // namespace gem_raider
