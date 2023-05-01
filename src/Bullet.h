#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

#include "Entity.h"
#include "Player.h"
#include "settings.h"

class Bullet : public Entity {
public:
    Bullet() = default;
    Bullet(sf::Vector2f playerPosition, sf::Vector2i mousePosition) {
        sf::Vector2f size{4.f, 4.f};

        shape.setSize(size);
        shape.setFillColor(sf::Color::Yellow);
        shape.setOrigin(size.x / 2, size.y / 2);
        shape.setPosition(playerPosition);

        sf::Vector2f resultant{ playerPosition - static_cast<sf::Vector2f>(mousePosition) };
        float length{ sqrtf(powf(resultant.x, 2) + powf(resultant.y, 2)) };
        direction = sf::Vector2f( - resultant.x / length, - resultant.y / length);
    }

    void render(sf::RenderWindow & window) override {
        window.draw(shape);
    }

    void move() override {
        shape.move(direction * settings::bulletSpeed);
    }

    sf::Vector2f getPosition() override { return shape.getPosition(); }

    void forceKill() override {
        dead = true;
    }

    void kill() override {
        sf::Vector2f currentPosition{getPosition()};

        if (currentPosition.x < 0 || currentPosition.x > settings::WINDOW_WIDTH) {
            dead = true;
        }
        if (currentPosition.y < 0 || currentPosition.y > settings::WINDOW_HEIGHT) {
            dead = true;
        }
    }

    bool isDead() override {
        return dead;
    }

    void hit() override {}

    int type() override {
        return 3;
    }

    sf::FloatRect getBounds() override {
        return shape.getGlobalBounds();
    }

private:
    sf::RectangleShape shape;
    sf::Vector2f direction;

    bool dead{ false };
};