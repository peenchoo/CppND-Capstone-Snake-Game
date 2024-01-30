#include "multiplayer_game.h"
#include <iostream>
#include <future>
#include <mutex>
#include <condition_variable>
#include "SDL.h"

MultiplayerGame::MultiplayerGame(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
	    snake2(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height)), 
      controllerPlayer1(),
      controllerPlayer2()
{
  snake.setHeadPosition(random_w(engine),random_h(engine));
  snake2.setHeadPosition(random_w(engine),random_h(engine));
  PlaceFood();
}

void MultiplayerGame::Run(Renderer &renderer, std::size_t target_frame_duration) { 
	  Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    bool running = true;


    std::mutex inputMutex;
    std::condition_variable inputCV;

    auto inputFunctionArrows = [&](Controller &controller, Snake &snake) 
    {
      while (running) {
        std::unique_lock<std::mutex> lock(inputMutex);
        inputCV.wait(lock);

        controller.HandleMultiplayerArrowsInput(running, snake);

        lock.unlock();
      }
    };

    auto inputFunctionLetters = [&](Controller &controller, Snake &snake) 
    {
      while (running) {
        std::unique_lock<std::mutex> lock(inputMutex);
        inputCV.wait(lock);

        controller.HandleMultiplayerLettersInput(running, snake);

        lock.unlock();
      }
    };

    std::future<void> inputPlayer1Future = std::async(std::launch::async, inputFunctionArrows, std::ref(controllerPlayer1), std::ref(snake));
    std::future<void> inputPlayer2Future = std::async(std::launch::async, inputFunctionLetters, std::ref(controllerPlayer2), std::ref(snake2));

  	
    while (running) {
      frame_start = SDL_GetTicks();

      std::lock_guard<std::mutex> lock(inputMutex);
      inputCV.notify_all();
    
      Update();
      renderer.RenderMultiPlayer(snake, snake2, food);


      frame_end = SDL_GetTicks();

      // Keep track of how long each loop through the input/update/render cycle
      // takes.
      frame_count++;
      frame_duration = frame_end - frame_start;

      // After every second, update the window title.
      if (frame_end - title_timestamp >= 1000) {
        renderer.UpdateWindowTitle(score, frame_count);
        frame_count = 0;
        title_timestamp = frame_end;
      }

      // If the time for this frame is too small (i.e. frame_duration is
      // smaller than the target ms_per_frame), delay the loop to
      // achieve the correct frame rate.
      if (frame_duration < target_frame_duration) {
        SDL_Delay(target_frame_duration - frame_duration);
      }
  	}  
}

void MultiplayerGame::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y) && !snake2.SnakeCell(x,y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void MultiplayerGame::Update() {
  if (!snake.alive || !snake2.alive) return;


  snake.Update(snake2);
  snake2.Update(snake);


  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  int new_x_player2 = static_cast<int>(snake2.head_x);
  int new_y_player2 = static_cast<int>(snake2.head_y);
  
  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
  
  if(food.x == new_x_player2 && food.y == new_y_player2)
  {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake2.GrowBody();
    snake2.speed += 0.02; 
  }
  
}

int MultiplayerGame::GetScore() const { return score; }
int MultiplayerGame::GetSize() const { return snake.size; }