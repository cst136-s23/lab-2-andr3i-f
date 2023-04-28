#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.h"

class Player : public Entity {
public:
    Player() {
        sf::Vector2f size{30.f, 45.f};
        moveX = 1.f;
        moveY = 1.f;


        shape.setSize(size);
        shape.setFillColor(sf::Color::Blue);
        shape.setOrigin(size.x / 2, size.y / 2);

        shape.setPosition(400, 400);
    };

    void render(sf::RenderWindow & window) override {
        window.draw(shape);
    }

    void move() override {}

    sf::Vector2f getPosition() { return shape.getPosition(); }

    void moveUp() {
        shape.move(0, -moveY);
    }

    void moveDown() {
        shape.move(0, moveY);
    }

    void moveLeft() {
        shape.move(-moveX, 0);
    }

    void moveRight() {
        shape.move(moveX, 0);
    }

private:
    sf::RectangleShape shape;
    float moveX{};
    float moveY{};
};