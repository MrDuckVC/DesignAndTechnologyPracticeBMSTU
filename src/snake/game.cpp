#include <iostream>

#include "game.h"

Game::Game(sf::RenderWindow *window) : window0(window), tileLength0(20) {
  // Размеры окна должны обязательно нацело делитья на длину плитки
  window0->setVerticalSyncEnabled(true);

  // Загрузка тексктуры поля
  textures0[0] = new sf::Texture();
  textures0[0]->loadFromFile("assets/snake/field.png");

  int normalizedWidth = window0->getSize().x / tileLength0;
  int normalizedHeight = window0->getSize().y / tileLength0;

  field0 = new Field(normalizedWidth, normalizedHeight, tileLength0,
                         textures0[0]);

  // Загрузка текстуры еды
  textures0[1] = new sf::Texture();
  textures0[1]->loadFromFile("assets/snake/food.png");

  food0 = new FoodSpawner(field0, textures0[1]);

  // Загрузка текстуры змейки
  textures0[2] = new sf::Texture();
  textures0[2]->loadFromFile("assets/snake/snake.png");

  snake0 = new Snake(field0, textures0[2]);
}

Game::~Game() {
  delete snake0;
  delete food0;
  delete field0;

  for (auto pointer : textures0)
    delete pointer;
}

void Game::loop() {
  Orientation::dirNum directionNow = Orientation::Stop;

  while (window0->isOpen()) {
    // Обработка события нажатия
    while (auto ev = window0->pollEvent()) {
      if (ev->is<sf::Event::Closed>())
        window0->close();
      if (auto *kp = ev->getIf<sf::Event::KeyPressed>()) {
        if (kp->scancode == sf::Keyboard::Scancode::Escape)
          window0->close();
        directionNow = Orientation::fromKeyToDir(kp->scancode);
      }
    }

    if (endOfGame != true) {
      window0->clear();

      snake0->update(directionNow, food0->getCurrentPos());
      if (snake0->isFoodEaten()) {
        food0->respawn();
        score0++;
        window0->setTitle(std::string("Snake | Score: ") +
                          std::to_string(score0));
      }

      if (snake0->isDead()) {
        std::cout << "You are dead :( Your score: " << score0 << "!"
                  << std::endl;
        std::cout << "\nPress Esc to close the game." << std::endl;
        endOfGame = true;
      }

      window0->draw(*field0->getRectToDraw());

      for (auto drawable : snake0->getRectsToDraw())
        window0->draw(*drawable);

      window0->draw(*food0->getRectToDraw());

      window0->display();
    }
  }
}
