#include "ScoreManager.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>

void ScoreManager::addScore(const std::string& name, double time) {
    scores.emplace_back(name, time);
    std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });
    if (scores.size() > 5) {
        scores.pop_back();
    }
}

void ScoreManager::saveScores(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file for writing: " << filename << std::endl;
        return;
    }
    for (const auto& score : scores) {
        file << score.first << " " << score.second << "\n";
    }
}

void ScoreManager::loadScores(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file for reading: " << filename << std::endl;
        return;
    }
    scores.clear();
    std::string name;
    double time;
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