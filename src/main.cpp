#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "menu_enum.h"
#include "menu.h"
#include "scores_enum.h"
#include "scores.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Scores scores;
  Menu menu;
  while(true)
  {
    menu.DrawMenu();
    MenuEnum::States mode = menu.MenuController();

    if (mode == MenuEnum::PLAY)
    {
      menu.setPlayerName();
      Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
      Controller controller;
      Game game(kGridWidth, kGridHeight);
      game.Run(controller, &renderer, kMsPerFrame);
      scores.addScore(menu.getPlayerName(),game.GetScore());
      std::cout << "Game has terminated successfully!\n";
      std::cout << "Score: " << game.GetScore() << "\n";
      std::cout << "Size: " << game.GetSize() << "\n";
      return 0;
    }
    else if (mode == MenuEnum::SCORES)
    {
      while(true)
      {
        scores.ScoreMenu();
        ScoresEnum::States type = scores.ScoresMenuController();

        if (type == ScoresEnum::HIGH_SCORES)
        {
          scores.showHighScores(10);
        }
        else if (type == ScoresEnum::RECENT_SCORES)
        {
          scores.showRecentScores(10);
        }
        else if (type == ScoresEnum::EXIT)
        {
          break;
        }
      }
    }
    else if (mode == MenuEnum::EXIT)
    {
      break;
    }
  }
  return 0;
}