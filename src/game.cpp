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
  this->m_is_running = true;
}

void Game::update() {
  SDL_Rect player{32, 32, const_player::height, const_player::width};
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
            player.y = std::max(0, player.y - const_player::height);
            break;
          case SDLK_DOWN:
            if (player.y + const_player::height < const_window::height) {
              player.y += const_player::height;
            }
            break;
          case SDLK_LEFT:
            player.x = std::max(0, player.x - const_player::width);
            break;
          case SDLK_RIGHT:
            if (player.x + const_player::width < const_window::width) {
              player.x += const_player::width;
            }
            break;
        }
    }
  }
  if (!this->m_board.draw(this->m_surface.get())) {
    std::cerr << "Failed to draw tile map, Error:" << SDL_GetError()
              << std::endl;
    return;
  }
  Uint32 player_color =
      SDL_MapRGB(this->m_surface.get()->format, 128, 128, 128);
  SDL_FillRect(this->m_surface.get(), &player, player_color);

  SDL_UpdateWindowSurface(this->m_window.get());
}
