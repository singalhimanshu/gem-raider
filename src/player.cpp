#include "gem-raider/player.hpp"

namespace gem_raider {

[[nodiscard]] bool Player::draw(SDL_Surface *surface) {
  Uint32 player_color = SDL_MapRGB(surface->format, 128, 128, 128);
  SDL_Rect player_rect{this->m_x_pos, this->m_y_pos, player::width,
                       player::height};
  if (SDL_FillRect(surface, &player_rect, player_color) < 0) {
    return false;
  }
  return true;
}

void Player::move(Direction direction, Board &board) {
  auto is_moveable = [&](std::uint8_t row, std::uint8_t col) {
    return board.isMoveable(row, col);
  };
  switch (direction) {
    case Direction::left: {
      if (is_moveable(this->m_row, this->m_col - 1)) {
        this->m_x_pos -= player::width;
        this->m_col--;
      }
      break;
    }
    case Direction::right: {
      if (is_moveable(this->m_row, this->m_col + 1)) {
        this->m_x_pos += player::width;
        this->m_col++;
      }
      break;
    }
    case Direction::up: {
      if (is_moveable(this->m_row - 1, this->m_col)) {
        this->m_y_pos -= player::height;
        this->m_row--;
      }
      break;
    }
    case Direction::down: {
      if (is_moveable(this->m_row + 1, this->m_col)) {
        this->m_y_pos += player::height;
        this->m_row++;
      }
      break;
    }
  }
}
}  // namespace gem_raider
