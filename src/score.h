#ifndef SCORE_H
#define SCORE_H

#include <string>

class Score
{
public:
    std::string name;
    int score;

    bool operator<(const Score& other) const 
    {
        return score > other.score;
    }
};

#endif //SCORE_H