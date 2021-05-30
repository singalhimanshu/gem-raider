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

[[nodiscard]] bool Board::draw(SDL_Renderer *renderer) {
  int tile_x_pos = 0, tile_y_pos = window::top_bar_height;
  for (const auto &tiles : this->m_tiles) {
    for (const auto &tile : tiles) {
      Color color = tile.getColor();
      SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, 0);
      SDL_Rect tile_rect{tile_x_pos, tile_y_pos, tile::width, tile::height};
      if (SDL_RenderFillRect(renderer, &tile_rect) < 0) {
        return false;
      }
      tile_x_pos += tile::height;
    }
    tile_x_pos = 0;
    tile_y_pos += tile::width;
  }
  return true;
}

Type Board::getTileType(std::uint8_t row, std::uint8_t col) {
  if (this->m_isOutOfBounds(row, col)) {
    return Type::brick;
  }
  return this->m_tiles[row][col].type;
}

[[nodiscard]] bool Board::moveTile(std::uint8_t row, std::uint8_t col,
                                   Direction direction) {
  if (this->m_isOutOfBounds(row, col)) {
    return false;
  }
  bool moved = false;
  switch (direction) {
    case Direction::left: {
      if (getTileType(row, col - 1) == Type::empty) {
        std::swap(this->m_tiles[row][col], this->m_tiles[row][col - 1]);
        moved = true;
      }
      break;
    }
    case Direction::right: {
      std::size_t col_size = this->m_tiles[0].size();
      if (getTileType(row, col + 1) == Type::empty) {
        std::swap(this->m_tiles[row][col], this->m_tiles[row][col + 1]);
        moved = true;
      }
      break;
    }
    case Direction::up: {
      if (getTileType(row - 1, col) == Type::empty) {
        std::swap(this->m_tiles[row][col], this->m_tiles[row - 1][col]);
        moved = true;
      }
      break;
    }
    case Direction::down: {
      std::size_t row_size = this->m_tiles.size();
      if (getTileType(row + 1, col) == Type::empty) {
        std::swap(this->m_tiles[row][col], this->m_tiles[row + 1][col]);
        moved = true;
      }
      break;
    }
    default:
      break;
  }
  return moved;
}

Direction Board::levelCompleted(std::uint8_t row, std::uint8_t col) {
  if (!this->m_isOutOfBounds(row, col)) {
    if (getTileType(row, col - 1) == Type::goal) {
      return Direction::left;
    } else if (getTileType(row, col + 1) == Type::goal) {
      return Direction::right;
    } else if (getTileType(row - 1, col) == Type::goal) {
      return Direction::up;
    } else if (getTileType(row + 1, col) == Type::goal) {
      return Direction::down;
    }
  }
  return Direction::none;
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
