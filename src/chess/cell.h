#pragma once

#include "SFML/Graphics.hpp"
#include "untils.h"
#include "conf.h"
#include "figure.h"

namespace chess {

class Cell {
 private:
    Color cellColor;
    Figure figure;
    bool isEmpty;

    sf::RectangleShape cellShape = sf::RectangleShape({static_cast<float>(WINDOW_SIZE) / BOARD_SIZE, static_cast<float>(WINDOW_SIZE) / BOARD_SIZE});

    void FillCellColor();
 public:
    Cell(Color cellColor = Color::WHITE);

    Color GetCellColor();
    Figure& GetFigure();
    bool IsEmpty();
    sf::RectangleShape& GetCellShape();
    void SetCellColor(Color color);
    void SetFigure(Figure figure);
    void MakeEmpty();
};

}  // namespace chess
