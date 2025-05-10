#pragma once

#include <string>
#include "GameState.hpp"
#include "Menu.hpp"
#include "ScoreManager.hpp"
#include "ReplayManager.hpp"
#include "Timer.hpp"
#include "Player.hpp"
#include "Farm.hpp"
#include "Enemy.hpp"
#include "Animal.hpp"

class Game {
private:
    GameState currentState;       // Trenutno stanje igre
    Menu menu;                    // Upravljanje menija
    Timer timer;                  // Upravljanje časa
    ReplayManager replayManager;  // Upravljanje replay sistema
    ScoreManager scoreManager;    // Upravljanje rezultatov
    Player player;                // Igralec
    Farm farm;                    // Farma
    Animal animal;                // Žival
    std::vector<Enemy> enemies;   // Nasprotniki
    bool timerStarted;            // Ali je timer že začet
    bool inFarm;                  // Ali je igralec v farmi
    std::string playerName;       // Ime igralca

public:
    Game(SDL_Renderer* renderer);
    void run();
    void handleMenu();
    void handlePlaying();
    void handleGameOver(bool won);
};