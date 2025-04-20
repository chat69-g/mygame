#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

struct ScoreEntry {
    std::string name;
    int score;
    float time;
    int level;
};

class ScoreManager {
public:
    ScoreManager();
    
    void AddScore(const ScoreEntry& entry);
    void SaveToFile(const std::string& filename);
    void LoadFromFile(const std::string& filename);
    const std::vector<ScoreEntry>& GetTopScores(int count = 5) const;
    
private:
    std::vector<ScoreEntry> scores;
    nlohmann::json ToJson() const;
    void FromJson(const nlohmann::json& j);
};