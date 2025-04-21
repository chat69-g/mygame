// ScoreManager.cpp
#include "ScoreManager.hpp"
#include <fstream>
#include <sstream>

void ScoreManager::AddScore(const ScoreEntry& entry) {
    scores.push_back(entry);
    std::sort(scores.begin(), scores.end(), 
        [](const ScoreEntry& a, const ScoreEntry& b) {
            return a.score > b.score;
        });
    
    if(scores.size() > 5) scores.resize(5);
}

void ScoreManager::SaveToFile(const std::string& filename) {
    std::ofstream file(filename);
    for(const auto& entry : scores) {
        file << entry.playerName << "," << entry.score << "\n";
    }
}