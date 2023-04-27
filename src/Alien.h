#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.h"

class Alien : public Entity {
public:
    Alien() = default;
    Alien(float moveX, float moveY, float positionX, float positionY) {
        sf::Vector2f size{20.f, 25.f};
        this->moveX = moveX;
        this->moveY = moveY;

        shape.setSize(size);
        shape.setFillColor(sf::Color::Green);
        shape.setOrigin(size.x / 2, size.y / 2);

        shape.setPosition(positionX, positionY);
    }

    void render(sf::RenderWindow & window) override {
        window.draw(shape);
    }

    void move() {
        shape.move(moveX, moveY);
    }

protected:
    sf::RectangleShape shape;
    float moveX{};
    float moveY{};
};