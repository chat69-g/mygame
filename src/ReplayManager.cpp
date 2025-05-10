#include "ReplayManager.hpp"
#include <iostream>

void ReplayManager::recordMove(const std::string& move) {
    moves.push_back(move);
}

void ReplayManager::saveReplay(const std::string& filename) {
    std::ofstream file(filename);
    for (const std::string& move : moves) {
        file << move << std::endl;
    }
}

void ReplayManager::loadReplay(const std::string& filename) {
    std::ifstream file(filename);
    std::string move;
    while (std::getline(file, move)) {
        moves.push_back(move);
    }
}

void ReplayManager::playReplay() const {
    for (const std::string& move : moves) {
        std::cout << move << std::endl;
    }
}