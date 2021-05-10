#pragma once

#include <SDL2/SDL.h>

#include <ostream>
#include <string>
#include <vector>

#include "tile.hpp"

class Board {
 public:
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
  [[nodiscard]] bool draw(SDL_Surface *surface);
  friend std::ostream &operator<<(std::ostream &out, const Board &board);

 private:
  std::vector<std::vector<tile::Tile>> m_tiles;
};
