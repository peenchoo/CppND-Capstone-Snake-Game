#ifndef SCORES_ENUM_H
#define SCORES_ENUM_H


class ScoresEnum 
{
public:
    enum States 
    {
        HIGH_SCORES,
        RECENT_SCORES,
        EXIT,
        INVALID
    };

    static States getStateEnum(int n)
    {
        switch (n)
        {
        case 1:
            return HIGH_SCORES;
            break;
        case 2:
            return RECENT_SCORES;
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

#endif //SCORES_ENUM_H