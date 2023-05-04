#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Alien.h"

class Trilobite : public Alien {
public:
    Trilobite() = default;
    Trilobite(float moveX, float moveY, float positionX, float positionY) {
        if (!texture.loadFromFile("images/trilobite.png")) {
            std::cerr << "Could not find trilobite image\n";
        }

        shape.setTexture(texture);

        health = 300.f;
        healthMax = 300.f;

        healthBarMax.setSize(sf::Vector2f(25.f, 4.f));
        healthBarMax.setFillColor(sf::Color::Red);
        healthBarMax.setPosition((positionX - 13.f) , (positionY - 36.f));
        
        healthBar.setSize(sf::Vector2f(25.f, 4.f));
        healthBar.setFillColor(sf::Color::Green);
        healthBar.setPosition((positionX - 13.f) , (positionY - 36.f));

        moveX == 0 ? this->moveX = 1 : this->moveX = moveX;
        moveY == 0 ? this->moveY = 1 : this->moveY = moveY;

        shape.setOrigin(shape.getTextureRect().width / 2, shape.getTextureRect().height / 2);

        shape.setPosition(positionX, positionY); 
    }
};