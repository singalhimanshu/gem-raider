#include <gem-raider/sdl_util.hpp>

namespace gem_raider {
std::string getResPath() {
  static std::string res_path;
  if (!res_path.empty()) {
    return res_path;
  }
  char *base_path = SDL_GetBasePath();
  if (base_path == nullptr) {
    std::cerr << "Cannot get base path, Error: " << SDL_GetError() << std::endl;
    return res_path;
  }
  res_path = base_path;
  SDL_free(base_path);
  res_path += "res/";
  return res_path;
}
}  // namespace gem_raider
