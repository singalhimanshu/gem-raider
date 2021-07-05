#include <gtest/gtest.h>

#include <gem-raider/button.hpp>
#include <string>

namespace gem_raider {
namespace {
Button getTestButton(int x_pos, int y_pos, int width, int height) {
  std::string text = "TEST BUTTON";
  SDL_Color fg_color{.r = 255, .g = 255, .b = 255, .a = 255};
  SDL_Color bg_color{.r = 0, .g = 0, .b = 0, .a = 255};
  return Button(x_pos, y_pos, width, height, text, std::move(fg_color),
                std::move(bg_color));
}

TEST(test_button, test_button_click) {
  {
    int x_pos = 0, y_pos = 0;
    int width = 10, height = 10;
    Button test_button = getTestButton(x_pos, y_pos, width, height);
    int x_click_pos = x_pos + 1, y_click_pos = y_pos + 1;
    EXPECT_TRUE(test_button.is_clicked(x_click_pos, y_click_pos));
  }

  {
    int x_pos = 0, y_pos = 0;
    int width = 10, height = 10;
    Button test_button = getTestButton(x_pos, y_pos, width, height);
    int x_click_pos = x_pos + width + 1, y_click_pos = y_pos + height + 1;
    EXPECT_FALSE(test_button.is_clicked(x_click_pos, y_click_pos));
  }
}
}  // namespace
}  // namespace gem_raider
