#include <limits>
#include "menu.h"

Menu::Menu() 
{
}

void Menu::DrawMenu()
{
    std::cout << "\033c";
    std::cout << "/----------------- Snake Game ---------------/" << std::endl;
    std::cout << "/----------------- Main Menu ----------------/" << std::endl;
    std::cout << "1. Play Game" << std::endl;
    std::cout << "2. Scores" << std::endl;
    std::cout << "3. Quit" << std::endl;
}

void Menu::DrawGameModeMenu()
{
    std::cout << "" << std::endl;
    std::cout << "/----------------- Game Mode Menu ----------------/" << std::endl;
    std::cout << "1. Normal Mode" << std::endl;
    std::cout << "2. Toxic Food Mode" << std::endl;
    std::cout << "3. Quit" << std::endl;
}

MenuEnum::States Menu::MenuController()
{
    int n;
    while (true) 
    {
        if (std::cin >> n) 
        {
            break;
        } 
        else 
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid Input!\nPlease try again.\n";
        }
    }

    return MenuEnum::getStateEnum(n);
}

GameModeEnum::States Menu::GameModeMenuController()
{
    int n;
    while (true) 
    {
        if (std::cin >> n) 
        {
            break;
        } 
        else 
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid Input!\nPlease try again.\n";
        }
    }

    return GameModeEnum::getStateEnum(n);
}

void Menu::setPlayerName() 
{
    std::cout << "Enter your name: ";
    std::cin >> _playerName;
    
}

std::string Menu::getPlayerName()
{
    return _playerName;
}