#pragma once
#include <SDL2/SDL.h>

#include <iostream>

namespace gem_raider {
class ProgressBar {
 public:
  explicit ProgressBar() = default;
  explicit ProgressBar(int x, int y, int w, int h, SDL_Color bg_color,
                       SDL_Color fg_color, bool reduce_right_to_left)
      : m_x(x),
        m_y(y),
        m_w(w),
        m_h(h),
        m_bg_color(bg_color),
        m_fg_color(fg_color),
        m_reduce_right_to_left(reduce_right_to_left) {}
  ~ProgressBar() = default;

  ProgressBar(const ProgressBar &pb) noexcept = default;
  ProgressBar &operator=(const ProgressBar &pb) noexcept = default;

  ProgressBar(ProgressBar &&pb) noexcept = default;
  ProgressBar &operator=(ProgressBar &&pb) noexcept = default;

  [[nodiscard]] bool draw(SDL_Renderer *renderer, float percent);

 private:
  int m_x;
  int m_y;
  int m_w;
  int m_h;
  SDL_Color m_bg_color;
  SDL_Color m_fg_color;
  bool m_reduce_right_to_left;
};
}  // namespace gem_raider
