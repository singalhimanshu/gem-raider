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

  void init(std::uint8_t rows, std::uint8_t cols) noexcept;
  void fill() noexcept;
  [[nodiscard]] bool draw(SDL_Renderer *renderer);
  Type getTileType(std::uint8_t row, std::uint8_t col);
  [[nodiscard]] bool moveTile(std::uint8_t row, std::uint8_t col,
                              Direction direction);
  [[nodiscard]] Direction levelCompleted(std::uint8_t row, std::uint8_t col);
  void reset() { this->fill(); }
  friend std::ostream &operator<<(std::ostream &out, const Board &board);

 private:
  [[nodiscard]] bool m_isOutOfBounds(std::uint8_t row, std::uint8_t col) {
    return ((row < 0) && (col < 0) && (row >= this->m_tiles.size()) &&
            (col >= this->m_tiles[0].size()));
  }
  std::vector<std::vector<Tile>> m_tiles;
};
}  // namespace gem_raider
