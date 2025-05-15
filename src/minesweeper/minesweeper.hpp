#pragma once

#include "../games/game.h"
#include "StateController.hpp"

namespace minesweeper {
class Minesweeper : game::Game
{
private:
	VideoMode screenSize;
	Color screenBgColor;
	StateController* controller;
	void CreateWindow();
	void UpdateAll();
	void RenderAll();
public:
	Minesweeper(sf::RenderWindow& window);
	~Minesweeper();
	void Run() override;
    const std::string GetName() override;
};
}
