#include <gem-raider/button.hpp>
#include <gem-raider/game.hpp>
#include <gem-raider/sdl_util.hpp>

namespace gem_raider {
[[nodiscard]] bool Button::draw(SDL_Renderer *renderer, TTF_Font *font) {
  if (SDL_SetRenderDrawColor(renderer, this->m_bg_color.r, this->m_bg_color.g,
                             this->m_bg_color.b, this->m_bg_color.a) != 0) {
    std::cerr << "Unable to set render draw color, ERROR: " << SDL_GetError()
              << '\n';
    return false;
  }
  SDL_Rect button_rect{this->m_x_pos, this->m_y_pos, this->m_width,
                       this->m_height};
  if (SDL_RenderFillRect(renderer, &button_rect) < 0) {
    return false;
  }
  SDL_Texture *font_texture = this->m_render_text(renderer, font);
  if (font_texture == nullptr) {
    return false;
  }
  SDL_Rect font_rect;
  font_rect.x = this->m_x_pos + 10;
  font_rect.y = this->m_y_pos + 5;
  SDL_QueryTexture(font_texture, nullptr, nullptr, &font_rect.w, &font_rect.h);
  if (SDL_RenderCopy(renderer, font_texture, nullptr, &font_rect) < 0) {
    return false;
  }
  return true;
}

[[nodiscard]] SDL_Texture *Button::m_render_text(SDL_Renderer *renderer,
                                                 TTF_Font *font) {
  std::string font_path = getResPath() + "dpcomic.ttf";
  if (font == nullptr) {
    std::cerr << "Cannot load font, Error: " << SDL_GetError() << std::endl;
    return nullptr;
  }
  SDL_Color font_color{.r = this->m_fg_color.r,
                       .g = this->m_fg_color.g,
                       .b = this->m_fg_color.b,
                       .a = this->m_fg_color.a};
  SDL_Surface *font_surface =
      TTF_RenderText_Blended(font, this->m_text.c_str(), font_color);
  if (font_surface == nullptr) {
    TTF_CloseFont(font);
    std::cerr << "Cannot load font surface, Error: " << SDL_GetError()
              << std::endl;
    return nullptr;
  }
  // TODO(singalhimanshu): Center text to button
  SDL_Texture *font_texture =
      SDL_CreateTextureFromSurface(renderer, font_surface);
  if (font_texture == nullptr) {
    TTF_CloseFont(font);
    SDL_FreeSurface(font_surface);
    std::cerr << "Cannot load font texture, Error: " << SDL_GetError()
              << std::endl;
    return nullptr;
  }
  TTF_CloseFont(font);
  SDL_FreeSurface(font_surface);
  return font_texture;
}

}  // namespace gem_raider
