#pragma once

#include "foodSpawner.h"
#include "snake.h"

#include "../games/game.h"

class SnakeGame : public game::Game {
 private:
    sf::Texture* textures0[3];  // 0 - field, 1 - food, 2 - snake

    Field* field0;
    int tileLength0;

    FoodSpawner* food0;
    Snake* snake0;

    int score0 = 0;

    bool endOfGame = false;

 public:
    SnakeGame(sf::RenderWindow& window);
    ~SnakeGame();

    void Run();
    const std::string GetName() override;
};
