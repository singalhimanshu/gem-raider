#include <SDL2/SDL.h>
#include <gtest/gtest.h>

#include <gem-raider/game.hpp>
#include <gem-raider/spy_timer.hpp>

namespace gem_raider {
namespace {
TEST(test_game, game_over_when_time_over) {
  {
    Uint32 game_time = 60000;
    SpyTimer spy_timer(game_time);
    spy_timer.current_ticks = game_time + 1;
    Game game(spy_timer);
    game.start();
    EXPECT_FALSE(game.is_running());
  }
}

TEST(test_game, game_not_over_when_time_not_over) {
  {
    Uint32 game_time = 60000;
    SpyTimer spy_timer(game_time);
    spy_timer.current_ticks = game_time - 1;
    Game game(spy_timer);
    game.start();
    EXPECT_TRUE(game.is_running());
  }
}
}  // namespace
}  // namespace gem_raider
