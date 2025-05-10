#include "Timer.hpp"

Timer::Timer(int seconds) : duration(seconds) {
    startTime = std::chrono::steady_clock::now();
}

bool Timer::isTimeUp() const {
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
    return elapsed >= duration;
}