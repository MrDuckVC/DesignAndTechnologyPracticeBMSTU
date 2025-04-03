#pragma once

#include <string>

namespace game {
class Game {
private:
    static int gamesCount;
    static Game **games;

public:
    virtual void Run() = 0;
    virtual const std::string GetName() = 0;
    virtual const std::string GetDescription() = 0;

    static void AddGame(Game *game);
    static void RemoveGame(int index);
    static int GetGamesCount();
};
} // namespace game
