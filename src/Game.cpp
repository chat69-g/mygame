#include "Game.hpp"
#include <iostream>
using namespace std; // Da lahko uporabljamo standardne funkcije brez std::

Game::Game(SDL_Renderer* renderer)
    : renderer(renderer),
      currentState(GameState::MENU),
      menu(renderer),
      player(40, 30),
      farm(40, 30),
      animal(40, 30),
      timer(),
      inFarm(false),
      timerStarted(false) {
    // Konstruktor za inicializacijo igre in vseh komponent
}

void Game::run() {
    // Glavna zanka igre
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false; // Izhod iz igre
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
                                waiting = false; // Izhod iz prikaza rezultatov
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
                menu.handleInput(event); // Upravljanje vnosa v meniju
            }
        }

        if (currentState == GameState::MENU) {
            menu.displayMenu(); // Prikaz menija
        } else if (currentState == GameState::PLAYING) {
            handlePlaying(); // Upravljanje igranja
        } else if (currentState == GameState::REPLAY) {
            handleReplay(); // Upravljanje replaya
        }
    }
}

void Game::handleMenu() {
    // Prikaz menija
    menu.displayMenu();
}

void Game::handlePlaying() {
    // Upravljanje igranja
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Počistimo zaslon z črno barvo
    SDL_RenderClear(renderer);

    const Uint8* keyState = SDL_GetKeyboardState(nullptr);
    player.update(keyState); // Posodobimo stanje igralca

    if (inFarm) {
        replayManager.recordMovement(player.getX(), player.getY()); // Beleženje premikov za replay
    }

    // Izris igralca
    SDL_Rect playerRect = {player.getX() * 20, player.getY() * 20, 20, 20};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Bela barva za igralca
    SDL_RenderFillRect(renderer, &playerRect);

    // Preverimo, ali je igralec blizu farme in jo aktiviramo
    if (!inFarm) {
        farm.checkProximity(player.getX(), player.getY());
        if (farm.activate(player.getX(), player.getY())) {
            inFarm = true;
            timer.start(); // Timer se začne šele, ko igralec vstopi v farmo
            replayManager.recordMovement(player.getX(), player.getY()); // Začetna pozicija v replayu

            // Ustvarimo nasprotnike samo enkrat
            if (enemies.empty()) {
                for (int i = 0; i < 3; ++i) { // Prepričamo se, da ustvarimo največ 3 nasprotnike
                    int enemyX, enemyY;
                    do {
                        enemyX = rand() % 40;
                        enemyY = rand() % 30;
                    } while ((std::abs(enemyX - player.getX()) <= 6 && std::abs(enemyY - player.getY()) <= 6) || 
                             (enemyX == farm.getX() && enemyY == farm.getY()));
                    enemies.emplace_back(enemyX, enemyY);
                    cout << "Enemy created at (" << enemyX << ", " << enemyY << ")" << endl;
                }
            }
        }
    }

    // Izris farme, če je vidna
    if (farm.isVisible()) {
        SDL_Rect farmRect = {farm.getX() * 20, farm.getY() * 20, 20, 20};
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Rumena barva za farmo
        SDL_RenderFillRect(renderer, &farmRect);
    }

    // Izris nasprotnikov
    if (inFarm) {
        for (auto& enemy : enemies) {
            enemy.update(player.getX(), player.getY());
            SDL_Rect enemyRect = {enemy.getX() * 20, enemy.getY() * 20, 20, 20};
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rdeča barva za nasprotnike
            SDL_RenderFillRect(renderer, &enemyRect);

            // Preverimo, ali je nasprotnik blizu igralca
            if (enemy.isNearPlayer(player.getX(), player.getY())) {
                player.loseLife();
                if (!player.isAlive()) {
                    handleEndScreen(false, 0); // Klic funkcije za konec igre
                    return;
                }
            }
        }
    }

    // Izris živali
    if (inFarm && !animal.isRescued()) {
        SDL_Rect animalRect = {animal.getX() * 20, animal.getY() * 20, 20, 20};
        SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255); // Rjava barva za žival
        SDL_RenderFillRect(renderer, &animalRect);

        if (animal.checkRescue(player.getX(), player.getY())) {
            farm.generateExit(40, 30, player.getX(), player.getY());

            // Prikažemo besedilo "WHAT A SAVE!!"
            SDL_Color white = {255, 255, 255, 255};
            SDL_Surface* saveSurface = TTF_RenderText_Solid(menu.getFont(), "WHAT A SAVE!!", white);
            SDL_Texture* saveTexture = SDL_CreateTextureFromSurface(renderer, saveSurface);
            SDL_Rect saveRect = {200, 300, saveSurface->w, saveSurface->h};
            SDL_RenderCopy(renderer, saveTexture, nullptr, &saveRect);
            SDL_RenderPresent(renderer);
            SDL_Delay(1000);
            SDL_FreeSurface(saveSurface);
            SDL_DestroyTexture(saveTexture);
        }
    }

    // Izris izhoda, če je viden
    if (farm.isExitVisible()) {
        SDL_Rect exitRect = {farm.getExitX() * 20, farm.getExitY() * 20, 20, 20};
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255); // Svetlo modra barva za izhod
        SDL_RenderFillRect(renderer, &exitRect);

        if (player.getX() == farm.getExitX() && player.getY() == farm.getExitY()) {
            timer.stop();
            double elapsedTime = timer.getElapsedTime();
            handleEndScreen(true, elapsedTime);
            return;
        }
    }

    SDL_RenderPresent(renderer); // Posodobimo zaslon
}

void Game::handleReplay() {
    // Upravljanje replaya
    replayManager.loadReplay("replay.txt");
    replayManager.displayReplay(renderer, menu.getFont());
    currentState = GameState::MENU;
}

void Game::handleEndScreen(bool won, double elapsedTime) {
    // Upravljanje končnega zaslona
    replayManager.saveReplay("replay.txt");

    if (won) {
        scoreManager.addScore(menu.getPlayerName(), elapsedTime);
        scoreManager.saveScores("scores.txt");
    }

    // Ponastavimo stanje igre
    player = Player(40, 30);
    farm = Farm(40, 30);
    animal = Animal(40, 30);
    enemies.clear();
    inFarm = false;
    timerStarted = false;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Color white = {255, 255, 255, 255};
    string message = won ? "You won in " + to_string(elapsedTime) + " seconds!" : "Game Over!";
    SDL_Surface* messageSurface = TTF_RenderText_Solid(menu.getFont(), message.c_str(), white);
    SDL_Texture* messageTexture = SDL_CreateTextureFromSurface(renderer, messageSurface);
    SDL_Rect messageRect = {200, 100, messageSurface->w, messageSurface->h};
    SDL_RenderCopy(renderer, messageTexture, nullptr, &messageRect);
    SDL_FreeSurface(messageSurface);
    SDL_DestroyTexture(messageTexture);

    SDL_RenderPresent(renderer);
    SDL_Delay(3000);

    currentState = GameState::MENU; // Vrnemo se v meni
}