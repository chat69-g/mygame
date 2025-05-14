#include "Timer.hpp"
using namespace std; // Da lahko uporabljamo standardne funkcije brez std::

Timer::Timer() : running(false) {
    // Inicializacija timerja, ki ne teče
}

void Timer::start() {
    // Začni timer in shrani trenutni čas
    startTime = chrono::high_resolution_clock::now();
    running = true;
}

void Timer::stop() {
    // Ustavi timer in shrani končni čas
    endTime = chrono::high_resolution_clock::now();
    running = false;
}

double Timer::getElapsedTime() const {
    // Vrni pretečeni čas v sekundah
    if (running) {
        auto now = chrono::high_resolution_clock::now();
        return chrono::duration<double>(now - startTime).count();
    }
    return chrono::duration<double>(endTime - startTime).count();
}