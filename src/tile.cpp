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

std::ostream &operator<<(std::ostream &out, const Tile &tile) {
  switch (tile.m_type) {
    case Type::empty: {
      out << "Tile (type: empty, ";
      break;
    }
    case Type::brick: {
      out << "Tile (type: brick, ";
      break;
    }
    case Type::cheese: {
      out << "Tile (type: cheese, ";
      break;
    }
    case Type::gem: {
      out << "Tile (type: gem, ";
      break;
    }
    case Type::goal: {
      out << "Tile (type: goal, ";
      break;
    }
  }
  out << "row: " << unsigned(tile.m_row) << ", col: " << unsigned(tile.m_col)
      << ", color: (red=" << unsigned(tile.m_color.red)
      << ", green=" << unsigned(tile.m_color.green)
      << ", blue=" << unsigned(tile.m_color.blue) << "))";
  return out;
}
}  // namespace tile
