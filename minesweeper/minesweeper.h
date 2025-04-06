#pragma once

#include "../games/game.h"


namespace minesweeper {
/**
 * @brief Класс клетки
 */
class Cell {
 private:
    bool isMine;
    bool isRevealed;
    bool isFlagged;
    int neighborMines;
};

class Minesweeper : public game::Game {

    public:


    void Run() override;

    const std::string GetName() override;

    const std::string GetDescription() override;

    const std::string GetLogoFile() override;
   };
}// namespace minesweeper
