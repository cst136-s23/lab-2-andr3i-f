#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "vector.h"
#include "Bullet.h"

class Player : public Entity {
public:
    Player(Vector<Entity *> & gameObjects) {
        sf::Vector2f size{30.f, 45.f};
        items = gameObjects;
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

    void move() override {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { moveUp(); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { moveDown(); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { moveLeft(); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { moveRight(); }
    }

    sf::Vector2f getPosition() override { return shape.getPosition(); }

    void kill() override {
        if (health <= 0) { dead = true; }
    }

    bool isDead() override {
        return dead;
    }
    
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

    Vector<Entity *> items{};

    bool dead{ false };
    int health = 100;
};