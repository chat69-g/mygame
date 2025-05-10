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
        bool timerStarted; // Dodano za sledenje začetka timerja
        bool inFarm;
    
    public:
        Game();
        void run();
        void handleMenu();
        void handlePlaying();
        void handleGameOver(bool won);
    };