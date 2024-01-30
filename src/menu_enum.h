#ifndef MENU_ENUM_H
#define MENU_ENUM_H


class MenuEnum 
{
public:
    enum States 
    {
        MAIN,
        PLAY,
        SCORES,
        EXIT,
        INVALID
    };

    static States getStateEnum(int n)
    {
        switch (n)
        {
        case 0:
            return MAIN;
            break;
        case 1:
            return PLAY;
            break;
        case 2:
            return SCORES;
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

#endif //MENU_ENUM_H