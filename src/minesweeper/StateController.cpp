#include "StateController.hpp"

StateController::StateController(RenderWindow& window)
{
	states.push(new MainMenu(window));
}

StateController::~StateController()
{
	while(!states.empty())
	{
		delete states.top();
		states.pop();
	}
}

void StateController::CheckForStateChange()
{
	if (states.top()->IsPlayState())
	{
		states.top()->ResetState();
		states.top()->MoveToNextState(&states);
	}
	else if (states.top()->IsQuitState())
	{
		delete states.top();
		states.pop();
	}
}

void StateController::Update()
{
	CheckForStateChange();
	if (!states.empty())
	{
		states.top()->Update();
	}
}

void StateController::Render()
{
	if (!states.empty())
	{
		states.top()->Render();
	}
}
