#include <gem-raider/game_timer.hpp>

namespace gem_raider {
void GameTimer::start() { this->m_start_time = this->getTicks(); }

Uint32 GameTimer::getTicks() const { return SDL_GetTicks(); }

Uint32 GameTimer::getTimeElapsed() const {
  return this->getTicks() - this->m_start_time;
}

float GameTimer::getTimePercent() const {
  return this->getTimeElapsed() / (float)this->m_end_time;
}

[[nodiscard]] bool GameTimer::isTimeUp() const {
  return this->getTimeElapsed() >= this->m_end_time;
}
}  // namespace gem_raider
