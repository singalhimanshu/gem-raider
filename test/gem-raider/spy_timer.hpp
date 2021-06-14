#pragma once
#include <SDL2/SDL.h>

#include <gem-raider/timer.hpp>

namespace gem_raider {
class SpyTimer : public Timer {
 public:
  SpyTimer(Uint32 end_time) : Timer{end_time} {}
  Uint32 current_ticks{0};

  void start() override;
  Uint32 getTicks() const override;
  Uint32 getTimeElapsed() const override;
  float getTimePercent() const override;
  [[nodiscard]] bool isTimeUp() const override;
};
}  // namespace gem_raider
