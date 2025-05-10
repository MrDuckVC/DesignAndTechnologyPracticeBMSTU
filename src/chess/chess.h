#pragma once

#include "../games/game.h"

#include <iostream>
#include <map>

namespace chess {
const int BOARD_SIZE = 8;
const int WINDOW_SIZE = 1000;

enum class Color {
    WHITE,
    BLACK,
};

enum class FigureType {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
};

class Figure {
 private:
    FigureType figureType;
    Color figureColor;

    bool isSelected = false;

    sf::Sprite figureSprite;
 public:
    static std::map<std::pair<FigureType, Color>, sf::Texture> figureTextures;
    static sf::Texture LoadTexture(std::string pat);

    Figure(FigureType figureType = FigureType::PAWN, Color figureColor = Color::WHITE);

    FigureType GetFigureType();
    Color GetFigureColor();
    sf::Sprite GetFigureSprite();
    void SetFigureSpritePosition(float x, float y);
};
class Cell {
 private:
    Color cellColor;
    Figure figure;
    bool isEmpty;

    sf::RectangleShape cellShape = sf::RectangleShape({static_cast<float>(WINDOW_SIZE) / BOARD_SIZE, static_cast<float>(WINDOW_SIZE) / BOARD_SIZE});

    void FillCellColor();

 public:
    Cell(Color cellColor = Color::WHITE);
    Cell(Color cellColor, Figure figure);

    void SetFigure(Figure figure);
    void SetCellColor(Color color);
    void SetCellShapPosition(float x, float y);
    void MakeEmply();
    Figure GetFigure();
    Color GetCellColor();
    sf::RectangleShape GetCellShape();
    bool IsEmpty();
};

class Chess : public game::Game {
 private:
    Cell desk[BOARD_SIZE][BOARD_SIZE];

    void DrawBoard();
    void DrawFigures();
    void PlaceFigures();
 public:
    Chess(sf::RenderWindow& window);
    void Run() override;
    const std::string GetName() override;

    void draw();
};
}  // namespace chess
