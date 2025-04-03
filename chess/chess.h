#pragma once

#include "../games/game.h"

namespace chess {
const int boardSize = 8;

enum class Color { WHITE, BLACK };
enum class FigureType { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };

class Figure {
private:
    FigureType figureType;
    Color figureColor;
    int figureValue;

public:
    void PrintFigure();
    int GetFigureValue();
    FigureType GetFigureType();
    Color GetFigureColor();
};

class Chess : public game::Game {
private:
    Figure desk[boardSize][boardSize];

    void PrintBoard();
public:
    void Run() override;
    const std::string GetName() override;
    const std::string GetDescription() override;
};
} // namespace chess
