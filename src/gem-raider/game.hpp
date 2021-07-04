#pragma once

#include <SDL2/SDL.h>

#include <memory>

#include "board.hpp"
#include "button.hpp"
#include "game_timer.hpp"
#include "progress_bar.hpp"
#include "timer.hpp"

namespace gem_raider {
class Game {
 public:
  explicit Game(Timer &timer) : m_game_timer(timer) {}
  virtual ~Game() { TTF_Quit(); };

  Game(const Game &game) = default;
  Game &operator=(const Game &game) = default;

  Game(Game &&game) = default;
  Game &operator=(Game &&game) = default;

  void init(const char *title);
  void update();
  [[nodiscard]] bool is_running() {
    return !this->is_game_time_over() && this->m_is_running;
  }
  void reset();
  void start() { this->m_is_running = true; }
  void stop() { this->m_is_running = false; }
  [[nodiscard]] bool is_game_time_over();

 private:
  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window{
      nullptr, SDL_DestroyWindow};
  std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer{
      nullptr, SDL_DestroyRenderer};
  Board m_board;
  bool m_is_running{false};
  Button m_reset_button;
  Button m_quit_button;
  Timer &m_game_timer;
  ProgressBar m_time_progress_bar;
};
}  // namespace gem_raider
