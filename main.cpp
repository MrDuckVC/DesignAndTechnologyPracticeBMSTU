#include "games/game.h"
#include "chess/chess.h"

game::Game **game::Game::games = nullptr;
int game::Game::gamesCount = 0;

int main() {
    game::Game::AddGame(new chess::Chess());

    return 0;
}
