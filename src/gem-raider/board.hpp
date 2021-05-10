#pragma once

#include <SDL2/SDL.h>

#include <ostream>
#include <string>
#include <vector>

#include "tile.hpp"

class Board {
 public:
  Board(std::uint8_t _rows, std::uint8_t _cols) {
    // TODO: Figure out why this is wrong: m_tiles.resize(_rows,
    // std::vector<tile::Tile>(_cols, tile::Tile()));
    m_tiles.resize(_rows);
    for (std::uint8_t r = 0; r < _rows; r++) {
      m_tiles[r].resize(_cols);
    }
  }

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

  void fill() noexcept;
  [[nodiscard]] bool draw(SDL_Surface *surface);
  friend std::ostream &operator<<(std::ostream &out, const Board &board);

 private:
  std::vector<std::vector<tile::Tile>> m_tiles;
};
