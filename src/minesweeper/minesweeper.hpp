#pragma once

#include "../games/game.h"
#include "PlayState.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

namespace minesweeper {
class Minesweeper : game::Game
{
private:
	VideoMode screenSize;
	Color screenBgColor;
	PlayState playState;
	// StateController* controller;
	void CreateWindow();
	void RenderAll();
public:
	Minesweeper(sf::RenderWindow& window);
	void Run() override;
    const std::string GetName() override;
};
}
