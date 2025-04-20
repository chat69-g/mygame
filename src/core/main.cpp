#include "core/Game.h"

int main(int argc, char* argv[]) {
    auto& game = Game::getInstance();
    game.init("MYGAME_Bikec", 800, 600);
    game.run();
    game.cleanup();
    return 0;
}