#pragma once

namespace Constants {
    // Okno
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const char* WINDOW_TITLE = "My Game";
    
    // Igralec
    const int TILE_SIZE = 32;
    const float GRAVITY = 0.5f;
    const float JUMP_FORCE = -10.0f;
    const float PLAYER_SPEED = 5.0f;
    
    // Tipi tilov
    const char WALL = '#';
    const char PLAYER = 'P';
    const char EMPTY = ' ';
    const char GOAL = 'G';
    const char SPIKE = '^';
    const char PLATFORM = '=';
}