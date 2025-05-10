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

Game::Game() : currentState(GameState::MENU), timer(0), timerStarted(false), inFarm(false) {}

void Game::run() {
    while (true) {
        switch (currentState) {
            case GameState::MENU:
                menu.displayMenu();
                menu.handleInput();
                if (menu.isNameEntered()) {
                    currentState = GameState::PLAYING;
                }
                break;

            case GameState::PLAYING:
                // Logika za igranje igre
                break;

            case GameState::GAME_OVER:
                std::cout << "Game Over! Returning to menu...\n";
                currentState = GameState::MENU;
                break;
        }
    }
}

void Game::handleMenu() {
    menu.displayMenu();
    menu.handleInput();

    if (menu.isNameEntered()) {
        playerName = menu.getPlayerName(); // Shranimo ime igralca
        currentState = GameState::PLAYING; // Preklopimo v stanje igranja
    }
}

void Game::handlePlaying() {
    if (!inFarm) {
        // Logika za premikanje igralca in odkrivanje farme
    } else {
        if (!timerStarted) {
            timer.start(); // Začni timer, ko igralec vstopi v farmo
            timerStarted = true;
        }

        if (timer.isTimeUp()) {
            std::cout << "Game is over! Time is up!" << std::endl;
            currentState = GameState::GAME_OVER;
        }
    }
}
void Game::handleGameOver(bool won) {
    if (won) {
        std::cout << "Congratulations, " << playerName << "! You won!\n";
    } else {
        std::cout << "Game Over, " << playerName << ". Better luck next time!\n";
    }
    replayManager.saveReplay("replay.txt"); // Shranimo replay igre
    currentState = GameState::MENU;
}