#include "chess/chess.h"
#include "games/game.h"
#include "snake/snake.h"

game::Game** game::Game::games = nullptr;
int game::Game::gamesCount = 0;

int main() {
    game::Game::AddGame(new chess::Chess());
    game::Game::AddGame(new snake::Snake());

    return 0;
}
