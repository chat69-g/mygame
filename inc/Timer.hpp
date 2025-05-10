#pragma once

#include <chrono>

class Timer {
private:
    std::chrono::time_point<std::chrono::steady_clock> startTime;
    int duration;

public:
    Timer(int seconds);
    bool isTimeUp() const;
};