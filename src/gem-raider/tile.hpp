#pragma once
#include <cassert>
#include <cstdint>
#include <ostream>
#include <vector>

#include "constants.hpp"

namespace gem_raider {

enum class Type : std::uint8_t { empty, brick, cheese, gem, goal, player };

enum class Direction { left, right, up, down, none };

struct Color {
  std::uint8_t red;
  std::uint8_t green;
  std::uint8_t blue;
};

class Tile {
 public:
  Type type;
  Tile() = default;
  Tile(Type _type, std::uint8_t _row, std::uint8_t _col)
      : type(_type), m_row(_row), m_col(_col) {
    assert((_row < tile::rows) && (_col < tile::cols));
    switch (_type) {
      case Type::empty: {
        Color color{.red = 0, .green = 0, .blue = 0};
        this->m_color = color;
        break;
      }
      case Type::brick: {
        Color color{.red = 181, .green = 101, .blue = 29};
        this->m_color = color;
        break;
      }
      case Type::cheese: {
        Color color{.red = 255, .green = 243, .blue = 138};
        this->m_color = color;
        break;
      }
      case Type::gem: {
        Color color{.red = 82, .green = 201, .blue = 243};
        this->m_color = color;
        break;
      }
      case Type::goal: {
        Color color{.red = 25, .green = 77, .blue = 0};
        this->m_color = color;
        break;
      }
      case Type::player: {
        Color color{.red = 128, .green = 128, .blue = 128};
        this->m_color = color;
        break;
      }
    }
  }

  virtual ~Tile() = default;

  Tile(const Tile &other)
      : type(other.type),
        m_row(other.m_row),
        m_col(other.m_col),
        m_color(other.m_color) {}

  // TODO: See if copy-swap idiom is possible
  Tile &operator=(const Tile &other) noexcept {
    if (this != &other) {
      this->type = other.type;
      this->m_row = other.m_row;
      this->m_col = other.m_col;
      this->m_color = other.m_color;
    }
    return *this;
  }

  Tile(Tile &&other) noexcept
      : type(std::move(other.type)),
        m_row(std::move(other.m_row)),
        m_col(std::move(other.m_col)),
        m_color(std::move(other.m_color)) {}

  Tile &operator=(Tile &&other) noexcept {
    if (&other != this) {
      this->type = std::move(other.type);
      this->m_row = std::move(other.m_row);
      this->m_col = std::move(other.m_col);
      this->m_color = std::move(other.m_color);
    }
    return *this;
  }

  [[nodiscard]] Color getColor() const noexcept { return this->m_color; }
  friend std::ostream &operator<<(std::ostream &out, const Tile &tile);

 private:
  std::uint8_t m_row;
  std::uint8_t m_col;
  Color m_color;
};
}  // namespace gem_raider
