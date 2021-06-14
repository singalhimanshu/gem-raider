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

  ProgressBar(const ProgressBar &pb) noexcept
      : m_x(pb.m_x),
        m_y(pb.m_y),
        m_w(pb.m_w),
        m_h(pb.m_h),
        m_bg_color(pb.m_bg_color),
        m_fg_color(pb.m_fg_color),
        m_reduce_right_to_left(pb.m_reduce_right_to_left) {}
  ProgressBar &operator=(const ProgressBar &pb) noexcept {
    if (&pb != this) {
      this->m_x = pb.m_x;
      this->m_y = pb.m_y;
      this->m_w = pb.m_w;
      this->m_h = pb.m_h;
      this->m_bg_color = pb.m_bg_color;
      this->m_fg_color = pb.m_fg_color;
      this->m_reduce_right_to_left = pb.m_reduce_right_to_left;
    }
    return *this;
  }

  ProgressBar(ProgressBar &&pb) noexcept
      : m_x(std::move(pb.m_x)),
        m_y(std::move(pb.m_y)),
        m_w(std::move(pb.m_w)),
        m_h(std::move(pb.m_h)),
        m_bg_color(std::move(pb.m_bg_color)),
        m_fg_color(std::move(pb.m_fg_color)),
        m_reduce_right_to_left(pb.m_reduce_right_to_left) {}
  ProgressBar &operator=(ProgressBar &&pb) noexcept {
    if (&pb != this) {
      this->m_x = std::move(pb.m_x);
      this->m_y = std::move(pb.m_y);
      this->m_w = std::move(pb.m_w);
      this->m_h = std::move(pb.m_h);
      this->m_bg_color = std::move(pb.m_bg_color);
      this->m_fg_color = std::move(pb.m_fg_color);
      this->m_reduce_right_to_left = std::move(pb.m_reduce_right_to_left);
    }
    return *this;
  }

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
