#pragma once
#include <vector>
#include <string>

class ScoreManager {
private:
    std::vector<std::pair<std::string, double>> scores;

public:
    void addScore(const std::string& name, double time);
    void saveScores(const std::string& filename) const;
    void loadScores(const std::string& filename);
    void displayTopScores() const;
};