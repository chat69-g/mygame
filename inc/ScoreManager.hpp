// ScoreManager.hpp
#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct ScoreEntry {
    std::string playerName;
    int score;
    float time;
    int level;
};

class ScoreManager {
public:
    void AddScore(const ScoreEntry& entry);
    void SaveToFile(const std::string& filename);
    void LoadFromFile(const std::string& filename);
    const std::vector<ScoreEntry>& GetTopScores(int count = 5);

private:
    std::vector<ScoreEntry> scores;
};