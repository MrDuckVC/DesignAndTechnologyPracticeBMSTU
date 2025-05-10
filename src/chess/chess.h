#pragma once

#include "../games/game.h"
#include "untils.h"
#include "conf.h"
#include "figure.h"
#include "cell.h"

#include <iostream>
#include <map>

namespace chess {

class Chess : public game::Game {
 private:
    Cell desk[BOARD_SIZE][BOARD_SIZE];
    Color whoseTurn;

    void DrawBoard();
    void DrawFigures();
    void Draw();

    void Move(int oldN, int oldM, int newN, int newM);
 public:
    Chess(sf::RenderWindow& window);
    void Run() override;
    const std::string GetName() override;
};
}  // namespace chess
