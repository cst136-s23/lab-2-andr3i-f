#pragma once

#include <SFML/Graphics.hpp>

class Entity {
public:
    virtual void render(sf::RenderWindow & window) = 0;
    virtual void move() = 0;
    virtual ~Entity() {}
};