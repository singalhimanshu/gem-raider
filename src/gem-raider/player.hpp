#pragma once

#include <cassert>

#include "board.hpp"
#include "constants.hpp"

namespace gem_raider {

class Player {
 public:
  Player() = default;
  Player(std::uint16_t row_, std::uint16_t col_) : m_row(row_), m_col(col_) {
    assert((row_ < tile::rows) && (col_ < tile::cols));
    m_x_pos = col_ * player::width;
    m_y_pos = row_ * player::height;
  }
  virtual ~Player() = default;

  Player(const Player &player) = default;
  Player &operator=(const Player &player) noexcept {
    if (this != &player) {
      this->m_x_pos = player.m_x_pos;
      this->m_y_pos = player.m_y_pos;
      this->m_row = player.m_row;
      this->m_col = player.m_col;
    }
    return *this;
  }

  Player(Player &&player) = default;
  Player &operator=(Player &&player) noexcept {
    if (this != &player) {
      this->m_x_pos = std::move(player.m_x_pos);
      this->m_y_pos = std::move(player.m_y_pos);
      this->m_row = std::move(player.m_row);
      this->m_col = std::move(player.m_col);
    }
    return *this;
  }

  [[nodiscard]] bool draw(SDL_Renderer *renderer);
  void move(Direction direction, Board &board);

 private:
  std::uint16_t m_x_pos{0};
  std::uint16_t m_y_pos{0};
  std::uint8_t m_row{0};
  std::uint8_t m_col{0};
};
}  // namespace gem_raider
