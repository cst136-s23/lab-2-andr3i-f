#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.h"

class Alien : public Entity {
public:
    Alien() = default;
    Alien(float moveX, float moveY, float positionX, float positionY) {
        if (!texture.loadFromFile("images/alien.png")) {
            std::cerr << "Could not find alien image\n";
        }

        shape.setTexture(texture);
        
        healthBarMax.setSize(sf::Vector2f(25.f, 4.f));
        healthBarMax.setFillColor(sf::Color::Red);
        healthBarMax.setPosition((positionX - 13.f) , (positionY - 38.f));
        
        healthBar.setSize(sf::Vector2f(25.f, 4.f));
        healthBar.setFillColor(sf::Color::Green);
        healthBar.setPosition((positionX - 13.f) , (positionY - 38.f));

        health = 150.f;
        healthMax = 150.f;

        sf::Vector2f size{20.f, 25.f};

        moveX == 0 ? this->moveX = 1 : this->moveX = moveX;
        moveY == 0 ? this->moveY = 1 : this->moveY = moveY;

        shape.setOrigin(shape.getTextureRect().width / 2, shape.getTextureRect().height / 2);

        shape.setPosition(positionX, positionY);
    }

    void render(sf::RenderWindow & window) override {
        window.draw(healthBarMax);
        window.draw(healthBar);
        window.draw(shape);
    }

    sf::Vector2f getPosition() override { return shape.getPosition(); }

    void move() {
        sf::Vector2f currentPosition{getPosition()};

        if (currentPosition.x < 0 || currentPosition.x > settings::WINDOW_WIDTH) {
            moveX *= -1;
        }
        if (currentPosition.y < 0 || currentPosition.y > settings::WINDOW_HEIGHT) {
            moveY *= -1;
        }

        shape.move(moveX, moveY);
        healthBar.move(moveX, moveY);
        healthBarMax.move(moveX, moveY);
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
        healthBar.setSize(sf::Vector2f(((health / healthMax) * 25.f), 4.f));
    }

    int type() override {
        return 1;
    }

    sf::FloatRect getBounds() override {
        return shape.getGlobalBounds();
    }

protected:
    sf::Sprite shape;
    sf::Texture texture;

    sf::RectangleShape healthBar;
    sf::RectangleShape healthBarMax;

    float health{};
    float healthMax{};
    bool dead{ false };

    float moveX{};
    float moveY{};
};