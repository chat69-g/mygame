// ScoreManager.hpp
#pragma once
#include <vector>
#include <string>
#include <algorithm>

struct ScoreEntry {
    std::string playerName;
    int score;
};

class ScoreManager {
public:
    void AddScore(const ScoreEntry& entry);
    const std::vector<ScoreEntry>& GetTopScores() const;
    void SaveToFile(const std::string& filename);
    void LoadFromFile(const std::string& filename);

private:
    std::vector<ScoreEntry> scores;
};