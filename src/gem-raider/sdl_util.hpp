#pragma once
#include <iostream>
#include <string>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

namespace gem_raider {
std::string getResPath();
TTF_Font *getFont(const std::string &font_name, int font_size);
}  // namespace gem_raider
