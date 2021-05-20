#include "gem-raider/player.hpp"

namespace gem_raider {

[[nodiscard]] bool Player::draw(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
  SDL_Rect player_rect{this->m_x_pos, this->m_y_pos, player::width,
                       player::height};
  if (SDL_RenderFillRect(renderer, &player_rect) < 0) {
    return false;
  }
  return true;
}

void Player::move(Direction direction, Board &board) {
  switch (direction) {
    case Direction::left: {
      Type type = board.getTileType(this->m_row, this->m_col - 1);
      switch (type) {
        case Type::gem: {
          if (!board.moveTile(this->m_row, this->m_col - 1, Direction::left)) {
            break;
          } else {
            Direction maybe_dest_direction =
                board.levelCompleted(this->m_row, this->m_col - 2);
            if (maybe_dest_direction != Direction::none) {
              board.dest_reached = true;
              return;
            }
          }
        }
        case Type::empty: {
          this->m_x_pos -= player::width;
          this->m_col--;
          break;
        }
      }
      break;
    }
    case Direction::right: {
      Type type = board.getTileType(this->m_row, this->m_col + 1);
      switch (type) {
        case Type::gem: {
          if (!board.moveTile(this->m_row, this->m_col + 1, Direction::right)) {
            break;
          } else {
            Direction maybe_dest_direction =
                board.levelCompleted(this->m_row, this->m_col + 2);
            if (maybe_dest_direction != Direction::none) {
              board.dest_reached = true;
              return;
            }
          }
          case Type::empty: {
            this->m_x_pos += player::width;
            this->m_col++;
            break;
          }
        }
      }
      break;
    }
    case Direction::up: {
      Type type = board.getTileType(this->m_row - 1, this->m_col);
      switch (type) {
        case Type::gem: {
          if (!board.moveTile(this->m_row - 1, this->m_col, Direction::up)) {
            break;
          } else {
            Direction maybe_dest_direction =
                board.levelCompleted(this->m_row - 2, this->m_col);
            if (maybe_dest_direction != Direction::none) {
              board.dest_reached = true;
              return;
            }
          }
          case Type::empty: {
            this->m_y_pos -= player::height;
            this->m_row--;
            break;
          }
        }
      }
      break;
    }
    case Direction::down: {
      Type type = board.getTileType(this->m_row + 1, this->m_col);
      switch (type) {
        case Type::gem: {
          if (!board.moveTile(this->m_row + 1, this->m_col, Direction::down)) {
            break;
          } else {
            Direction maybe_dest_direction =
                board.levelCompleted(this->m_row + 2, this->m_col);
            if (maybe_dest_direction != Direction::none) {
              board.dest_reached = true;
              return;
            }
          }
          case Type::empty: {
            this->m_y_pos += player::height;
            this->m_row++;
            break;
          }
        }
      }
      break;
    }
  }
}

}  // namespace gem_raider
