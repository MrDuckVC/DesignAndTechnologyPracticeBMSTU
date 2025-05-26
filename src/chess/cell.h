#pragma once

#include "SFML/Graphics.hpp"
#include "conf.h"
#include "figure.h"
#include "untils.h"

namespace chess {

class Cell {
 private:
    Color cellColor;
    Figure figure;
    bool isEmpty;

    sf::RectangleShape cellShape = sf::RectangleShape({static_cast<float>(WINDOW_SIZE) / BOARD_SIZE, static_cast<float>(WINDOW_SIZE) / BOARD_SIZE});
 public:
    Cell(Color cellColor = Color::WHITE);

    Color GetCellColor();
    Figure& GetFigure();
    bool IsEmpty();
    sf::RectangleShape& GetCellShape();
    void SetCellColor(Color color);
    void SetFigure(Figure figure);
    void MakeEmpty();

    void FillCellColor();
};

}  // namespace chess
