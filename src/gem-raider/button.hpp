#pragma once
#include <string>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

namespace gem_raider {
class Button {
 public:
  explicit Button() = default;
  Button(int x_pos, int y_pos, int width, int height, const std::string &text,
         SDL_Color &&fg_color, SDL_Color &&bg_color)
      : m_x_pos(x_pos),
        m_y_pos(y_pos),
        m_width(width),
        m_height(height),
        m_text(text),
        m_fg_color(fg_color),
        m_bg_color(bg_color) {}
  virtual ~Button() = default;

  Button(const Button &button)
      : m_x_pos(button.m_x_pos),
        m_y_pos(button.m_y_pos),
        m_width(button.m_width),
        m_height(button.m_height),
        m_text(button.m_text),
        m_fg_color(button.m_fg_color),
        m_bg_color(button.m_bg_color) {}
  Button &operator=(const Button &button) {
    if (this != &button) {
      this->m_x_pos = button.m_x_pos;
      this->m_y_pos = button.m_y_pos;
      this->m_width = button.m_width;
      this->m_height = button.m_height;
      this->m_text = button.m_text;
      this->m_fg_color = button.m_fg_color;
      this->m_bg_color = button.m_bg_color;
    }
    return *this;
  }

  Button(Button &&button) noexcept
      : m_x_pos(std::move(button.m_x_pos)),
        m_y_pos(std::move(button.m_y_pos)),
        m_width(std::move(button.m_width)),
        m_height(std::move(button.m_height)),
        m_text(std::move(button.m_text)),
        m_fg_color(std::move(button.m_fg_color)),
        m_bg_color(std::move(button.m_bg_color)) {}
  Button &operator=(Button &&button) noexcept {
    if (this != &button) {
      this->m_x_pos = std::move(button.m_x_pos);
      this->m_y_pos = std::move(button.m_y_pos);
      this->m_width = std::move(button.m_width);
      this->m_height = std::move(button.m_height);
      this->m_text = std::move(button.m_text);
      this->m_fg_color = std::move(button.m_fg_color);
      this->m_bg_color = std::move(button.m_bg_color);
    }
    return *this;
  }

  [[nodiscard]] bool draw(SDL_Renderer *renderer, TTF_Font *font);
  bool is_clicked(int x_click_pos, int y_click_pos) {
    return ((x_click_pos >= this->m_x_pos) && (y_click_pos >= this->m_y_pos) &&
            (x_click_pos <= (this->m_x_pos + this->m_width)) &&
            (y_click_pos <= (this->m_y_pos + this->m_height)));
  }

 private:
  [[nodiscard]] SDL_Texture *m_render_text(SDL_Renderer *renderer,
                                           TTF_Font *font);
  int m_x_pos{0};
  int m_y_pos{0};
  int m_width{50};
  int m_height{30};
  std::string m_text{"BUTTON"};
  SDL_Color m_fg_color;
  SDL_Color m_bg_color;
};

}  // namespace gem_raider
