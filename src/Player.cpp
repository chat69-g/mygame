#include "Player.hpp"
#include "TextureManager.hpp"
#include "Game.hpp"
#include <iostream>

Player::Player() : position{0, 0}, health(3), score(0) {}

Player::~Player() {
    // Texture is managed by TextureManager
}

void Player::HandleInput(const Uint8* keystate) {
    float speed = 200.0f; // Hitrost gibanja
    
    if (keystate[SDL_SCANCODE_W]) position.y -= speed * Game::Instance().GetDeltaTime();
    if (keystate[SDL_SCANCODE_S]) position.y += speed * Game::Instance().GetDeltaTime();
    if (keystate[SDL_SCANCODE_A]) position.x -= speed * Game::Instance().GetDeltaTime();
    if (keystate[SDL_SCANCODE_D]) position.x += speed * Game::Instance().GetDeltaTime();
}
void Player::TakeDamage(int amount) {
    health -= amount;
    if (health <= 0) {
        Game::Instance().ChangeState(GameState::GAME_OVER);
    }
}

void Player::HandleEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_w: y -= speed; break;
            case SDLK_s: y += speed; break;
            case SDLK_a: x -= speed; break;
            case SDLK_d: x += speed; break;
        }
        std::cout << "Player position: (" << x << ", " << y << ")" << std::endl;
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