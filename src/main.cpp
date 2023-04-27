#include <iostream>
#include <SFML/Graphics.hpp>

#include "list.h"

void processEvents(sf::RenderWindow & window) {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
    }
  }
}

void update(float dt, const List<sf::CircleShape> & items) {
  items.for_each([&](auto & item) {
    item.move(5*dt, 10*dt);
  });
}

void render(sf::RenderWindow & window, const List<sf::CircleShape> & items) {
  // always clear
  window.clear();

  // draw whatever
  items.for_each([&](const auto & item) {
    window.draw(item);
  });

  // swap the buffer
  window.display();
}

int main() {
  sf::RenderWindow window{sf::VideoMode{800, 600}, "MyProject"};
  window.setVerticalSyncEnabled(true);

  List<sf::CircleShape> items{};

  sf::CircleShape circle{15};
  circle.setFillColor(sf::Color::Cyan);
  circle.setPosition(100, 100);

  items.append(circle);

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
      update(dt.asSeconds(), items);
    }

    render(window, items);
  }
}
