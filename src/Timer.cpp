#include "Timer.hpp"

#include <chrono>

std::chrono::time_point<std::chrono::steady_clock> startTime;

void Timer::start() {
    startTime = std::chrono::steady_clock::now();
}

int Timer::getElapsedTime() const {
    auto now = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
}