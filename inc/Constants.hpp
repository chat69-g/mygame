// include/Constants.hpp
#pragma once

namespace Constants {
    // Window
    inline const int SCREEN_WIDTH = 800;
    inline const int SCREEN_HEIGHT = 600;
    inline const char* WINDOW_TITLE = "My Game";
    
    // Gameplay
    inline const float GRAVITY = 0.5f;
    inline const float JUMP_FORCE = -10.0f;
    inline const float PLAYER_SPEED = 5.0f;
    
    // Tiles
    inline const int TILE_SIZE = 32;
    const char WALL = '#';
    const char PLAYER = 'P';
    const char EMPTY = ' ';
    const char GOAL = 'G';
    const char SPIKE = '^';
    const char PLATFORM = '=';
    
    // Colors
    const unsigned int PLAYER_COLOR = 0xFF0000FF; // RGBA
    const unsigned int WALL_COLOR = 0xFFFFFFFF;
    const unsigned int GOAL_COLOR = 0x00FF00FF;
}