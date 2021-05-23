#include "gem-raider/game.hpp"

#include <iostream>

#include "gem-raider/constants.hpp"

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
  this->m_board.init(tile::rows, tile::cols);
  this->m_board.fill();
  this->m_player = std::move(Player(1, 1));
  this->m_reset_button =
      std::move(Button(100, 30, "RESET(r)", window::width - 100, 0));
  this->m_is_running = true;
}

void Game::update() {
  SDL_Event event;
  if (SDL_PollEvent(&event) != 0) {
    switch (event.type) {
      case SDL_QUIT:
        this->m_is_running = false;
        return;
        break;
      case SDL_KEYDOWN: {
        switch (event.key.keysym.sym) {
          case SDLK_UP:
            this->m_player.move(Direction::up, this->m_board);
            break;
          case SDLK_DOWN:
            this->m_player.move(Direction::down, this->m_board);
            break;
          case SDLK_LEFT:
            this->m_player.move(Direction::left, this->m_board);
            break;
          case SDLK_RIGHT:
            this->m_player.move(Direction::right, this->m_board);
            break;
          case SDLK_r:
            this->reset();
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
    this->m_is_running = false;
    std::cout << "game over" << std::endl;
    return;
  }
  SDL_RenderClear(this->m_renderer.get());
  if (!this->m_reset_button.draw(this->m_renderer.get())) {
    std::cerr << "Failed to draw reset button, Error:" << SDL_GetError()
              << std::endl;
    this->m_is_running = false;
    return;
  }
  if (!this->m_board.draw(this->m_renderer.get())) {
    std::cerr << "Failed to draw tile map, Error:" << SDL_GetError()
              << std::endl;
    this->m_is_running = false;
    return;
  }
  if (!this->m_player.draw(this->m_renderer.get())) {
    std::cerr << "Failed to draw player, Error:" << SDL_GetError() << std::endl;
    this->m_is_running = false;
    return;
  }
  SDL_RenderPresent(this->m_renderer.get());
  SDL_UpdateWindowSurface(this->m_window.get());
}

void Game::reset() {
  this->m_board.reset();
  this->m_player.reset();
}

}  // namespace gem_raider
