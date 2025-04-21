#include "Player.hpp"
#include "TextureManager.hpp"
#include "Game.hpp"

Player::Player() : 
    x(100), y(100), width(50), height(50), 
    health(100), speed(5) {
    texture = TextureManager::getInstance().get("player");
}

Player::~Player() {
    // Texture is managed by TextureManager
}

void Player::HandleEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_w: y -= speed; break;
            case SDLK_s: y += speed; break;
            case SDLK_a: x -= speed; break;
            case SDLK_d: x += speed; break;
        }
    }
}

void Player::Update() {
    // Collision detection and other updates would go here
}

void Player::Render(SDL_Renderer* renderer) {
    SDL_Rect destRect = {x, y, width, height};
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}

bool Player::IsDead() const {
    return health <= 0;
}

void Player::TakeDamage(int amount) {
    health -= amount;
}