#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

class ScoreManager {
private:
    std::vector<int> scores;

public:
    void SaveToFile(const std::string& filename);
    void addScore(int score);
    void saveScores(const std::string& filename);
    void loadScores(const std::string& filename);
    void displayTopScores() const;
};