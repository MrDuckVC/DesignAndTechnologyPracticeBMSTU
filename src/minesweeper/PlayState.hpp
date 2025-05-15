#pragma once
#include <iostream>
#include "States.hpp"
#include "Button.hpp"
#include "Board.hpp"

#define BOMB_COUNT 20

class PlayState : public States
{
private:
	// Game Area
	Vector2f borderOffset;
	RectangleShape gameArea;
	void CreateGameArea();
	Board board;
	// bomb
	int bombCount;
	Text bombText;
	void ResetBombs();
	void UpdateBomb();
	// Timer
	Clock timer;
	int playTime;
	Font font;
	Text timeText;
	void ResetTime();
	void UpdateTime();
	// Buttons
	Button* resetButton;
	void CreateButtons();
	void ResetGame();
	void PlayGame(bool isLeftClick, bool isRightClick, Vector2i mousePos);
	// Win/Lose Popup
	bool showPopup;
	RectangleShape popupBackground;
	Text PopupText;
	Button* restartButton;
	Button* quitButton;
	void ShowPopup(const std::string& message);
	void HidePopup();
	// Mouse
	bool isGameStart;
	void CheckForMouseClick(Vector2i mousePos);
	void CheckForMouseHover(Vector2i mousePos);
	void CheckExitState();
public:
	PlayState(RenderWindow* window);
	virtual ~PlayState();
	void MoveToNextState(std::stack<States*>* states);
	void Update();
	void Render();
};
