#include "gem-raider/tile.hpp"

#include <algorithm>
#include <cassert>
#include <cstddef>

namespace tile {
void Tile::move(std::vector<std::vector<Tile>> &tile_map, Direction direction) {
  assert(this->m_type == Type::gem);
  // TODO: check for the previous tile is not a brick or cheese
  switch (direction) {
    case Direction::left: {
      if ((this->m_col >= 0)) {
        std::swap(tile_map[this->m_row][this->m_col],
                  tile_map[this->m_row][this->m_col - 1]);
      }
      break;
    }
    case Direction::right: {
      std::size_t col_size = tile_map[0].size();
      if (this->m_col + 1 < col_size) {
        std::swap(tile_map[this->m_row][this->m_col],
                  tile_map[this->m_row][this->m_col + 1]);
      }
      break;
    }
    case Direction::up: {
      if (this->m_row - 1 >= 0) {
        std::swap(tile_map[this->m_row][this->m_col],
                  tile_map[this->m_row - 1][this->m_col]);
      }
      break;
    }
    case Direction::down: {
      std::size_t row_size = tile_map.size();
      if (this->m_row + 1 < row_size) {
        std::swap(tile_map[this->m_row][this->m_col],
                  tile_map[this->m_row + 1][this->m_col]);
      }
      break;
    }
  }
}
}  // namespace tile
