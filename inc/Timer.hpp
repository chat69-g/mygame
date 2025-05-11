#pragma once
#include <chrono>

class Timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> endTime;
    bool running;

public:
    Timer(); // Deklaracija konstruktorja
    void start(); // Deklaracija metode start
    void stop(); // Deklaracija metode stop
    double getElapsedTime() const; // Deklaracija metode getElapsedTime
};