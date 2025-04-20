#pragma once
#include "common.hpp"
#include <vector>

struct Particle {
    Vec2 position;
    Vec2 velocity;
    float lifetime;
    Color color;
};

class Farm {
public:
    Farm(const Vec2& position);
    
    void Update(float deltaTime);
    void Render(SDL_Renderer* renderer);
    void Destroy();
    bool IsDestroyed() const { return isDestroyed; }
    
    Vec2 position;
    
private:
    bool isDestroyed;
    float destructionProgress;
    std::vector<Particle> particles;
    SDL_Texture* texture;
};