#include <iostream>
#include "controller.h"
#include "game.h"
#include "multiplayer_game.h"
#include "game_mode_enum.h"
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
    MenuEnum::States selection = menu.MenuController();

    if (selection == MenuEnum::PLAY)
    {
      while (true)
      {
        menu.DrawGameModeMenu();
        GameModeEnum::States mode = menu.GameModeMenuController();

        if (mode == GameModeEnum::ONE_PLAYER)
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
        else if (mode == GameModeEnum::TWO_PLAYERS)
        {
          Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
          MultiplayerGame multiplayerGame(kGridWidth, kGridHeight);
          multiplayerGame.Run(renderer, kMsPerFrame);
          std::cout << "Game has terminated successfully!\n";
          return 0;

        }
        else if (mode == GameModeEnum::EXIT)
        {
          break;
        }
      }
    }
    else if (selection == MenuEnum::SCORES)
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
    else if (selection == MenuEnum::EXIT)
    {
      break;
    }
  }
  return 0;
}
