// ReplaySystem.hpp
#pragma once
#include <vector>
#include <string>
#include "common.hpp"

struct GameSnapshot {
    Vec2 playerPos;
    std::vector<Vec2> enemyPositions;
    float timestamp;
};

class ReplaySystem {
public:
    void RecordFrame(const GameSnapshot& snapshot);
    void SaveToFile(const std::string& filename);
    void LoadFromFile(const std::string& filename);

private:
    std::vector<GameSnapshot> frames;
};