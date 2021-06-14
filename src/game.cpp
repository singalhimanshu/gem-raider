#include <gem-raider/constants.hpp>
#include <gem-raider/game.hpp>
#include <iostream>

namespace gem_raider {

void Game::init(const char *title) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
    return;
  }
  if (TTF_Init() != 0) {
    SDL_Log("Failed to initialize TTF: %s", SDL_GetError());
    return;
  }
  this->m_window.reset(SDL_CreateWindow(
      title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window::width,
      window::height + window::top_bar_height, 0));
  if (!this->m_window) {
    std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
    return;
  }
  this->m_renderer.reset(
      SDL_CreateRenderer(this->m_window.get(), -1, SDL_RENDERER_ACCELERATED));
  if (this->m_renderer == nullptr) {
    std::cerr << "Failed to create SDL renderer: " << SDL_GetError()
              << std::endl;
    return;
  }
  this->m_board.init();
  this->m_board.fill();
  this->m_reset_button =
      std::move(Button(100, 25, "RESET(r)", window::width - 210, 5));
  this->m_quit_button =
      std::move(Button(100, 25, "QUIT(q)", window::width - 105, 5));
  this->m_time_progress_bar = std::move(ProgressBar(
      window::width - 220, 5, 100, 25, SDL_Color{91, 140, 252, 255},
      SDL_Color{255, 188, 7, 255}, /*m_reduce_right_to_left=*/true));
}

void Game::update() {
  if (this->is_game_time_over()) {
    this->stop();
    return;
  }
  SDL_Event event;
  if (SDL_PollEvent(&event) != 0) {
    switch (event.type) {
      case SDL_QUIT:
        this->stop();
        return;
        break;
      case SDL_KEYDOWN: {
        switch (event.key.keysym.sym) {
          case SDLK_UP:
            this->m_board.movePlayer(Direction::up);
            break;
          case SDLK_DOWN:
            this->m_board.movePlayer(Direction::down);
            break;
          case SDLK_LEFT:
            this->m_board.movePlayer(Direction::left);
            break;
          case SDLK_RIGHT:
            this->m_board.movePlayer(Direction::right);
            break;
          case SDLK_r:
            this->reset();
            break;
          case SDLK_q:
            this->stop();
            return;
            break;
        }
        break;
      }
      case SDL_MOUSEBUTTONDOWN:
        switch (event.button.button) {
          case SDL_BUTTON_LEFT: {
            int x_pos = event.button.x;
            int y_pos = event.button.y;
            if (this->m_reset_button.is_clicked(x_pos, y_pos)) {
              this->reset();
            } else if (this->m_quit_button.is_clicked(x_pos, y_pos)) {
              this->stop();
            }
            break;
          }
          default:
            break;
        }
        break;
    }
  }
  if (this->m_board.dest_reached) {
    this->stop();
    std::cout << "game over" << std::endl;
    return;
  }
  SDL_RenderClear(this->m_renderer.get());
  if (!this->m_reset_button.draw(this->m_renderer.get())) {
    std::cerr << "Failed to draw reset button, Error:" << SDL_GetError()
              << std::endl;
    this->stop();
    return;
  }
  if (!this->m_quit_button.draw(this->m_renderer.get())) {
    std::cerr << "Failed to draw quit button, Error:" << SDL_GetError()
              << std::endl;
    this->stop();
    return;
  }
  if (!this->m_time_progress_bar.draw(this->m_renderer.get(),
                                      this->m_game_timer.getTimePercent())) {
    std::cerr << "Failed to draw progress bar, Error: " << SDL_GetError();
    return;
  }
  if (!this->m_board.draw(this->m_renderer.get())) {
    std::cerr << "Failed to draw tile map, Error:" << SDL_GetError()
              << std::endl;
    this->stop();
    return;
  }
  SDL_RenderPresent(this->m_renderer.get());
  SDL_UpdateWindowSurface(this->m_window.get());
}

void Game::reset() { this->m_board.reset(); }

[[nodiscard]] bool Game::is_game_time_over() {
  bool time_up = this->m_game_timer.isTimeUp();
  if (time_up) {
    std::cout << "TIME UP!\n";
  }
  return time_up;
}

}  // namespace gem_raider
