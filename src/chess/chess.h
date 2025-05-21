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
    void DrawEndGame();
    void Draw();

    bool IsSquareUnderAttack(int x, int y, Color defendingColor, Cell board[BOARD_SIZE][BOARD_SIZE] = nullptr);
    bool CanAttack(int attackerX, int attackerY, int targetX, int targetY, Cell board[BOARD_SIZE][BOARD_SIZE] = nullptr);
    bool IsPathClear(int fromX, int fromY, int toX, int toY, Cell board[BOARD_SIZE][BOARD_SIZE] = nullptr);
    bool IsInCheck(Color color);
    bool CanMoveTo(int oldN, int oldM, int newN, int newM);
    void PromotePawn(FigureType newType);
    void Move(int oldN, int oldM, int newN, int newM);
    bool isGameOver();
 public:
    Chess(sf::RenderWindow& window);
    void Run() override;
    const std::string GetName() override;
};
}  // namespace chess
