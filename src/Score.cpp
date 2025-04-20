#include "Score.hpp"
#include <sstream>
#include <algorithm>

ScoreManager::ScoreManager() {
    // Initialize with some default scores
    scores = {
        {"Hero", 5000, 120.5f, 2},
        {"Champion", 4000, 150.0f, 2},
        {"Savior", 3000, 180.0f, 1},
        {"Protector", 2000, 200.0f, 1},
        {"Newbie", 1000, 250.0f, 1}
    };
}

void ScoreManager::AddScore(const ScoreEntry& entry) {
    scores.push_back(entry);
    std::sort(scores.begin(), scores.end(), 
        [](const ScoreEntry& a, const ScoreEntry& b) {
            return a.score > b.score;
        });
    
    if(scores.size() > 5) {
        scores.resize(5);
    }
}

std::string ScoreManager::SerializeScores() const {
    std::ostringstream oss;
    for(const auto& entry : scores) {
        oss << entry.name << "," 
            << entry.score << ","
            << entry.time << ","
            << entry.level << "\n";
    }
    return oss.str();
}

void ScoreManager::DeserializeScores(const std::string& data) {
    std::istringstream iss(data);
    scores.clear();
    
    std::string line;
    while(std::getline(iss, line)) {
        std::istringstream lineStream(line);
        ScoreEntry entry;
        std::string field;
        
        if(std::getline(lineStream, field, ',')) entry.name = field;
        if(std::getline(lineStream, field, ',')) entry.score = std::stoi(field);
        if(std::getline(lineStream, field, ',')) entry.time = std::stof(field);
        if(std::getline(lineStream, field, ',')) entry.level = std::stoi(field);
        
        scores.push_back(entry);
    }
}

void ScoreManager::SaveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if(file.is_open()) {
        file << SerializeScores();
        file.close();
    }
}

void ScoreManager::LoadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if(!file.is_open()) return;
    
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    DeserializeScores(content);
}

const std::vector<ScoreEntry>& ScoreManager::GetTopScores(int count) const {
    static std::vector<ScoreEntry> topScores;
    topScores.clear();
    
    int end = std::min(count, static_cast<int>(scores.size()));
    for(int i = 0; i < end; i++) {
        topScores.push_back(scores[i]);
    }
    
    return topScores;
}