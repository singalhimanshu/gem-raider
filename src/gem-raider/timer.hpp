#pragma once
#include <SDL2/SDL.h>

namespace gem_raider {
class Timer {
 public:
  explicit Timer() = default;
  explicit Timer(Uint32 end_time) : m_end_time(end_time) {}
  virtual ~Timer() = default;

  Timer(const Timer &timer) = default;
  Timer &operator=(const Timer &timer) noexcept {
    if (this != &timer) {
      this->m_start_time = timer.m_start_time;
      this->m_end_time = timer.m_end_time;
    }
    return *this;
  }

  Timer(Timer &&timer) = default;
  Timer &operator=(Timer &&timer) noexcept {
    if (this != &timer) {
      this->m_start_time = std::move(timer.m_start_time);
      this->m_end_time = std::move(timer.m_end_time);
    }
    return *this;
  }

  virtual void start() = 0;
  virtual Uint32 getTicks() const = 0;
  virtual Uint32 getTimeElapsed() const = 0;
  virtual float getTimePercent() const = 0;
  [[nodiscard]] virtual bool isTimeUp() const = 0;

 protected:
  Uint32 m_start_time{0};
  Uint32 m_end_time{0};
};
}  // namespace gem_raider
