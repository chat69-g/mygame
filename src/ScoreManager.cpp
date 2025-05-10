#include "ScoreManager.hpp"
#include <iostream>

void ScoreManager::addScore(int score) {
    scores.push_back(score);
    std::sort(scores.rbegin(), scores.rend());
    if (scores.size() > 5) {
        scores.pop_back();
    }
}

void ScoreManager::saveScores(const std::string& filename) {
    std::ofstream file(filename);
    for (int score : scores) {
        file << score << std::endl;
    }
}

void ScoreManager::loadScores(const std::string& filename) {
    std::ifstream file(filename);
    int score;
    while (file >> score) {
        scores.push_back(score);
    }
    std::sort(scores.rbegin(), scores.rend());
}

void ScoreManager::displayTopScores() const {
    std::cout << "Top Scores:" << std::endl;
    for (int score : scores) {
        std::cout << score << std::endl;
    }
}
void ScoreManager::SaveToFile(const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& score : scores) {
        file << score << std::endl;
    }
}