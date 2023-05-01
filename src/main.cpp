// Object images used from https://opengameart.org/content/shoot-em-up-enemies
// Background image used from https://opengameart.org/content/galaxy-skybox

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

  items.for_each([&](Entity * item) {
    item->move();
    item->kill();

    // Checks for collisions, player type = 0, alien type = 1,
    // trilobite type = 2, bullet type = 3
    int oneType{ item->type() };
    items.for_each([&](Entity * itemTwo) {
      if (!itemTwo->isDead() && !item->isDead()) {
        int twoType{ itemTwo->type() };

        if (oneType == 0 && (twoType == 1 || twoType == 2)) {
          if (item->getBounds().intersects(itemTwo->getBounds())) {
            itemTwo->forceKill();
            item->hit();
          }
        }
        else if (oneType == 3 && (twoType == 1 || twoType == 2)) {
          if (item->getBounds().intersects(itemTwo->getBounds())) {
            item->forceKill();
            itemTwo->hit();
          }
        }
        else if (twoType == 0 && (oneType == 1 || oneType == 2)) {
          if (item->getBounds().intersects(itemTwo->getBounds())) {
            item->forceKill();
            itemTwo->hit();
          }
        }
        else if (twoType == 3 && (oneType == 1 || oneType == 2)) {
          if (item->getBounds().intersects(itemTwo->getBounds())) {
            itemTwo->forceKill();
            item->hit();
          }
        }
      }
    });
  });
}

void render(sf::RenderWindow & window, Vector<Entity *> & items, sf::Sprite & bgImage, sf::Text gameOverText, sf::Text gameWonText, bool & gameWon) {
  // always clear
  window.clear();

  // draw whatever
  window.draw(bgImage);
  items.for_each([&](Entity * item){
    item->render(window);
  });

  if (items[0]->type() != 0) {
    window.draw(gameOverText);
  }

  if (items.size() == 1) { 
    gameWon = true;
  }

  if (gameWon) {
    window.draw(gameWonText);
  }

  // swap the buffer
  window.display();
}

int main() {
  sf::RenderWindow window{sf::VideoMode{settings::WINDOW_WIDTH, settings::WINDOW_HEIGHT}, "Alien Invader"};
  window.setVerticalSyncEnabled(true);

  Vector<Entity *> items{};
  Player * player = new Player{};
  items.append(player);

  sf::Font font;
  sf::Text gameOverText;
  sf::Text gameWonText;

  bool gameWon{ false };

  if (!font.loadFromFile("fonts\\arial.ttf")) {
    std::cerr << "Could not load arial font\n";
  }

  gameOverText.setFont(font);
  gameOverText.setCharacterSize(50);
  gameOverText.setStyle(sf::Text::Bold);
  gameOverText.setString("GAME OVER L");
  gameOverText.setPosition(sf::Vector2f(((settings::WINDOW_WIDTH / 2) - 175), settings::WINDOW_HEIGHT / 2));

  gameWonText.setFont(font);
  gameWonText.setCharacterSize(50);
  gameWonText.setStyle(sf::Text::Bold);
  gameWonText.setString("GAME WON NERD");
  gameWonText.setPosition(sf::Vector2f(((settings::WINDOW_WIDTH / 2) - 225), settings::WINDOW_HEIGHT / 2));

  sf::Texture backgroundImage;
  if (!backgroundImage.loadFromFile("images\\galaxy.png")) {
    std::cerr << "Could not find galaxy image\n";
  }
  sf::Sprite backgroundSprite(backgroundImage);

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

    render(window, items, backgroundSprite, gameOverText, gameWonText, gameWon);
  }

  items.remove_if([&](Entity * item) { 
    return true;
  });
}
