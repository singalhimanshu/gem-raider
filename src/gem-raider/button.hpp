#pragma once
#include <string>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

namespace gem_raider {
class Button {
 public:
  explicit Button() = default;
  Button(uint16_t width, uint16_t height, const std::string &text,
         uint16_t x_pos, uint16_t y_pos)
      : m_height(height),
        m_width(width),
        m_text(text),
        m_x_pos(x_pos),
        m_y_pos(y_pos) {}
  virtual ~Button() = default;

  Button(const Button &button)
      : m_width(button.m_width),
        m_height(button.m_height),
        m_text(button.m_text),
        m_x_pos(button.m_x_pos),
        m_y_pos(button.m_y_pos) {}
  Button &operator=(const Button &button) {
    if (this != &button) {
      this->m_width = button.m_width;
      this->m_height = button.m_height;
      this->m_text = button.m_text;
      this->m_x_pos = button.m_x_pos;
      this->m_y_pos = button.m_y_pos;
    }
    return *this;
  }

  Button(Button &&button)
      : m_width(std::move(button.m_width)),
        m_height(std::move(button.m_height)),
        m_text(std::move(button.m_text)),
        m_x_pos(std::move(button.m_x_pos)),
        m_y_pos(std::move(button.m_y_pos)) {}
  Button &operator=(Button &&button) {
    if (this != &button) {
      this->m_width = std::move(button.m_width);
      this->m_height = std::move(button.m_height);
      this->m_text = std::move(button.m_text);
      this->m_x_pos = std::move(button.m_x_pos);
      this->m_y_pos = std::move(button.m_y_pos);
    }
    return *this;
  }

  [[nodiscard]] bool draw(SDL_Renderer *renderer);
  bool is_clicked(int x_click_pos, int y_click_pos) {
    return ((x_click_pos >= this->m_x_pos) && (y_click_pos >= this->m_y_pos) &&
            (x_click_pos <= (this->m_x_pos + this->m_width)) &&
            (y_click_pos <= (this->m_y_pos + this->m_height)));
  }

 private:
  [[nodiscard]] SDL_Texture *m_render_text(SDL_Renderer *renderer);
  uint16_t m_width{50};
  uint16_t m_height{30};
  std::string m_text{"BUTTON"};
  uint16_t m_x_pos{0};
  uint16_t m_y_pos{0};
};

}  // namespace gem_raider
