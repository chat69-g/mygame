#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "TextureManager.hpp"

class Player;
class Map;
class Menu;

class Game {
public:
    enum GameState { MENU, PLAYING, GAME_OVER };
    
    static Game& Instance();
    bool Init(const char* title, int width, int height);
    void Run();
    void Clean();
    
    SDL_Renderer* GetRenderer() const;
    bool IsRunning() const;

private:
    Game();
    ~Game();

    void HandleEvents();
    void Update();
    void Render();
    void RenderGameOver();
    void Reset();

    static Game* sInstance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;
    GameState currentState;
    
    Player* player;
    Map* map;
    Menu* menu;
    TextureManager& textureManager;
};