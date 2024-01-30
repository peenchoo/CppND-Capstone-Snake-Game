#include <limits>
#include "scores.h"

Scores::Scores() : _scores(std::make_unique<std::vector<Score>>()) 
{
    loadScores();
}

void Scores::addScore(const std::string& name, int score) 
{
    Score newScore = {name, score};
    _scores->push_back(newScore);
    saveScores();
}

void Scores::showHighScores(int amount) {
    std::cout << "\nHigh Scores:\n";
    std::vector<Score> highScores = *_scores;
    std::sort(highScores.begin(), highScores.end());
    int amountToShow = std::min(amount, static_cast<int>(highScores.size()));
    for (int i = 0; i < amountToShow; ++i) 
    {
        std::cout << "\t" << highScores[i].name << ": " << highScores[i].score << std::endl;
    }
}

void Scores::showRecentScores(int amount) {
    std::cout << "\nRecent Scores:\n";
    std::vector<Score> recentScores = *_scores;
    std::reverse(recentScores.begin(), recentScores.end());
    int amountToShow = std::min(amount, static_cast<int>(recentScores.size()));
    for (int i = 0; i < amountToShow; ++i) 
    {
        std::cout << "\t" << recentScores[i].name << ": " << recentScores[i].score << std::endl;
    }
}

void Scores::ScoreMenu()
{
    std::cout << "" << std::endl;
    std::cout << "/----------------- Score Menu ----------------/" << std::endl;
    std::cout << "1. High Scores" << std::endl;
    std::cout << "2. Recent Scores" << std::endl;
    std::cout << "3. Quit" << std::endl;
}

ScoresEnum::States Scores::ScoresMenuController()
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
    return ScoresEnum::getStateEnum(n);
}

void Scores::loadScores() {
    std::ifstream file(scoresFile);
    if (file.is_open()) 
    {
        _scores->clear();
        Score score;
        while (file >> score.name >> score.score) 
        {
            _scores->push_back(score);
        }
        file.close();
    }
    else
    {
        std::cout << "Loading Scores: Error opening scores file" <<std::endl;
    }
}

void Scores::saveScores() {
    std::ofstream file(scoresFile);
    if (file.is_open()) 
    {
        for (const auto& score : *_scores) 
        {
            file << score.name << " " << score.score << std::endl;
        }
        file.flush();
        file.close();
    }
    else
    {
        std::cout << "Saving Score: Error opening scores file" <<std::endl;
    }
}