#include <gem-raider/spy_timer.hpp>
#include <limits>

namespace gem_raider {
void SpyTimer::start() { this->m_start_time = getTicks(); }

Uint32 SpyTimer::getTicks() const { return current_ticks; }

Uint32 SpyTimer::getTimeElapsed() const {
  return this->getTicks() - m_start_time;
}

float SpyTimer::getTimePercent() const { return 0.f; }

[[nodiscard]] bool SpyTimer::isTimeUp() const {
  return getTimeElapsed() >= this->m_end_time;
}
}  // namespace gem_raider
