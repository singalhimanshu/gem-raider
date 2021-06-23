#include <gtest/gtest.h>

#include <gem-raider/button.hpp>
#include <sdl_util_test.cpp>
#include <string>

namespace gem_raider {
namespace {
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
