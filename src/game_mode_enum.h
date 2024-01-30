#ifndef GAME_MODE_ENUM_H
#define GAME_MODE_ENUM_H


class GameModeEnum 
{
public:
    enum States 
    {
        ONE_PLAYER,
        TWO_PLAYERS,
        EXIT,
        INVALID
    };

    static States getStateEnum(int n)
    {
        switch (n)
        {
        case 1:
            return ONE_PLAYER;
            break;
        case 2:
            return TWO_PLAYERS;
            break;
        case 3:
            return EXIT;
            break;
        default:
            return INVALID;
            break;
        }
    }
};

#endif //GAME_MODE_ENUM_H