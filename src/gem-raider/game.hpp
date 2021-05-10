#pragma once

#include <SDL2/SDL.h>

#include <memory>

#include "board.hpp"

class Game {
 public:
  Game() = default;
  virtual ~Game() = default;

  void init(const char *title);
  void update();
  [[nodiscard]] inline bool is_running() { return this->m_is_running; }

 private:
  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window{
      nullptr, SDL_DestroyWindow};
  std::unique_ptr<SDL_Surface> m_surface{nullptr};
  Board m_board;
  bool m_is_running{false};
};
