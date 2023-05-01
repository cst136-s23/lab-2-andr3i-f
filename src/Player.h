#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

#include "Entity.h"
#include "vector.h"
#include "Bullet.h"

#define PI 3.14159265

class Player : public Entity {
public:
    Player() {
        if (!texture.loadFromFile("images\\player.png")) {
            std::cerr << "Could not find player image\n";
        }

        shape.setTexture(texture);

        moveX = 1.f;
        moveY = 1.f;

        shape.setOrigin(shape.getTextureRect().width / 2, shape.getTextureRect().height / 2);

        shape.setPosition(400, 400);
    };

    void render(sf::RenderWindow & window) override {
        sf::Vector2f currentPosition{ getPosition() };
        sf::Vector2f mousePosition{ sf::Mouse::getPosition(window) };

        float dx{ currentPosition.x - mousePosition.x };
        float dy{ currentPosition.y - mousePosition.y };

        float rotation{ static_cast<float>(atan2(dy, dx) * 180 / PI) };
        
        shape.setRotation(rotation + 180);

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
    sf::Sprite shape;
    sf::Texture texture;

    float moveX{};
    float moveY{};

    bool dead{ false };
    int health = 100;
};