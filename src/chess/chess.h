#pragma once

#include "../games/game.h"
#include "cell.h"
#include "conf.h"
#include "figure.h"
#include "untils.h"

#include <iostream>
#include <map>

namespace chess {

class Chess : public game::Game {
 private:
    Cell desk[BOARD_SIZE][BOARD_SIZE];
    Color whoseTurn;

    bool isPromotionPendingOfPawn;
    std::pair<int, int> promotionPosition;
    const std::vector<FigureType> possibleFiguresToChoose = {FigureType::QUEEN, FigureType::BISHOP, FigureType::KNIGHT, FigureType::ROOK};

    void DrawBoard();
    void DrawFigures();
    void Draw();

    bool IsSquareUnderAttack(int x, int y, Color defendingColor);
    bool CanAttack(int attackerX, int attackerY, int targetX, int targetY);
    bool IsPathClear(int fromX, int fromY, int toX, int toY);
    bool IsInCheck(Color color);
    bool CanMoveTo(int oldN, int oldM, int newN, int newM);
    void PromotePawn(FigureType newType);
    void Move(int oldN, int oldM, int newN, int newM);
 public:
    Chess(sf::RenderWindow& window);
    void Run() override;
    const std::string GetName() override;
};
}  // namespace chess
