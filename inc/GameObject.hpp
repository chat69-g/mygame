#pragma once
#include <SDL2/SDL.h>

class GameObject {
public:
    GameObject(float x, float y, float width, float height);
    virtual ~GameObject() = default;
    
    virtual void update() = 0;
    virtual void render(SDL_Renderer* renderer) = 0;  // Spremenjeno
    
    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;
    
protected:
    float x, y;
    float width, height;
};