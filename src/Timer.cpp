#include "Timer.hpp"

void Timer::start() {
    startTime = std::chrono::steady_clock::now();
}

int Timer::getElapsedTime() const {
    auto now = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
}

bool Timer::isTimeUp() const {
    return getElapsedTime() >= duration; // Preveri, ali je čas potekel
}