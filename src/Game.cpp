#include "Game.hpp"
#include <iostream>

Game::Game(SDL_Renderer* renderer)
    : renderer(renderer),
      currentState(GameState::MENU), // Začetno stanje je MENU
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
                    if (event.user.code == 1) { // Prikaz "Top 5 Scores"
                        scoreManager.loadScores("scores.txt");
                        scoreManager.displayTopScores(renderer, menu.getFont());
    
                        bool waiting = true;
                        SDL_Event waitEvent;
                        while (waiting) {
                            while (SDL_PollEvent(&waitEvent)) {
                                if (waitEvent.type == SDL_KEYDOWN && waitEvent.key.keysym.sym == SDLK_ESCAPE) {
                                    waiting = false;
                                }
                            }
                        }
                    } else if (event.user.code == 2) { // Začetek igre
                        currentState = GameState::PLAYING;
                    } else if (event.user.code == 3) { // Replay
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
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Bela za igralca
    SDL_RenderFillRect(renderer, &playerRect);

    if (!inFarm) {
        farm.checkProximity(player.getX(), player.getY());
        if (farm.activate(player.getX(), player.getY())) {
            inFarm = true;
            timer.start();

            // Ustvarimo nasprotnike
            enemies.clear();
            for (int i = 0; i < 3; ++i) { // Dodamo 3 nasprotnike
                int enemyX, enemyY;
                do {
                    enemyX = rand() % 40;
                    enemyY = rand() % 30;
                } while (std::abs(enemyX - player.getX()) <= 5 && std::abs(enemyY - player.getY()) <= 5);
                enemies.emplace_back(enemyX, enemyY);
            }
        }
    }

    if (farm.isVisible()) {
        SDL_Rect farmRect = {farm.getX() * 20, farm.getY() * 20, 20, 20};
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Rumena za farmo
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
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rdeča za nasprotnike
            SDL_RenderFillRect(renderer, &enemyRect);

            if (enemy.isNearPlayer(player.getX(), player.getY())) {
                player.loseLife();
                if (!player.isAlive()) {
                    player = Player(40, 30); // Ponastavimo igralca
                    std::cout << "Game Over! You lost all your lives!" << std::endl;
                    currentState = GameState::MENU;
                    return;
                }
            }
        }

        SDL_Rect animalRect = {animal.getX() * 20, animal.getY() * 20, 20, 20};
        SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255); // Rjava za žival
        SDL_RenderFillRect(renderer, &animalRect);

        if (animal.checkRescue(player.getX(), player.getY())) {
            std::cout << "Animal rescued! Find the exit!" << std::endl;
            farm.generateExit(40, 30, player.getX(), player.getY()); // Generiramo izhod
        }

        if (farm.isExitVisible()) {
            SDL_Rect exitRect = {farm.getExitX() * 20, farm.getExitY() * 20, 20, 20};
            SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255); // Svetlo modra za izhod
            SDL_RenderFillRect(renderer, &exitRect);

            if (player.getX() == farm.getExitX() && player.getY() == farm.getExitY()) {
                timer.stop();
                double elapsedTime = timer.getElapsedTime();
                std::cout << "You completed the game in " << elapsedTime << " seconds!" << std::endl;

                scoreManager.addScore(menu.getPlayerName(), elapsedTime);
                scoreManager.saveScores("scores.txt");

                currentState = GameState::MENU;
                return;
            }
        }
    }

    SDL_RenderPresent(renderer);
}

void Game::handleReplay() {
    replayManager.loadReplay("replay.txt");
    replayManager.displayReplay(renderer, menu.getFont());
    currentState = GameState::MENU;
}

void Game::handleEndScreen(bool won, double elapsedTime) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Color white = {255, 255, 255, 255};
    std::string message = won ? "You won in " + std::to_string(elapsedTime) + " seconds!" : "Game Over!";
    SDL_Surface* messageSurface = TTF_RenderText_Solid(menu.getFont(), message.c_str(), white);
    SDL_Texture* messageTexture = SDL_CreateTextureFromSurface(renderer, messageSurface);
    SDL_Rect messageRect = {200, 100, messageSurface->w, messageSurface->h};
    SDL_RenderCopy(renderer, messageTexture, nullptr, &messageRect);
    SDL_FreeSurface(messageSurface);
    SDL_DestroyTexture(messageTexture);

    std::vector<std::string> options = {"Play Again", "Replay", "Exit Game", "Return to Menu"};
    size_t selectedOption = 0;

    bool waiting = true;
    SDL_Event event;
    while (waiting) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (size_t i = 0; i < options.size(); ++i) {
            SDL_Color color = (i == selectedOption) ? SDL_Color{255, 255, 0, 255} : white;
            SDL_Surface* optionSurface = TTF_RenderText_Solid(menu.getFont(), options[i].c_str(), color);
            SDL_Texture* optionTexture = SDL_CreateTextureFromSurface(renderer, optionSurface);
            SDL_Rect optionRect = {200, 200 + static_cast<int>(i) * 50, optionSurface->w, optionSurface->h};
            SDL_RenderCopy(renderer, optionTexture, nullptr, &optionRect);
            SDL_FreeSurface(optionSurface);
            SDL_DestroyTexture(optionTexture);
        }

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                    case SDLK_w:
                        selectedOption = (selectedOption - 1 + options.size()) % options.size();
                        break;
                    case SDLK_DOWN:
                    case SDLK_s:
                        selectedOption = (selectedOption + 1) % options.size();
                        break;
                    case SDLK_RETURN:
                        if (selectedOption == 0) {
                            currentState = GameState::PLAYING;
                            waiting = false;
                        } else if (selectedOption == 1) {
                            currentState = GameState::REPLAY;
                            waiting = false;
                        } else if (selectedOption == 2) {
                            exit(0);
                        } else if (selectedOption == 3) {
                            currentState = GameState::MENU;
                            waiting = false;
                        }
                        break;
                }
            }
        }
    }
}