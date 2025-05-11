#include "Menu.hpp"
#include <iostream>

Menu::Menu(SDL_Renderer* renderer) : renderer(renderer), nameEntered(false), selectedOption(0) {
    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
    }
    font = TTF_OpenFont("assets/fonts/Roboto-Bold.ttf", 24);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }
}

Menu::~Menu() {
    TTF_CloseFont(font);
    TTF_Quit();
}

void Menu::displayMenu() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Počistimo zaslon z črno barvo
    SDL_RenderClear(renderer);

    SDL_Color white = {255, 255, 255, 255};
    SDL_Color yellow = {255, 255, 0, 255};

    SDL_Surface* titleSurface = TTF_RenderText_Solid(font, "=== MENU ===", white);
    SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
    SDL_Rect titleRect = {200, 50, titleSurface->w, titleSurface->h};
    SDL_RenderCopy(renderer, titleTexture, nullptr, &titleRect);
    SDL_FreeSurface(titleSurface);
    SDL_DestroyTexture(titleTexture);

    for (size_t i = 0; i < options.size(); ++i) {
        SDL_Color color = (i == selectedOption) ? yellow : white;
        SDL_Surface* optionSurface = TTF_RenderText_Solid(font, options[i].c_str(), color);
        SDL_Texture* optionTexture = SDL_CreateTextureFromSurface(renderer, optionSurface);
        SDL_Rect optionRect = {200, 150 + static_cast<int>(i) * 50, optionSurface->w, optionSurface->h};
        SDL_RenderCopy(renderer, optionTexture, nullptr, &optionRect);
        SDL_FreeSurface(optionSurface);
        SDL_DestroyTexture(optionTexture);
    }

    if (selectedOption == 0) { // Prikaz za vnos imena
        std::string prompt = "Enter your name: " + playerName;
        SDL_Surface* nameSurface = TTF_RenderText_Solid(font, prompt.c_str(), white);
        SDL_Texture* nameTexture = SDL_CreateTextureFromSurface(renderer, nameSurface);
        SDL_Rect nameRect = {200, 400, nameSurface->w, nameSurface->h}; // Premaknemo besedilo nižje
        SDL_RenderCopy(renderer, nameTexture, nullptr, &nameRect);
        SDL_FreeSurface(nameSurface);
        SDL_DestroyTexture(nameTexture);
    }

    SDL_RenderPresent(renderer);
}

void Menu::handleInput(SDL_Event& event) {
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
                if (selectedOption == 0) { // Izbira za vnos imena
                    if (!nameEntered) {
                        nameEntered = true;
                    }
                } else if (selectedOption == 1) { // Izbira za začetek igre
                    if (playerName.empty()) {
                        std::cout << "Please enter your name first!" << std::endl;
                    } else {
                        SDL_Event startEvent;
                        startEvent.type = SDL_USEREVENT;
                        startEvent.user.code = 2;
                        SDL_PushEvent(&startEvent);
                    }
                } else if (selectedOption == 2) { // Izbira za prikaz top 5 rezultatov
                    SDL_Event scoreEvent;
                    scoreEvent.type = SDL_USEREVENT;
                    scoreEvent.user.code = 1;
                    SDL_PushEvent(&scoreEvent);
                } else if (selectedOption == 3) { // Izbira za replay
                    SDL_Event replayEvent;
                    replayEvent.type = SDL_USEREVENT;
                    replayEvent.user.code = 3;
                    SDL_PushEvent(&replayEvent);
                }
                break;
            case SDLK_BACKSPACE: // Brisanje znakov pri vnosu imena
                if (!playerName.empty()) {
                    playerName.pop_back();
                }
                break;
            default:
                if (event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z) {
                    playerName += static_cast<char>(event.key.keysym.sym);
                }
                break;
        }
    }
}

std::string Menu::getPlayerName() const {
    return playerName;
}

bool Menu::isNameEntered() const {
    return nameEntered;
}