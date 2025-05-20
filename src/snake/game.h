#pragma once

#include "foodSpawner.h"
#include "snake.h"

class Game {
private:
  sf::RenderWindow *window0;
  sf::Texture *textures0[3]; // 0 - field, 1 - food, 2 - snake

  Field *field0;
  int tileLength0;

	FoodSpawner *food0;
  Snake *snake0;

  int score0 = 0;

	bool endOfGame = false;

public:
  Game(sf::RenderWindow *window);
  ~Game();

  void loop();
};
