#ifndef SCORES_H
#define SCORES_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "score.h"
#include "scores_enum.h"

class Scores
{

public:
    Scores();

    void addScore(const std::string& name, int score);
    void showHighScores(int amount);
    void showRecentScores(int amount);
    void ScoreMenu();
    ScoresEnum::States ScoresMenuController();

private:
    std::vector<Score> _scores;
    const std::string scoresFile = "scores.txt";

    void loadScores();
    void saveScores();

};

#endif //SCORES_H