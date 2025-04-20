#include "Game.hpp"
#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "SDL could not initialize! Error: " << SDL_GetError() << endl;
        return 1;
    }

    // Initialize SDL_image
    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        cerr << "SDL_image could not initialize! Error: " << IMG_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    // Initialize SDL_ttf
    if(TTF_Init() == -1) {
        cerr << "SDL_ttf could not initialize! Error: " << TTF_GetError() << endl;
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    try {
        Game& game = Game::Instance();
        game.Init("Animal Rescue", 800, 600);
        
        Uint32 lastTime = SDL_GetTicks();
        while(game.Running()) {
            Uint32 currentTime = SDL_GetTicks();
            float deltaTime = (currentTime - lastTime) / 1000.0f;
            lastTime = currentTime;
            
            game.HandleEvents();
            game.Update(deltaTime);
            game.Render();
            
            // Cap at 60 FPS
            Uint32 frameTime = SDL_GetTicks() - currentTime;
            if(frameTime < 16) {
                SDL_Delay(16 - frameTime);
            }
        }
        
        game.Clean();
    } catch(const exception& e) {
        cerr << "Game crashed with exception: " << e.what() << endl;
        return 1;
    }

    // Clean up SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    
    return 0;
}