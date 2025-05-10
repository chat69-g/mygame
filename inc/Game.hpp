#pragma once

#include <string>
#include "GameState.hpp"
#include "Menu.hpp"
#include "ScoreManager.hpp"
#include "ReplayManager.hpp"
#include "Timer.hpp"

class Game {
    private:
        GameState currentState;
        Timer timer;
        bool timerStarted;
        bool inFarm;
    
        Menu menu;                     // Dodano za upravljanje menija
        std::string playerName;        // Dodano za shranjevanje imena igralca
        ReplayManager replayManager;   // Dodano za upravljanje replay sistema
    
    public:
        Game();
        void run();
        void handleMenu();
        void handlePlaying();
        void handleGameOver(bool won);
    };