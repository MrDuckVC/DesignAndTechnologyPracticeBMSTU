#pragma once

#include "const.h"
#include "foodSpawner.h"
#include "snake.h"

#include "../games/game.h"

namespace snake {
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

    void Run() override;
    const std::string GetName() override;
};
}  // namespace snake
