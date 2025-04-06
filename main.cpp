#include "chess/chess.h"
#include "minesweeper/minesweeper.h"
#include "games/game.h"

game::Game** game::Game::games = nullptr;
int game::Game::gamesCount = 0;

int main() {
    game::Game::AddGame(new chess::Chess());
    game::Game::AddGame(new minesweeper::Minesweeper());

    return 0;
}
