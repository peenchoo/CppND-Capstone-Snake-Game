#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height, int *score)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2),
        _score(score) {}

  void Update();
  void Update(Snake secondSnake);

  void GrowBody();
  bool SnakeCell(int x, int y);
  void setHeadPosition(float x, float y);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell, Snake secondSnake);

  bool growing{false};
  int grid_width;
  int grid_height;
  int *_score;
};

#endif