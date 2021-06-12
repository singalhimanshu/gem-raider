#pragma once

#include <SDL2/SDL.h>

#include <memory>

#include "board.hpp"
#include "button.hpp"

namespace gem_raider {
class Game {
 public:
  Game() = default;
  virtual ~Game() { TTF_Quit(); };
  void init(const char *title);
  void update();
  [[nodiscard]] bool is_running() { return this->m_is_running; }
  void reset();

 private:
  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window{
      nullptr, SDL_DestroyWindow};
  std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer{
      nullptr, SDL_DestroyRenderer};
  Board m_board;
  bool m_is_running{false};
  Button m_reset_button;
  Button m_quit_button;
};
}  // namespace gem_raider
