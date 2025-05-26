#include <iostream>

#include "snakeGame.h"

namespace snake {
SnakeGame::SnakeGame(sf::RenderWindow& window) : Game(window), tileLength0(window.getSize().x / 10) {
    // Размеры окна должны обязательно нацело делитья на длину плитки
    window.setVerticalSyncEnabled(true);

    // Загрузка тексктур поля, еды и змейки
    textures0[0] = new sf::Texture();
    textures0[1] = new sf::Texture();
    textures0[2] = new sf::Texture();
    if (!textures0[0]->loadFromFile(snake::PATH_FIELD) || !textures0[1]->loadFromFile(snake::PATH_FOOD) ||
        !textures0[2]->loadFromFile(snake::PATH_SNAKE)) {
        throw std::runtime_error("Failed to load field texture.");
    }

    // Подсчет количества клеток
    int normalizedWidth = window.getSize().x / tileLength0;
    int normalizedHeight = window.getSize().y / tileLength0;

    field0 = new Field(normalizedWidth, normalizedHeight, tileLength0, textures0[0]);
    food0 = new FoodSpawner(field0, textures0[1]);
    snake0 = new Snake(field0, textures0[2]);
}

SnakeGame::~SnakeGame() {
    delete snake0;
    delete food0;
    delete field0;

    for (sf::Texture* pointer : textures0)
        delete pointer;
}

void SnakeGame::Run() {
    Orientation::dirNum directionNow = Orientation::Stop;

    while (window.isOpen()) {
        // Обработка события нажатия
        while (std::optional<sf::Event> ev = window.pollEvent()) {
            if (ev->is<sf::Event::Closed>())
                window.close();
            if (const sf::Event::KeyPressed* kp = ev->getIf<sf::Event::KeyPressed>()) {
                if (kp->scancode == sf::Keyboard::Scancode::Escape)
                    return;
                directionNow = Orientation::fromKeyToDir(kp->scancode);
            }
        }

        if (endOfGame != true) {
            window.clear();

            snake0->update(directionNow, food0->getCurrentPos());
            if (snake0->isFoodEaten()) {
                food0->respawn();
                score0++;
                window.setTitle(std::string("Snake | Score: ") + std::to_string(score0));
            }

            if (snake0->isDead()) {
                endOfGame = true;
            }

            window.draw(*field0->getRectToDraw());

            for (const sf::Drawable* drawable : snake0->getRectsToDraw())
                window.draw(*drawable);

            window.draw(*food0->getRectToDraw());

            window.display();
        }
    }
}

const std::string SnakeGame::GetName() {
    return "Snake";
}
}  // namespace snake
