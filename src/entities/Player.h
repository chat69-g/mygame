#pragma once
#include <SDL2/SDL.h>

class Player {
public:
    Player(int x, int y);
    
    void update(float deltaTime);
    void render(SDL_Renderer* renderer);
    void handleEvent(const SDL_Event& event);
    
    SDL_Rect getRect() const { return rect; }
    void teleport(int x, int y);

private:
    SDL_Rect rect{0, 0, 32, 32};  // x, y, w, h
    float velX = 0, velY = 0;
    bool isTeleporting = false;
};