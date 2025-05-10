#pragma once
#include <chrono>

class Timer {
private:
    std::chrono::time_point<std::chrono::steady_clock> startTime;
    int duration; // Trajanje v sekundah

public:
    Timer() : duration(0) {}
    Timer(int seconds) : duration(seconds) {}
    void start();
    int getElapsedTime() const;
    bool isTimeUp() const; // Nova metoda
};