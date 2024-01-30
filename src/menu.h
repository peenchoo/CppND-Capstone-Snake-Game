#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include "menu_enum.h"
#include "game_mode_enum.h"

class Menu 
{
public:
    Menu();

    void DrawMenu();
    void DrawGameModeMenu();
    MenuEnum::States MenuController();
    GameModeEnum::States GameModeMenuController();
    void setPlayerName();
    std::string getPlayerName();

private:
    std::string _playerName;

};

#endif //MENU_H