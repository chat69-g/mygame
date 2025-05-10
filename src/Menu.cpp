#include "Menu.hpp"
#include "TextureManager.hpp"
#include <SDL2/SDL_ttf.h>
#include <ctime>
#include <algorithm>
#include <iostream>  // Dodano za std::cout
#include <ostream>   // Dodano za std::endl

Menu::Menu() : nameEntered(false) {}

void Menu::displayMenu() {
    std::cout << "=== MENU ===\n";
    std::cout << "1. View Top 5 Scores\n";
    std::cout << "2. Start Game\n";
    std::cout << "3. Replay Last Game\n";
    std::cout << "Enter your choice: ";
}

void Menu::handleInput() {
    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            std::cout << "Top 5 Scores:\n";
            // Prikaz rezultatov (implementirano v ScoreManager)
            break;
        case 2:
            if (!nameEntered) {
                std::cout << "Enter your name: ";
                std::cin >> playerName;
                nameEntered = true;
            }
            break;
        case 3:
            std::cout << "Replaying last game...\n";
            // Replay logika (implementirano v ReplayManager)
            break;
        default:
            std::cout << "Invalid choice. Try again.\n";
            break;
    }
}

std::string Menu::getPlayerName() const {
    return playerName;
}

bool Menu::isNameEntered() const {
    return nameEntered;
}