// include/Constants.hpp
#pragma once

namespace Constants {
    // Window
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const char* WINDOW_TITLE = "My Game";
    
    // Gameplay
    const float GRAVITY = 0.5f;
    const float JUMP_FORCE = -10.0f;
    const float PLAYER_SPEED = 5.0f;
    
    // Tiles
    const int TILE_SIZE = 32;
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