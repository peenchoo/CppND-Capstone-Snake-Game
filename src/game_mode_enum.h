#ifndef GAME_MODE_ENUM_H
#define GAME_MODE_ENUM_H


class GameModeEnum 
{
public:
    enum States 
    {
        NORMAL,
        TOXIC,
        HARD,
        EXIT,
        INVALID
    };

    static States getStateEnum(int n)
    {
        switch (n)
        {
        case 1:
            return NORMAL;
            break;
        case 2:
            return TOXIC;
            break;
        case 3:
            return HARD;
            break;
        case 4:
            return EXIT;
            break;
        default:
            return INVALID;
            break;
        }
    }
};

#endif //GAME_MODE_ENUM_H