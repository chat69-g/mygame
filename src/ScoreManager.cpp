#include "ScoreManager.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>

void ScoreManager::addScore(const std::string& name, int time) {
    scores.emplace_back(name, time);
    std::sort(scores.begin(), scores.end(), [](auto& a, auto& b) {
        return a.second < b.second;
    });
    if (scores.size() > 5) {
        scores.pop_back();
    }
}

void ScoreManager::saveScores(const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& score : scores) {
        file << score.first << " " << score.second << "\n";
    }
}

void ScoreManager::loadScores(const std::string& filename) {
    std::ifstream file(filename);
    scores.clear();
    std::string name;
    int time;
    while (file >> name >> time) {
        scores.emplace_back(name, time);
    }
}

void ScoreManager::displayTopScores() const {
    std::cout << "Top 5 Scores:\n";
    for (const auto& score : scores) {
        std::cout << score.first << ": " << score.second << " seconds\n";
    }
}