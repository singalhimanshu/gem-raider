#include <SDL2/SDL.h>

#include <array>
#include <fstream>
#include <iostream>
#include <string>

#include "gem-raider/board.hpp"
#include "gem-raider/constants.hpp"

namespace const_window = constants::window;
namespace const_player = constants::player;
namespace const_tile = constants::tile;

int main(int argc, char *argv[]) {
  std::cout << "Starting" << std::endl;
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow(
      "Hello World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      const_window::width, const_window::height, 0);
  if (window == nullptr) {
    std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
    return 2;
  }

  SDL_Surface *surface = SDL_GetWindowSurface(window);

  Board board(const_tile::rows, const_tile::cols);
  board.fill();

  SDL_Event event;
  bool is_running = true;

  SDL_Rect player{32, 32, const_player::height, const_player::width};

  while (is_running) {
    if (SDL_PollEvent(&event) != 0) {
      switch (event.type) {
        case SDL_QUIT:
          is_running = false;
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

    if (!board.draw(surface)) {
      std::cerr << "Failed to draw tile map, Error:" << SDL_GetError()
                << std::endl;
      return 3;
    }

    Uint32 player_color = SDL_MapRGB(surface->format, 128, 128, 128);
    SDL_FillRect(surface, &player, player_color);

    SDL_UpdateWindowSurface(window);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
