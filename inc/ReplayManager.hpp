#pragma once

#include <vector>
#include <string>
#include <fstream>

class ReplayManager {
private:
    std::vector<std::string> moves;

public:
    void recordMove(const std::string& move);
    void saveReplay(const std::string& filename);
    void loadReplay(const std::string& filename);
    void playReplay() const;
};