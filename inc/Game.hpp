#pragma once

#include <SDL2/SDL.h>
#include <string>
#include "Menu.hpp"
#include "Player.hpp"
#include "Farm.hpp"
#include "Animal.hpp"
#include "Enemy.hpp"
#include "Timer.hpp"
#include "ScoreManager.hpp"
#include "ReplayManager.hpp"

enum class GameState {
    MENU,
    PLAYING,
    REPLAY
};

class Game {
private:
    SDL_Renderer* renderer;
    GameState currentState;
    Menu menu;
    Player player;
    Farm farm;
    Animal animal;
    std::vector<Enemy> enemies;
    Timer timer;
    ScoreManager scoreManager;
    ReplayManager replayManager;
    bool inFarm;
    bool timerStarted;

public:
    Game(SDL_Renderer* renderer);
    void run();
    void handleMenu();
    void handlePlaying();
    void handleReplay();
};