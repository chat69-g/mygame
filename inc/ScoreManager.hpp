#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

class ScoreManager {
    private:
    std::vector<std::pair<std::string, int>> scores; // Popravljena deklaracija
    
    public:
        void addScore(const std::string& name, int time); // Posodobljena deklaracija
        void saveScores(const std::string& filename);
        void loadScores(const std::string& filename);
        void displayTopScores() const;
    };