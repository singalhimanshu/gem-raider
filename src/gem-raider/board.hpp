#pragma once

#include <SDL2/SDL.h>

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

  void fill();
  [[nodiscard]] bool draw(SDL_Surface *surface);

 private:
  std::vector<std::vector<tile::Tile>> m_tiles;
};
