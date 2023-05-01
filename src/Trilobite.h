#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Alien.h"

class Trilobite : public Alien {
public:
    Trilobite() = default;
    Trilobite(float moveX, float moveY, float positionX, float positionY) {
        health = 250;

        sf::Vector2f size{30.f, 35.f};

        moveX == 0 ? this->moveX = 1 : this->moveX = moveX;
        moveY == 0 ? this->moveY = 1 : this->moveY = moveY;

        shape.setSize(size);
        shape.setFillColor(sf::Color::Yellow);
        shape.setOrigin(size.x / 2, size.y / 2);

        shape.setPosition(positionX, positionY); 
    }

    void render(sf::RenderWindow & window) override {
        window.draw(shape);
    }

    void move() override {
        sf::Vector2f currentPosition{getPosition()};

        if (currentPosition.x < 0 || currentPosition.x > settings::WINDOW_WIDTH) {
            moveX *= -1;
        }
        if (currentPosition.y < 0 || currentPosition.y > settings::WINDOW_HEIGHT) {
            moveY *= -1;
        }

        shape.move(moveX, moveY);
    }

    void kill() override {
        if (health <= 0) { dead = true; }
    }

    bool isDead() override {
        return dead;
    }

    sf::Vector2f getPosition() override { return shape.getPosition(); }
};