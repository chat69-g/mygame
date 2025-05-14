#pragma once
#include <chrono>
using namespace std; // Da lahko uporabljamo standardne funkcije brez std::

class Timer {
private:
    chrono::time_point<chrono::high_resolution_clock> startTime; // Začetni čas
    chrono::time_point<chrono::high_resolution_clock> endTime; // Končni čas
    bool running; // Ali timer trenutno teče

public:
    Timer(); // Konstruktor za inicializacijo timerja
    void start(); // Začni timer
    void stop(); // Ustavi timer
    double getElapsedTime() const; // Vrni pretečeni čas v sekundah
};