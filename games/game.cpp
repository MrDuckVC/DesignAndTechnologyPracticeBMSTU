#include "game.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

namespace game {
void Game::PrintLogo() {
    std::ifstream logoFile(GetLogoFile());
    if (!logoFile.is_open()) {
        std::cerr << "Не удалось открыть файл\n";
        return;
    }

    char ch;
    while (logoFile.get(ch)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        std::cout << ch;
    }

    logoFile.close();
}

void Game::AddGame(Game* game) {
    Game** newGames = new Game*[gamesCount + 1];
    for (int i = 0; i < gamesCount; i++) {
        newGames[i] = games[i];
    }
    newGames[gamesCount] = game;
    delete[] games;
    games = newGames;
    gamesCount++;
}
void Game::RemoveGame(int index) {
    Game** newGames = new Game*[gamesCount - 1];
    int i = 0;
    for (int j = 0; j < gamesCount; j++) {
        if (j != index) {
            newGames[i] = games[j];
            i++;
        }
    }
    delete[] games;
    games = newGames;
    gamesCount--;
}

int Game::GetGamesCount() {
    return gamesCount;
}
}  // namespace game
