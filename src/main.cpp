#include <SDL2/SDL.h>

#include <array>
#include <fstream>
#include <gem-raider/board.hpp>
#include <gem-raider/constants.hpp>
#include <gem-raider/game.hpp>
#include <gem-raider/game_timer.hpp>
#include <iostream>
#include <memory>
#include <string>

constexpr int fps = 60;

int main(int argc, char *argv[]) {
  Uint32 game_time = 60000;
  gem_raider::GameTimer game_timer(game_time);
  gem_raider::Game game(game_timer);
  game.init("gem-raider");

  Uint32 frame_time = 0;
  Uint32 elapsed = 0;
  game.start();
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
