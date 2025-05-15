#pragma once

#include "MainMenu.hpp"

class StateController
{
private:
	std::stack<States*> states;
	void CheckForStateChange();
public:
	StateController(RenderWindow* window);
	virtual ~StateController();
	void Update();
	void Render();
};