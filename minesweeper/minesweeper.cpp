#include "minesweeper.h"

#include <iostream>


/**
 * @brief Цвета для полей
 */
namespace colors {

    const std::string COLOR_RESET = "\033[0m";
    const std::string COLOR_RED = "\033[31m";
    const std::string COLOR_GREEN = "\033[32m";
    const std::string COLOR_BLUE = "\033[34m";
    const std::string COLOR_YELLOW = "\033[33m";
    const std::string COLOR_MAGENTA = "\033[35m";
    const std::string COLOR_CYAN = "\033[36m";
    const std::string COLOR_GRAY = "\033[90m";
    const std::string COLOR_WHITE = "\033[97m";

}; // namespace colors

void PrintLogo(){}

namespace minesweeper{

const std::string Minesweeper::GetName(){
    return "Minesweeper";
}

const std::string Minesweeper::GetDescription() {
    return "Minesweeper is a puzzle computer game in which you need to find all the mines\n"
            "on the playing field using numerical hints. The principle of the game: the playing\n"
            "field is divided into adjacent cells (squares, hexagons, cubes, etc.),\n"
            "some of which are mined. The goal of the game is to open all the cells that do not contain mines.\n"
            "The player opens the cells, trying not to open the cell with a mine. By opening a mine slot, he loses.\n";
}

const std::string Minesweeper::GetLogoFile() {
    return "./minesweeper/minesweeperLogo.txt";
}

void Minesweeper::Run(){
    PrintLogo();
}

} // namespace minesweeper
