#pragma once
#include <SDL2/SDL.h>

#include "timer.hpp"

namespace gem_raider {
class GameTimer : public Timer {
 public:
  explicit GameTimer(Uint32 end_time) : Timer{end_time} {}
  ~GameTimer() = default;

  GameTimer(const GameTimer &game_timer) = default;
  GameTimer &operator=(const GameTimer &game_timer) = default;

  GameTimer(const GameTimer &&game_timer) = default;
  GameTimer &operator=(GameTimer &&game_timer) = default;

  void start() override;
  Uint32 getTicks() const override;
  Uint32 getTimeElapsed() const override;
  float getTimePercent() const override;
  [[nodiscard]] bool isTimeUp() const override;
};
}  // namespace gem_raider
