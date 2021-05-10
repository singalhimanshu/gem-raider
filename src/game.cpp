#include "gem-raider/game.hpp"

#include <iostream>

#include "gem-raider/constants.hpp"

namespace const_window = constants::window;
namespace const_tile = constants::tile;
namespace const_player = constants::player;

void Game::init(const char *title) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
    return;
  }
  this->m_window.reset(
      SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       const_window::width, const_window::height, 0));
  if (!this->m_window) {
    std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
    return;
  }
  this->m_surface.reset(SDL_GetWindowSurface(this->m_window.get()));
  if (!this->m_surface) {
    std::cerr << "Failed to create SDL surface: " << SDL_GetError()
              << std::endl;
    return;
  }
  this->m_board.init(const_tile::rows, const_tile::cols);
  this->m_board.fill();
  this->m_player = std::move(tile::Player(1, 1));
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
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
          case SDLK_UP:
            this->m_player.move(tile::Direction::up, this->m_board);
            break;
          case SDLK_DOWN:
            this->m_player.move(tile::Direction::down, this->m_board);
            break;
          case SDLK_LEFT:
            this->m_player.move(tile::Direction::left, this->m_board);
            break;
          case SDLK_RIGHT:
            this->m_player.move(tile::Direction::right, this->m_board);
            break;
        }
    }
  }
  if (!this->m_board.draw(this->m_surface.get())) {
    std::cerr << "Failed to draw tile map, Error:" << SDL_GetError()
              << std::endl;
    return;
  }
  if (!this->m_player.draw(this->m_surface.get())) {
    std::cerr << "Failed to draw player, Error:" << SDL_GetError() << std::endl;
    return;
  }

  SDL_UpdateWindowSurface(this->m_window.get());
}
