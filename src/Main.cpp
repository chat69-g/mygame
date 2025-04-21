#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

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
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "SDL initialization failed: " << SDL_GetError() << endl;
        return 1;
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