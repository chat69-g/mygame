#include "ReplayManager.hpp"
#include <fstream>
#include <iostream>

void ReplayManager::recordMove(const std::string& move) {
    moves.push_back(move);
}

void ReplayManager::saveReplay(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file for writing: " << filename << std::endl;
        return;
    }
    for (const auto& move : moves) {
        file << move << "\n";
    }
}

void ReplayManager::loadReplay(const std::string& filename) {
    std::ifstream file(filename);
    moves.clear();
    std::string move;
    while (std::getline(file, move)) {
        moves.push_back(move);
    }
}

void ReplayManager::playReplay() const {
    for (const auto& move : moves) {
        std::cout << move << "\n";
    }
}