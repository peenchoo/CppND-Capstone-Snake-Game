#ifndef GAME_H
#define GAME_H

#include <random>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, bool isToxicFoodMode, bool isHardModeActive);
  void Run(Controller const &controller, Renderer *renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  void TriggerPause();
  bool isToxicFood;
  

 private:
  Snake snake;
  SDL_Point food;
  bool _paused;
  static void TimerThread(bool *toxicFood);
  static void HardModeTimer(Game& gameInstance);
  std::mutex mutex;
  std::condition_variable condition_var;
  bool _isToxicFoodMode;
  bool _isHardModeActive;
  bool _isHardModeTimerActive;

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