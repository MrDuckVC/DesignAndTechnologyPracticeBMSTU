#pragma once
#include "StateController.hpp"

class Game
{
private:
	RenderWindow* window;
	VideoMode screenSize;
	Color screenBgColor;
	StateController* controller;
	void CreateWindow();
	void UpdateAll();
	void RenderAll();
public:
	Game();
	~Game();
	void Run();
};