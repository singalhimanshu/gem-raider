#include <SDL2/SDL.h>

#include <array>
#include <fstream>
#include <iostream>
#include <string>

#include "gem-raider/board.hpp"
#include "gem-raider/constants.hpp"
#include "gem-raider/game.hpp"

int main(int argc, char *argv[]) {
  Game game;
  game.init("gem-raider");

  while (game.is_running()) {
    game.update();
  }

  SDL_Quit();
  return 0;
}
