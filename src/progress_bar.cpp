#include <gem-raider/progress_bar.hpp>

namespace gem_raider {
[[nodiscard]] bool ProgressBar::draw(SDL_Renderer *renderer, float percent) {
  if (percent > 1.f) {
    percent = 1.f;
  } else if (percent < 0.f) {
    percent = 0.f;
  }

  int w = this->m_w;
  if (this->m_reduce_right_to_left) {
    w *= -1;
  }
  SDL_Rect bg_rect = {this->m_x, this->m_y, w, this->m_h};
  if (SDL_SetRenderDrawColor(renderer, this->m_bg_color.r, this->m_bg_color.g,
                             this->m_bg_color.b, this->m_bg_color.a) != 0) {
    std::cerr << "Cannot set render draw color in progress bar, Error: "
              << SDL_GetError() << '\n';
    return false;
  }
  if (SDL_RenderFillRect(renderer, &bg_rect) != 0) {
    std::cerr << "Cannot draw background rect in progress bar, Error: "
              << SDL_GetError() << '\n';
    return false;
  }

  int fg_w = static_cast<int>((float)w * percent);
  SDL_Rect fg_rect = {this->m_x, this->m_y, fg_w, this->m_h};
  if (SDL_SetRenderDrawColor(renderer, this->m_fg_color.r, this->m_fg_color.g,
                             this->m_fg_color.b, this->m_fg_color.a) != 0) {
    std::cerr << "Cannot set render draw color in progress bar, Error: "
              << SDL_GetError() << '\n';
    return false;
  }
  if (SDL_RenderFillRect(renderer, &fg_rect) != 0) {
    std::cerr << "Cannot draw foreground rect in progress bar, Error: "
              << SDL_GetError() << '\n';
    return false;
  }
  return true;
}
}  // namespace gem_raider
