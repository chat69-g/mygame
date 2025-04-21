// ScoreManager.cpp
#include "ScoreManager.hpp"
#include <fstream>
#include <algorithm>

void ScoreManager::AddScore(const ScoreEntry& entry) {
    scores.push_back(entry);
    std::sort(scores.begin(), scores.end(), 
        [](const ScoreEntry& a, const ScoreEntry& b) {
            return a.score > b.score;
        });
    
    if(scores.size() > 5) scores.resize(5);
}

void ScoreManager::SaveToFile(const std::string& filename) {
    json j;
    for(const auto& entry : scores) {
        j["scores"].push_back({
            {"name", entry.playerName},
            {"score", entry.score},
            {"time", entry.time},
            {"level", entry.level}
        });
    }
    
    std::ofstream file(filename);
    file << j.dump(4);
}