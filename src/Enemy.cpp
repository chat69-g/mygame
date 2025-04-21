#include "Enemy.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cmath>
#include <memory>   // For smart pointers
#include <queue>

using namespace std;

Enemy::Enemy(const Vec2& startPos) : 
    position(startPos), velocity{0,0}, health(3), isActive(true),
    speed(150.0f), attackRange(50.0f), detectionRange(200.0f) {
    
    texture = IMG_LoadTexture(Game::Instance().GetRenderer(), "assets/enemy.png");
    if(!texture) {
        cerr << "Failed to load enemy texture: " << IMG_GetError() << endl;
    }
}

void Enemy::Update(float deltaTime, const Player& player, const Map& map) {
    if(!isActive) return;

    float distToPlayer = sqrt(pow(player.position.x - position.x, 2) + 
                         pow(player.position.y - position.y, 2));

    if(distToPlayer < detectionRange) {
        if(distToPlayer > attackRange) {
            CalculatePath(player.position, map);
            MoveAlongPath(deltaTime);
        } else {
            AttackPlayer(const_cast<Player&>(player));
        }
    }
}

void Enemy::Render(SDL_Renderer* renderer) {
    if(!isActive) return;
    
    SDL_Rect dest = {static_cast<int>(position.x), 
               static_cast<int>(position.y), 32, 32};
    SDL_RenderCopy(renderer, texture, nullptr, &dest);
}

void Enemy::AttackPlayer(Player& player) {
    player.TakeDamage(1);
}

void Enemy::CalculatePath(const Vec2& target, const Map& map) {
    currentPath.clear();
    
    Vec2 current = {position.x / 32, position.y / 32};
    Vec2 goal = {target.x / 32, target.y / 32};
    
    while(current.x != goal.x || current.y != goal.y) {
        // Check walkable tiles using map
        if(current.x < goal.x && map.IsPositionWalkable({(current.x+1)*32, current.y*32})) {
            current.x++;
        }
        else if(current.x > goal.x && map.IsPositionWalkable({(current.x-1)*32, current.y*32})) {
            current.x--;
        }
        
        if(current.y < goal.y && map.IsPositionWalkable({current.x*32, (current.y+1)*32})) {
            current.y++;
        }
        else if(current.y > goal.y && map.IsPositionWalkable({current.x*32, (current.y-1)*32})) {
            current.y--;
        }
        
        currentPath.push_back({current.x * 32, current.y * 32});
    }
}

void Enemy::MoveAlongPath(float deltaTime) {
    if(currentPath.empty()) return;
    
    Vec2 target = currentPath.front();
    Vec2 direction = {target.x - position.x, target.y - position.y};
    
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if(length > 0) {
        direction.x /= length;
        direction.y /= length;
    }
    
    position.x += direction.x * speed * deltaTime;
    position.y += direction.y * speed * deltaTime;
    
    if(abs(position.x - target.x) < 5 && abs(position.y - target.y) < 5) {
        currentPath.erase(currentPath.begin());
    }
}