#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <vector>

typedef SDL_FPoint Vec2;
typedef SDL_Color Color;

enum class GameState {
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER,
    LEVEL_COMPLETE
};