#pragma once

#include <SFML/Graphics.hpp>

class Entity {
public:
    virtual void render(sf::RenderWindow & window) = 0;
    virtual void move() = 0;
    virtual sf::Vector2f getPosition() = 0;
    virtual void forceKill() = 0;
    virtual void kill() = 0;
    virtual bool isDead() = 0;
    virtual void hit() = 0;
    virtual int type() = 0;
    virtual sf::FloatRect getBounds() = 0;
    virtual ~Entity() {}
};