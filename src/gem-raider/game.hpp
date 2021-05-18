#pragma once

#include <SDL2/SDL.h>

#include <memory>

#include "board.hpp"
#include "player.hpp"

namespace gem_raider {

class Game {
 public:
  Game() = default;
  virtual ~Game() { SDL_FreeSurface(this->m_surface); }
  void init(const char *title);
  void update();
  [[nodiscard]] inline bool is_running() { return this->m_is_running; }

 private:
  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window{
      nullptr, SDL_DestroyWindow};
  SDL_Surface *m_surface{nullptr};
  Board m_board;
  bool m_is_running{false};
  Player m_player;
};
}  // namespace gem_raider
