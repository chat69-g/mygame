#include "Game.hpp"
#include <iostream>

Game::Game(SDL_Renderer* renderer)
    : renderer(renderer),
      currentState(GameState::MENU),
      menu(renderer),
      player(40, 30),
      farm(40, 30),
      animal(40, 30),
      timer(),
      inFarm(false),
      timerStarted(false) {}

void Game::run() {
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            if (event.type == SDL_USEREVENT) {
                if (event.user.code == 1) {
                    scoreManager.displayTopScores();
                } else if (event.user.code == 2) {
                    currentState = GameState::PLAYING;
                } else if (event.user.code == 3) {
                    currentState = GameState::REPLAY;
                }
            }

            if (currentState == GameState::MENU) {
                menu.handleInput(event);
            }
        }

        if (currentState == GameState::MENU) {
            menu.displayMenu();
        } else if (currentState == GameState::PLAYING) {
            handlePlaying();
        } else if (currentState == GameState::REPLAY) {
            handleReplay();
        }
    }
}

void Game::handleMenu() {
    menu.displayMenu();
}

void Game::handlePlaying() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    const Uint8* keyState = SDL_GetKeyboardState(nullptr);
    player.update(keyState);

    SDL_Rect playerRect = {player.getX() * 20, player.getY() * 20, 20, 20};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &playerRect);

    if (!inFarm) {
        farm.checkProximity(player.getX(), player.getY());
        if (farm.activate(player.getX(), player.getY())) {
            inFarm = true;
            timer.start();
        }
    }

    if (farm.isVisible()) {
        SDL_Rect farmRect = {farm.getX() * 20, farm.getY() * 20, 20, 20};
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderFillRect(renderer, &farmRect);
    }

    if (inFarm) {
        if (!timerStarted) {
            timer.start();
            timerStarted = true;
        }

        for (auto& enemy : enemies) {
            enemy.update(player.getX(), player.getY());
            SDL_Rect enemyRect = {enemy.getX() * 20, enemy.getY() * 20, 20, 20};
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &enemyRect);
        }

        SDL_Rect animalRect = {animal.getX() * 20, animal.getY() * 20, 20, 20};
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &animalRect);

        if (animal.checkRescue(player.getX(), player.getY())) {
            std::cout << "Animal rescued! Find the exit!" << std::endl;
        }

        if (player.hasExitedFarm()) {
            timer.stop();
            double elapsedTime = timer.getElapsedTime();
            std::cout << "You completed the game in " << elapsedTime << " seconds!" << std::endl;

            scoreManager.addScore(menu.getPlayerName(), elapsedTime);
            scoreManager.saveScores("scores.txt");

            currentState = GameState::MENU;
        }
    }

    SDL_RenderPresent(renderer);
}

void Game::handleReplay() {
    replayManager.displayReplay();
    currentState = GameState::MENU;
}