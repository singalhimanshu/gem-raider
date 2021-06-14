#include <gem-raider/button.hpp>
#include <gem-raider/game.hpp>
#include <gem-raider/sdl_util.hpp>

namespace gem_raider {
[[nodiscard]] bool Button::draw(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
  SDL_Rect button_rect{this->m_x_pos, this->m_y_pos, this->m_width,
                       this->m_height};
  if (SDL_RenderFillRect(renderer, &button_rect) < 0) {
    return false;
  }
  SDL_Texture *font_texture = this->m_render_text(renderer);
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

[[nodiscard]] SDL_Texture *Button::m_render_text(SDL_Renderer *renderer) {
  std::string font_path = getResPath() + "dpcomic.ttf";
  // TODO(singalhimanshu): Take font size as input
  TTF_Font *font = TTF_OpenFont(font_path.c_str(), 20);
  if (font == nullptr) {
    std::cerr << "Cannot load font, Error: " << SDL_GetError() << std::endl;
    return nullptr;
  }
  SDL_Color font_color{.r = 0, .g = 0, .b = 0, .a = 255};
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
