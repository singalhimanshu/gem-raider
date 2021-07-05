#include <gem-raider/button.hpp>
#include <string>

namespace gem_raider {
Button getTestButton(int x_pos, int y_pos, int width, int height) {
  std::string text = "TEST BUTTON";
  SDL_Color fg_color{.r = 255, .g = 255, .b = 255, .a = 255};
  SDL_Color bg_color{.r = 0, .g = 0, .b = 0, .a = 255};
  return Button(x_pos, y_pos, width, height, text, std::move(fg_color),
                std::move(bg_color));
}  // namespace
}  // namespace gem_raider
