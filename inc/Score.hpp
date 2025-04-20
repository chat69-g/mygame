#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

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

    std::string SerializeScores() const;
    void DeserializeScores(const std::string& data);
};