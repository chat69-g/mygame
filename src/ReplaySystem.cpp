// ReplaySystem.cpp
#include "ReplaySystem.hpp"
#include <fstream>

void ReplaySystem::RecordFrame(const GameSnapshot& snapshot) {
    frames.push_back(snapshot);
}

void ReplaySystem::SaveToFile(const std::string& filename) {
    std::ofstream file(filename);
    for(const auto& frame : frames) {
        file << frame.timestamp << " "
             << frame.playerPos.x << " " << frame.playerPos.y << " ";
        
        for(const auto& enemyPos : frame.enemyPositions) {
            file << enemyPos.x << " " << enemyPos.y << " ";
        }
        file << "\n";
    }
}