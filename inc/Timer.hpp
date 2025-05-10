#pragma once

class Timer {
private:
    int duration;

    public:
    Timer() : duration(0) {} // Privzeti konstruktor
    Timer(int seconds) : duration(seconds) {}
    void start();
    int getElapsedTime() const;
};