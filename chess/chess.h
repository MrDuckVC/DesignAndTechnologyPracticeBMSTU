#pragma once

#include "../games/game.h"

namespace chess {
const int BOARD_SIZE = 8; // Не более 26 (т.к. в английском алфавите 26 букв, и если привысить это число, то программа будет некоректно работать).
const int CELL_SIZE = 3; // Количество строчек символов в ячейке

enum class Color { WHITE, BLACK };
enum class FigureType { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };

class Figure {
private:
    FigureType figureType;
    Color figureColor;
    int figureValue;

public:
    Figure();
    Figure(FigureType figureType, Color figureColor);
    void PrintFigure();
    int GetFigureValue();
    FigureType GetFigureType();
    Color GetFigureColor();
};

class Cell {
private:
    Color cellColor;
    Figure figure;
    bool isEmpty;
public:
    Cell();
    Cell(Color cellColor);
    Cell(Color cellColor, Figure figure);
    void PrintCell(int cellLine);
    void SetFigure(Figure figure);
    Figure GetFigure();
    Color GetCellColor();
};

class Chess : public game::Game {
private:
    Cell desk[BOARD_SIZE][BOARD_SIZE];

    void PrintBoard();
public:
    Chess();
    void Run() override;
    const std::string GetName() override;
    const std::string GetDescription() override;
};
} // namespace chess
