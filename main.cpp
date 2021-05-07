#include <SDL2/SDL.h>
#include <array>
#include <fstream>
#include <iostream>
#include <string>

constexpr int WINDOW_HEIGHT = 640;
constexpr int WINDOW_WIDTH = 480;
constexpr int PLAYER_HEIGHT = 32;
constexpr int PLAYER_WIDTH = 32;
constexpr int TILE_ROWS = WINDOW_HEIGHT / PLAYER_HEIGHT;
constexpr int TILE_COLS = WINDOW_WIDTH / PLAYER_WIDTH;
constexpr int TILE_MAP_SIZE = TILE_ROWS * TILE_COLS;

[[nodiscard]] std::array<int, TILE_MAP_SIZE> loadTileMap() {
  std::ifstream tile_map_file("tile_map.txt");
  std::array<int, TILE_MAP_SIZE> tile_map;
  if (tile_map_file.is_open()) {
    int i = 0;
    int tile_id = 0;
    while (tile_map_file >> tile_id) {
      tile_map[i] = tile_id;
      i++;
    }
  }
  tile_map_file.close();
  return tile_map;
}

[[nodiscard]] bool drawTileMap(SDL_Surface *surface,
                               const std::array<int, TILE_MAP_SIZE> &tile_map) {
  int tile_x_pos = 0, tile_y_pos = 0;
  int i = 0;
  for (int r = 0; r < TILE_ROWS; r++) {
    for (int c = 0; c < TILE_COLS; c++) {
      SDL_Rect tile_rect =
          SDL_Rect{tile_x_pos, tile_y_pos, PLAYER_WIDTH, PLAYER_HEIGHT};
      Uint32 tile_color = SDL_MapRGBA(surface->format, 0, 0, 0, 0);
      switch (tile_map[TILE_COLS * r + c]) {
      // moveable space
      case 1:
        tile_color = SDL_MapRGB(surface->format, 0, 0, 0);
        break;
      // rocks
      case 2:
        tile_color = SDL_MapRGB(surface->format, 181, 101, 29);
        break;
      // gem
      case 3:
        tile_color = SDL_MapRGB(surface->format, 0, 255, 255);
        break;
      // destination
      case 4:
        tile_color = SDL_MapRGB(surface->format, 25, 77, 0);
        break;
      // eatable  (or something IDK)
      case 5:
        tile_color = SDL_MapRGB(surface->format, 255, 243, 138);
        break;
      }
      if (SDL_FillRect(surface, &tile_rect, tile_color) < 0) {
        return false;
      }
      i++;
      tile_x_pos += PLAYER_WIDTH;
    }
    tile_x_pos = 0;
    tile_y_pos += PLAYER_HEIGHT;
  }
  return true;
}

void printTileMap(const std::array<int, TILE_MAP_SIZE> &tile_map) {
  for (int r = 0; r < TILE_ROWS; r++) {
    for (int c = 0; c < TILE_COLS; c++) {
      std::cout << tile_map[r * TILE_COLS + c] << ' ';
    }
    std::cout << std::endl;
  }
}

int main(int argc, char *argv[]) {
  std::cout << "Starting" << std::endl;
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
    return 1;
  }

  SDL_Window *window =
      SDL_CreateWindow("Hello World", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  if (window == nullptr) {
    std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
    return 2;
  }

  SDL_Surface *surface = SDL_GetWindowSurface(window);

  std::array<int, TILE_MAP_SIZE> tile_map = loadTileMap();
  printTileMap(tile_map);

  SDL_Event event;
  bool is_running = true;

  SDL_Rect player{32, 32, PLAYER_HEIGHT, PLAYER_WIDTH};

  while (is_running) {
    if (SDL_PollEvent(&event) != 0) {
      switch (event.type) {
      case SDL_QUIT:
        is_running = false;
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_UP:
          player.y = std::max(0, player.y - PLAYER_HEIGHT);
          break;
        case SDLK_DOWN:
          if (player.y + PLAYER_HEIGHT < WINDOW_HEIGHT) {
            player.y += PLAYER_HEIGHT;
          }
          break;
        case SDLK_LEFT:
          player.x = std::max(0, player.x - PLAYER_WIDTH);
          break;
        case SDLK_RIGHT:
          if (player.x + PLAYER_WIDTH < WINDOW_WIDTH) {
            player.x += PLAYER_WIDTH;
          }
          break;
        }
      }
    }

    if (!drawTileMap(surface, tile_map)) {
      std::cerr << "Failed to draw tile map, Error:" << SDL_GetError()
                << std::endl;
      return 3;
    }

    Uint32 player_color = SDL_MapRGB(surface->format, 128, 128, 128);
    SDL_FillRect(surface, &player, player_color);

    SDL_UpdateWindowSurface(window);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
