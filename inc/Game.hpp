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
using namespace std; // Da lahko uporabljamo standardne funkcije brez std::

enum class GameState {
    MENU,    // Stanje igre: meni
    PLAYING, // Stanje igre: igranje
    REPLAY   // Stanje igre: replay
};

class Game {
private:
    SDL_Renderer* renderer; // SDL renderer za izris
    GameState currentState; // Trenutno stanje igre
    Menu menu; // Meni igre
    Player player; // Igralec
    Farm farm; // Farma
    Animal animal; // Žival
    vector<Enemy> enemies; // Seznam nasprotnikov
    Timer timer; // Timer za merjenje časa
    ScoreManager scoreManager; // Upravljalnik rezultatov
    ReplayManager replayManager; // Upravljalnik replaya
    bool inFarm; // Ali je igralec v farmi
    bool timerStarted; // Ali je timer že zagnan

public:
    Game(SDL_Renderer* renderer); // Konstruktor za inicializacijo igre
    void run(); // Glavna zanka igre
    void handleMenu(); // Upravljanje menija
    void handlePlaying(); // Upravljanje igranja
    void handleReplay(); // Upravljanje replaya
    void handleEndScreen(bool won, double elapsedTime); // Upravljanje končnega zaslona
};