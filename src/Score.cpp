#include "Score.hpp"
#include <fstream>
#include <algorithm>

using namespace std;
using json = nlohmann::json;

ScoreManager::ScoreManager() {
    // Initialize with some default scores
    scores = {
        {"Hero", 5000},
        {"Champion", 4000},
        {"Savior", 3000},
        {"Protector", 2000},
        {"Newbie", 1000}
    };
}

void ScoreManager::AddScore(const ScoreEntry& entry) {
    scores.push_back(entry);
    sort(scores.begin(), scores.end(), 
        [](const ScoreEntry& a, const ScoreEntry& b) {
            return a.score > b.score;
        });
    
    if(scores.size() > 5) {
        scores.resize(5);
    }
}

void ScoreManager::SaveToFile(const string& filename) {
    json j;
    for(const auto& entry : scores) {
        j["scores"].push_back({
            {"name", entry.name},
            {"score", entry.score},
            {"time", entry.time},
            {"level", entry.level}
        });
    }
    
    ofstream file(filename);
    if(file.is_open()) {
        file << j.dump(4);
        file.close();
    }
}

void ScoreManager::LoadFromFile(const string& filename) {
    ifstream file(filename);
    if(!file.is_open()) return;
    
    json j;
    file >> j;
    file.close();
    
    scores.clear();
    for(const auto& item : j["scores"]) {
        scores.push_back({
            item["name"].get<string>(),
            item["score"].get<int>(),
            item["time"].get<float>(),
            item["level"].get<int>()
        });
    }
}

const vector<ScoreEntry>& ScoreManager::GetTopScores(int count) const {
    static vector<ScoreEntry> topScores;
    topScores.clear();
    
    int end = min(count, static_cast<int>(scores.size()));
    for(int i = 0; i < end; i++) {
        topScores.push_back(scores[i]);
    }
    
    return topScores;
}

json ScoreManager::ToJson() const {
    json j;
    for(const auto& entry : scores) {
        j["scores"].push_back({
            {"name", entry.name},
            {"score", entry.score},
            {"time", entry.time},
            {"level", entry.level}
        });
    }
    return j;
}

void ScoreManager::FromJson(const json& j) {
    scores.clear();
    for(const auto& item : j["scores"]) {
        scores.push_back({
            item["name"].get<string>(),
            item["score"].get<int>(),
            item["time"].get<float>(),
            item["level"].get<int>()
        });
    }
}