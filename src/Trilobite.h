#pragma once

#include <SFML/Graphics.hpp>

#include "Alien.h"

class Trilobite : public Alien {
public:
    Trilobite() = default;
    Trilobite(float moveX, float moveY, float positionX, float positionY) {
        sf::Vector2f size{30.f, 35.f};
        this->moveX = moveX;
        this->moveY = moveY;

        shape.setSize(size);
        shape.setFillColor(sf::Color::Yellow);
        shape.setOrigin(size.x / 2, size.y / 2);

        shape.setPosition(positionX, positionY); 
    }

    void render(sf::RenderWindow & window) override {
        window.draw(shape);
    }

    void move() override {
        shape.move(moveX, moveY);
    }
};