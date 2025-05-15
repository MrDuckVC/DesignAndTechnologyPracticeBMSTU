#include "States.hpp"

States::States(RenderWindow* window)
{
	this->window = window;
	ResetState();
}

States::~States()
{}

bool States::IsQuitState()
{
	return quitState;
}

bool States::IsPlayState()
{
	return playState;
}

void States::ResetState()
{
	quitState = false;
	playState = false;
}
