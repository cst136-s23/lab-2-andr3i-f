#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Alien.h"

class Trilobite : public Alien {
public:
    Trilobite() = default;
    Trilobite(float moveX, float moveY, float positionX, float positionY) {
        if (!texture.loadFromFile("images\\trilobite.png")) {
            std::cerr << "Could not find trilobite image\n";
        }

        shape.setTexture(texture);

        health = 250;

        moveX == 0 ? this->moveX = 1 : this->moveX = moveX;
        moveY == 0 ? this->moveY = 1 : this->moveY = moveY;

        shape.setOrigin(shape.getTextureRect().width / 2, shape.getTextureRect().height / 2);

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

    void forceKill() override {
        dead = true;
    }

    void kill() override {
        if (health <= 0) { dead = true; }
    }

    bool isDead() override {
        return dead;
    }

    void hit() override {
        health -= 10;
    }

    int type() override {
        return 2;
    }

    sf::FloatRect getBounds() override {
        return shape.getGlobalBounds();
    }

    sf::Vector2f getPosition() override { return shape.getPosition(); }
};