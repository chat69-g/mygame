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
    Menu menu;
    ScoreManager scoreManager;
    ReplayManager replayManager;
    Timer timer;
    std::string playerName;
    bool inFarm;

public:
    Game();
    void run();
    void handleMenu();
    void handlePlaying();
    void handleGameOver(bool won);
};