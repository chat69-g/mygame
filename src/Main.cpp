#define SDL_MAIN_HANDLED

#ifdef _WIN32
#undef main  // Fix for Windows
#endif

#include "Game.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <memory>   // For smart pointers
#include <cmath>    // For math functions

using namespace std;

int main(int argc, char* argv[]){
    SDL_SetMainReady(); 

    (void)argc;  // Mark unused parameters explicitly
    (void)argv;

    // Initialize SDL
    if (!Game::Instance().Init("My Farm Game", 800, 600)) {
        std::cerr << "Game initialization failed!" << std::endl;
        return -1;
    }

    // Initialize SDL_image
    int imgFlags = IMG_INIT_PNG;
    if((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
        cerr << "SDL_image initialization failed: " << IMG_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    // Initialize SDL_ttf
    if(TTF_Init() == -1) {
        cerr << "SDL_ttf initialization failed: " << TTF_GetError() << endl;
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    try {
        Game& game = Game::Instance();
        game.Init("Animal Rescue", 800, 600);
        
        Uint32 lastTime = SDL_GetTicks();
        while (Game::Instance().IsRunning()) {
            Uint32 frameStart = SDL_GetTicks();
            float deltaTime = (currentTime - lastTime) / 1000.0f;
            lastTime = currentTime;
            
            Game::Instance().HandleEvents();
            Game::Instance().Update();
            Game::Instance().Render();
            
             // Frame rate control
            Uint32 frameTime = SDL_GetTicks() - frameStart;
            if (frameTime < 16) {  // ~60 FPS
                SDL_Delay(16 - frameTime);
            }
        }
        
        // Clean up
    Game::Instance().Clean();
    } catch(const exception& e) {
        cerr << "Exception: " << e.what() << endl;
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}