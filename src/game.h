#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, bool isToxicFoodMode);
  void Run(Controller const &controller, Renderer *renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  void TriggerPause();
  bool isToxicFood;
  bool isToxicFoodMode;

 private:
  Snake snake;
  SDL_Point food;
  bool _paused;
  static void TimerThread(bool *toxicFood);
  


  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void Update(Renderer *renderer);
  void Pause();
  void Resume();

protected:
  bool wall;
};

#endif