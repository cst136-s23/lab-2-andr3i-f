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
        if (!texture.loadFromFile("images/player.png")) {
            std::cerr << "Could not find player image\n";
        }

        shape.setTexture(texture);

        if (!font.loadFromFile("fonts/arial.ttf")) {
            std::cerr << "Could not load arial font\n";
        }

        text.setFont(font);
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(18);
        text.setStyle(sf::Text::Bold);
        text.setString("Player Health");
        text.setPosition(sf::Vector2f(6.f, 5.f));

        healthBarMax.setSize(sf::Vector2f(124.f, 20.f));
        healthBarMax.setFillColor(sf::Color::Red);
        healthBarMax.setPosition(sf::Vector2f(5.f, 5.f));

        healthBar.setSize(sf::Vector2f(124.f, 20.f));
        healthBar.setFillColor(sf::Color::Green);
        healthBar.setPosition(sf::Vector2f(5.f, 5.f));

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

        window.draw(healthBarMax);
        window.draw(healthBar);
        window.draw(text);

        window.draw(shape);
    }

    void move() override {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { moveUp(); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { moveDown(); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { moveLeft(); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { moveRight(); }
    }

    sf::Vector2f getPosition() override { return shape.getPosition(); }

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
        healthBar.setSize(sf::Vector2f(((health / healthMax) * 124.f), 20.f));
    }

    int type() override {
        return 0;
    }

    sf::FloatRect getBounds() override {
        return shape.getGlobalBounds();
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

    sf::Font font;
    sf::Text text;
    sf::RectangleShape healthBar;
    sf::RectangleShape healthBarMax;

    float moveX{};
    float moveY{};

    bool dead{ false };
    float health = 100.f;
    float healthMax = 100.f;
};