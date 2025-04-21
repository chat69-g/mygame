#include "Farm.hpp"
#include "Game.hpp"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <random>

using namespace std;

Farm::Farm(const Vec2& pos) : 
    position(pos), isDestroyed(false), destructionProgress(0) {
    
    texture = IMG_LoadTexture(Game::Instance().GetRenderer(), "assets/farm.png");
    if(!texture) {
        cerr << "Failed to load farm texture: " << IMG_GetError() << endl;
    }
}

void Farm::Update(float deltaTime) {
    if(isDestroyed) {
        for(auto& p : particles) {
            p.position.x += p.velocity.x * deltaTime;
            p.position.y += p.velocity.y * deltaTime;
            p.lifetime -= deltaTime;
        }
        
        particles.erase(remove_if(particles.begin(), particles.end(),
            [](const Particle& p) { return p.lifetime <= 0; }), particles.end());
    }
}

void Farm::Render(SDL_Renderer* renderer) {
    if(isDestroyed) {
        for(auto& p : particles) {
            SDL_SetRenderDrawColor(renderer, p.color.r, p.color.g, p.color.b, p.color.a);
            SDL_RenderDrawPoint(renderer, static_cast<int>(p.position.x), 
                              static_cast<int>(p.position.y));
        }
    } else {
        SDL_Rect dest = {static_cast<int>(position.x), 
                       static_cast<int>(position.y), 64, 64};
        SDL_RenderCopy(renderer, texture, nullptr, &dest);
    }
}

void Farm::Destroy() {
    if(isDestroyed) return;
    
    isDestroyed = true;
    destructionProgress = 1.0f;
    
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> velDist(-100.0, 100.0);
    uniform_int_distribution<> lifeDist(500, 1000);
    uniform_int_distribution<> colorDist(150, 255);
    
    for(int i = 0; i < 100; i++) {
        Particle p;
        p.position = {position.x + 32, position.y + 32};
        p.velocity = {static_cast<float>(velDist(gen)), 
                     static_cast<float>(velDist(gen))};
        p.lifetime = lifeDist(gen) / 1000.0f;
        p.color = {static_cast<Uint8>(colorDist(gen)),
                  static_cast<Uint8>(colorDist(gen)),
                  static_cast<Uint8>(colorDist(gen)), 255};
        particles.push_back(p);
    }
    
    Game::Instance().player->DestroyFarm();
}