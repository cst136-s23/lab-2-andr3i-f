#include <iostream>
#include <SFML/Graphics.hpp>

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

void update(float dt, const Vector<Entity *> & items, Player & player) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { player.moveUp(); }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { player.moveDown(); }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { player.moveLeft(); }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { player.moveRight(); }
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
  Player player{};
  items.append(&player);

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
      update(dt.asSeconds(), items, player);
    }

    render(window, items);
  }
}
