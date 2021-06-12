#include <SDL2/SDL.h>

#include <array>
#include <fstream>
#include <gem-raider/board.hpp>
#include <gem-raider/constants.hpp>
#include <gem-raider/game.hpp>
#include <iostream>
#include <string>

constexpr int fps = 60;

int main(int argc, char *argv[]) {
  gem_raider::Game game;
  game.init("gem-raider");

  Uint32 frame_time = 0;
  Uint32 elapsed = 0;
  game.startGame();
  while (game.is_running()) {
    elapsed = SDL_GetTicks();
    game.update();
    frame_time = SDL_GetTicks() - elapsed;
    if (1000 / fps > frame_time) {
      SDL_Delay((1000 / fps) - frame_time);
    }
  }
  return 0;
}
