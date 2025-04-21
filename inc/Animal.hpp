#pragma once
#include <SDL2/SDL.h>
#include "common.hpp"

class Animal {
    public:
        Animal(Vec2 position, int scoreValue);  // Dodajte parameter scoreValue
        
        bool IsRescued() const { return isRescued; }
        int GetScoreValue() const { return scoreValue; }  // Definicija tukaj
        
        void Update(float deltaTime);
        void Render(SDL_Renderer* renderer);
        
        Vec2 position;
        bool isRescued = false;
        
    private:
        int scoreValue;  // Dodajte člansko spremenljivko
        float rescueTime = 0.0f;
        float rescueDuration = 2.0f;
    };