#include "gem-raider/board.hpp"

#include <cassert>
#include <iostream>

#include "gem-raider/constants.hpp"

namespace gem_raider {

void Board::init(std::uint8_t rows, std::uint8_t cols) noexcept {
  this->m_tiles.resize(rows);
  for (std::uint8_t r = 0; r < rows; r++) {
    this->m_tiles[r].resize(cols);
  }
}

void Board::fill() noexcept {
  std::size_t raw_board_idx = 0;
  std::uint8_t rows = this->m_tiles.size();
  std::uint8_t cols = this->m_tiles[0].size();
  assert(board::raw_board.size() == (rows * cols));
  for (std::uint8_t r = 0; r < rows; r++) {
    for (std::uint8_t c = 0; c < cols; c++) {
      Type type = static_cast<Type>(board::raw_board[raw_board_idx] - '0');
      this->m_tiles[r][c] = std::move(Tile(type, r, c));
      raw_board_idx++;
    }
  }
}

[[nodiscard]] bool Board::draw(SDL_Surface *surface) {
  int tile_x_pos = 0, tile_y_pos = 0;
  for (const auto &tiles : this->m_tiles) {
    for (const auto &tile : tiles) {
      SDL_Rect tile_rect{tile_x_pos, tile_y_pos, tile::width, tile::height};
      Color color = tile.getColor();
      Uint32 sdl_color =
          SDL_MapRGB(surface->format, color.red, color.green, color.blue);
      if (SDL_FillRect(surface, &tile_rect, sdl_color) < 0) {
        return false;
      }
      tile_x_pos += tile::height;
    }
    tile_x_pos = 0;
    tile_y_pos += tile::width;
  }
  return true;
}

[[nodiscard]] bool Board::isMoveable(std::uint8_t row, std::uint8_t col) {
  if ((row >= 0) && (col >= 0) && (row < this->m_tiles.size()) &&
      (col < this->m_tiles[0].size())) {
    return this->m_tiles[row][col].type == Type::empty;
  }
  return false;
}

std::ostream &operator<<(std::ostream &out, const Board &board) {
  for (const auto &tile_row : board.m_tiles) {
    for (const auto &tile : tile_row) {
      std::cout << tile << " ";
    }
    std::cout << std::endl;
  }
  return out;
}
}  // namespace gem_raider
