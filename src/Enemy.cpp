#include "Enemy.hpp"
#include "TextureManager.hpp"

Enemy::Enemy(int x, int y) : x(x), y(y), health(50), damage(10) {
    texture = TextureManager::getInstance().get("enemy");
}

Enemy::~Enemy() {
    // Texture managed by TextureManager
}

void Enemy::Update() {
    // Simple AI movement would go here
}

void Enemy::Render(SDL_Renderer* renderer) {
    SDL_Rect destRect = {x, y, 50, 50};
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}

void Enemy::TakeDamage(int amount) {
    health -= amount;
}

bool Enemy::IsDead() const {
    return health <= 0;
}