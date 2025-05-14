#include "Player.hpp"
#include <cstdlib>
using namespace std; // Da lahko uporabljamo standardne funkcije brez std::

Player::Player(int maxX, int maxY) : lives(3), lastMoveTime(0), speed(200) {
    // Inicializacija igralca na naključnih koordinatah znotraj meja
    x = rand() % maxX;
    y = rand() % maxY;
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x >= maxX) x = maxX - 1;
    if (y >= maxY) y = maxY - 1;
}

void Player::update(const Uint8* keyState) {
    // Posodobi pozicijo igralca glede na pritisnjene tipke
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastMoveTime < speed) {
        return; // Prepreči premikanje, če še ni minilo dovolj časa
    }
    lastMoveTime = currentTime;

    if (keyState[SDL_SCANCODE_W] && y > 0) --y; // Premik gor
    if (keyState[SDL_SCANCODE_S] && y < 29) ++y; // Premik dol
    if (keyState[SDL_SCANCODE_A] && x > 0) --x; // Premik levo
    if (keyState[SDL_SCANCODE_D] && x < 39) ++x; // Premik desno
}

void Player::move(char direction) {
    // Premik igralca glede na podano smer
    switch (direction) {
        case 'w': --y; break; // Gor
        case 's': ++y; break; // Dol
        case 'a': --x; break; // Levo
        case 'd': ++x; break; // Desno
    }
}

void Player::loseLife() {
    // Zmanjšaj število življenj igralca
    if (lives > 0) {
        --lives;
    }
}

bool Player::isAlive() const {
    // Preveri, ali ima igralec še življenja
    return lives > 0;
}

bool Player::hasExitedFarm() const {
    // Preveri, ali je igralec zapustil farmo (izven meja)
    return x < 0 || y < 0 || x >= 40 || y >= 30;
}