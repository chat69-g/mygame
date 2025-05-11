#include "ReplayManager.hpp"
#include <fstream>
#include <iostream>

void ReplayManager::recordMovement(int x, int y) {
    movements.emplace_back(x, y);
}

void ReplayManager::saveReplay(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file for writing: " << filename << std::endl;
        return;
    }
    for (const auto& move : movements) {
        file << move.first << " " << move.second << "\n";
    }
}

void ReplayManager::loadReplay(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file for reading: " << filename << std::endl;
        return;
    }
    movements.clear();
    int x, y;
    while (file >> x >> y) {
        movements.emplace_back(x, y);
    }
}

void ReplayManager::displayReplay() const {
    std::cout << "Replay of last game:\n";
    for (const auto& move : movements) {
        std::cout << "Player moved to (" << move.first << ", " << move.second << ")\n";
    }
}