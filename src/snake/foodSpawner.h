#pragma once

#include <random>

#include "field.h"

class FoodSpawner {
 private:
    int getRand(int maxNum) const;

    std::mt19937* gen0;

    Field* field0;

    sf::RectangleShape foodUnit0;

 public:
    FoodSpawner(Field* field, sf::Texture* texture);
    ~FoodSpawner();

    sf::Vector2f getCurrentPos() const { return foodUnit0.getPosition(); }

    sf::Drawable* getRectToDraw() const { return (sf::Drawable*)&foodUnit0; }

    void respawn();
};
