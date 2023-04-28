#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>

#include "Entity.h"
#include "Player.h"
#include "settings.h"

class Bullet : public Entity {
public:
    Bullet() = default;
    Bullet(Player & player, sf::Vector2i mousePosition) {
        sf::Vector2f size{2.5f, 3.f};
        sf::Vector2f playerPosition{ player.getPosition() };

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

private:
    sf::RectangleShape shape;
    sf::Vector2f direction;
};