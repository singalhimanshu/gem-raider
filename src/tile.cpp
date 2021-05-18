#include "gem-raider/tile.hpp"

#include <algorithm>
#include <cstddef>

namespace gem_raider {
std::ostream &operator<<(std::ostream &out, const Tile &tile) {
  switch (tile.type) {
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
}  // namespace gem_raider
