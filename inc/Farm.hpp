#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "Animal.hpp"

class Farm {
    public:
        ~Farm();
        int CollectAnimals();
        void AddAnimal(Animal* animal);
        
    private:
        std::vector<Animal*> animals;  // Vektor kazalcev po vzoru GameRPA-13
    };