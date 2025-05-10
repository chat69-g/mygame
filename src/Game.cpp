#include "Game.hpp"
#include <iostream>
#include <SDL2/SDL.h>

Game::Game(SDL_Renderer* renderer)
    : currentState(GameState::MENU),
      menu(renderer),
      timer(0),
      player(40, 30),
      farm(40, 30),
      animal(40, 30),
      enemies({Enemy(40, 30), Enemy(40, 30)}),
      timerStarted(false),
      inFarm(false) {}

  void Game::run() {
    while (true) {
        switch (currentState) {
            case GameState::MENU:
                handleMenu();
                break;

            case GameState::PLAYING:
                handlePlaying();
                break;

            case GameState::PAUSED:
                std::cout << "Game is paused. Press any key to continue...\n";
                std::cin.ignore();
                currentState = GameState::PLAYING;
                break;

            case GameState::GAME_OVER:
                handleGameOver(false); // Ali true, če je igralec zmagal
                break;
        }
    }
}

void Game::handleMenu() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            currentState = GameState::GAME_OVER;
            return;
        }
        menu.handleInput(event);
    }

    menu.displayMenu();

    if (menu.isNameEntered()) {
        playerName = menu.getPlayerName(); // Shranimo ime igralca
        currentState = GameState::PLAYING; // Preklopimo v stanje igranja
    }
}

void Game::handlePlaying() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            currentState = GameState::GAME_OVER;
            return;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_w: player.move('w'); break;
                case SDLK_s: player.move('s'); break;
                case SDLK_a: player.move('a'); break;
                case SDLK_d: player.move('d'); break;
            }
        }
    }

    if (!inFarm) {
        farm.checkProximity(player.getX(), player.getY());
        if (farm.isVisible()) {
            inFarm = true;
        }
    } else {
        if (!timerStarted) {
            timer.start(); // Začni timer, ko igralec vstopi v farmo
            timerStarted = true;
        }

        for (auto& enemy : enemies) {
            enemy.update(player.getX(), player.getY());
            if (enemy.isNearPlayer(player.getX(), player.getY())) {
                player.loseLife();
                if (!player.isAlive()) {
                    currentState = GameState::GAME_OVER;
                    return;
                }
            }
        }

        animal.checkRescue(player.getX(), player.getY());
        if (animal.isRescued()) {
            std::cout << "You rescued the animal! Find the exit!" << std::endl;
            // Logika za prikaz izhoda
        }

        if (timer.isTimeUp()) {
            std::cout << "Game Over! Time is up!" << std::endl;
            currentState = GameState::GAME_OVER;
            return;
        }
    }

    // Rendering (uporabite SDL za prikazovanje)
}

void Game::handleGameOver(bool won) {
    if (won) {
        std::cout << "Congratulations, " << playerName << "! You won!\n";
        scoreManager.addScore(playerName, timer.getElapsedTime());
        scoreManager.saveScores("scores.txt");
    } else {
        std::cout << "Game Over, " << playerName << ". Better luck next time!\n";
    }
    replayManager.saveReplay("replay.txt"); // Shranimo replay igre
    currentState = GameState::MENU;
}