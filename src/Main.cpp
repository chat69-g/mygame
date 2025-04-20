#include "Game.hpp"
#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
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
    return 0;
}