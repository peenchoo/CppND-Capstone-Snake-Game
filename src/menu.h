#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include "menu_enum.h"

class Menu 
{
public:
    Menu();

    void DrawMenu();
    MenuEnum::States MenuController();
    void setPlayerName();
    std::string getPlayerName();

private:
    std::string _playerName;

};

#endif //MENU_H