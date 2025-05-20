#include <iostream>

#include "snakeGame.h"

SnakeGame::SnakeGame(sf::RenderWindow& window) : Game(window), tileLength0(20) {
  // Размеры окна должны обязательно нацело делитья на длину плитки
  window.setVerticalSyncEnabled(true);

  // Загрузка тексктуры поля
  textures0[0] = new sf::Texture();
  textures0[0]->loadFromFile("assets/snake/field.png");

  int normalizedWidth = window.getSize().x / tileLength0;
  int normalizedHeight = window.getSize().y / tileLength0;

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

SnakeGame::~SnakeGame() {
  delete snake0;
  delete food0;
  delete field0;

  for (auto pointer : textures0)
    delete pointer;
}

void SnakeGame::loop() {
  Orientation::dirNum directionNow = Orientation::Stop;

  while (window.isOpen()) {
    // Обработка события нажатия
    while (auto ev = window.pollEvent()) {
      if (ev->is<sf::Event::Closed>())
        window.close();
      if (auto *kp = ev->getIf<sf::Event::KeyPressed>()) {
        if (kp->scancode == sf::Keyboard::Scancode::Escape)
          window.close();
        directionNow = Orientation::fromKeyToDir(kp->scancode);
      }
    }

    if (endOfGame != true) {
      window.clear();

      snake0->update(directionNow, food0->getCurrentPos());
      if (snake0->isFoodEaten()) {
        food0->respawn();
        score0++;
        window.setTitle(std::string("Snake | Score: ") +
                          std::to_string(score0));
      }

      if (snake0->isDead()) {
        std::cout << "You are dead :( Your score: " << score0 << "!"
                  << std::endl;
        std::cout << "\nPress Esc to close the game." << std::endl;
        endOfGame = true;
      }

      window.draw(*field0->getRectToDraw());

      for (auto drawable : snake0->getRectsToDraw())
        window.draw(*drawable);

      window.draw(*food0->getRectToDraw());

      window.display();
    }
  }
}
