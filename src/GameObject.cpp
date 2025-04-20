// src/GameObject.cpp
#include "GameObject.hpp"

GameObject::GameObject(float x, float y, float w, float h) 
    : x(x), y(y), width(w), height(h) {}

float GameObject::getX() const { return x; }
float GameObject::getY() const { return y; }
float GameObject::getWidth() const { return width; }
float GameObject::getHeight() const { return height; }