#pragma once

#include <SFML/Graphics.hpp>
#include "../games/game.h"
#include "PlayState.hpp"

namespace minesweeper {
class Minesweeper : public game::Game {
 private:
    sf::VideoMode screenSize;
    sf::Color screenBgColor;
    PlayState playState;
    void CreateWindow();
    void RenderAll();

 public:
    Minesweeper(sf::RenderWindow& window);
    void Run() override;
    const std::string GetName() override;
};
}  // namespace minesweeper
