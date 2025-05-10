#include "Game.hpp"
#include "TextureManager.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Animal.hpp"
#include "Farm.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

Game::Game() : currentState(GameState::MENU), inFarm(false), timer(0) {} // Inicializacija timerja

void Game::run() {
    while (true) {
        switch (currentState) {
            case GameState::MENU:
                handleMenu();
                break;
            case GameState::PLAYING:
                handlePlaying();
                break;
            case GameState::GAME_OVER:
                handleGameOver(false); // Ali true, če je igralec zmagal
                break;
            default:
                break;
        }
    }
}

void Game::handleMenu() {
    menu.displayMenu();
    menu.handleInput();

    if (menu.isNameEntered()) {
        playerName = menu.getPlayerName();
        currentState = GameState::PLAYING;
    }
}

void Game::handlePlaying() {
    // Logika za igranje igre
    if (!inFarm) {
        // Premikanje igralca in odkrivanje farme
    } else {
        timer.start();
        // Logika za farmo (nasprotniki, bik, izhod)
    }
}

void Game::handleGameOver(bool won) {
    if (won) {
        std::cout << "Congratulations, " << playerName << "! You won!\n";
    } else {
        std::cout << "Game Over, " << playerName << ". Better luck next time!\n";
    }
    replayManager.saveReplay("replay.txt");
    currentState = GameState::MENU;
}