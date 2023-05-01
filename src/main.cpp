// Images used from https://opengameart.org/content/shoot-em-up-enemies

#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>

#include "vector.h"
#include "settings.h"
#include "Entity.h"
#include "Player.h"
#include "Alien.h"
#include "Trilobite.h"
#include "Bullet.h"

void processEvents(sf::RenderWindow & window) {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
    }
  }
}

void update(float dt, Vector<Entity *> & items, sf::RenderWindow & window) {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    items.append(new Bullet{ items[0]->getPosition(), sf::Mouse::getPosition(window)});
  }

  items.for_each([](Entity * item) {
    item->move();
    item->kill();
  });
}

void render(sf::RenderWindow & window, const Vector<Entity *> & items) {
  // always clear
  window.clear();

  // draw whatever
  items.for_each([&](Entity * item){
    item->render(window);
  });

  // swap the buffer
  window.display();
}

int main() {
  sf::RenderWindow window{sf::VideoMode{settings::WINDOW_WIDTH, settings::WINDOW_HEIGHT}, "Alien Invader"};
  window.setVerticalSyncEnabled(true);

  Vector<Entity *> items{};
  Player * player = new Player{};
  items.append(player);

  std::random_device rd;

  std::uniform_int_distribution<int> distanceX(0, settings::WINDOW_WIDTH);
  std::uniform_int_distribution<int> distanceY(0, settings::WINDOW_HEIGHT);

  std::uniform_int_distribution<int> moveX(-2, 2);
  std::uniform_int_distribution<int> moveY(-2, 2);

  for (size_t i{}; i < 20; ++i) {
    float x{static_cast<float>(distanceX(rd))};
    float y{static_cast<float>(distanceY(rd))};

    float xSpeed{static_cast<float>(moveX(rd))};
    float ySpeed{static_cast<float>(moveY(rd))};
    
    i % 2 == 0 ? items.append(new Alien{xSpeed, ySpeed, x, y}) : items.append(new Trilobite{xSpeed, ySpeed, x, y});
  }

  // https://subscription.packtpub.com/book/game+development/9781849696845/1/ch01lvl1sec11/game-loops-and-frames
  // https://gafferongames.com/post/fix_your_timestep/
  sf::Clock clock;
  sf::Time t{sf::Time::Zero}; // time
  sf::Time dt{sf::seconds(1.0f / 60.0f)}; // delta time (fixed to 60fps)

  while (window.isOpen()) {
    processEvents(window);
    t += clock.restart();

    while (t > dt) {
      t -= dt;
      processEvents(window);
      update(dt.asSeconds(), items, window);
    }

    items.remove_if([](Entity * item) {
      return item->isDead();
    });

    render(window, items);
  }

  items.remove_if([&](Entity * item) { 
    return true;
  });
}
