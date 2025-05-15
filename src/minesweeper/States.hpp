#pragma once
#include <SFML/Graphics.hpp>
#include <stack>

using namespace sf;

class States
{
protected:
	RenderWindow* window;
	bool quitState;
	bool playState;
public:
	States(RenderWindow* window);
	bool IsQuitState();
	bool IsPlayState();
	void ResetState();
	virtual void MoveToNextState(std::stack<States*>* states) = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual ~States();
};