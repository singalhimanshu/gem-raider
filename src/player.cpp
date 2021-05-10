#include "gem-raider/player.hpp"

namespace const_player = constants::player;
namespace const_window = constants::window;

namespace tile {
[[nodiscard]] bool Player::draw(SDL_Surface *surface) {
  Uint32 player_color = SDL_MapRGB(surface->format, 128, 128, 128);
  SDL_Rect player_rect{this->m_x_pos, this->m_y_pos, const_player::width,
                       const_player::height};
  if (SDL_FillRect(surface, &player_rect, player_color) < 0) {
    return false;
  }
  return true;
}

void Player::move(Direction direction, Board &board) {
  switch (direction) {
    case Direction::left: {
      if (this->m_x_pos - const_player::width >= 0) {
        this->m_x_pos -= const_player::width;
        this->m_col--;
      }
      break;
    }
    case Direction::right: {
      if (this->m_x_pos + const_player::width < const_window::width) {
        this->m_x_pos += const_player::width;
        this->m_col++;
      }
      break;
    }
    case Direction::up: {
      if (this->m_y_pos - const_player::height >= 0) {
        this->m_y_pos -= const_player::height;
        this->m_row--;
      }
      break;
    }
    case Direction::down: {
      if (this->m_y_pos + const_player::height < const_window::height) {
        this->m_y_pos += const_player::height;
        this->m_row++;
      }
      break;
    }
  }
}
}  // namespace tile
