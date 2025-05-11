#include "Timer.hpp"

Timer::Timer() : running(false) {}

void Timer::start() {
    startTime = std::chrono::high_resolution_clock::now();
    running = true;
}

void Timer::stop() {
    endTime = std::chrono::high_resolution_clock::now();
    running = false;
}

double Timer::getElapsedTime() const {
    if (running) {
        auto now = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double>(now - startTime).count();
    }
    return std::chrono::duration<double>(endTime - startTime).count();
}