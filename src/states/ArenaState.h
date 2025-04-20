#pragma once
#include "State.h"
#include "../entities/Player.h"
#include "../entities/Portal.h"
#include "../entities/Enemy.h"

class ArenaState : public State {
public:
    void init() override;
    void handleEvents() override;
    void update(float deltaTime) override;
    void render() override;

private:
    Player player;
    std::vector<Enemy> enemies;
    Portal entryPortal;
    Portal exitPortal;
    int score = 0;
};