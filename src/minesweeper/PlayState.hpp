#pragma once
#include <iostream>
#include "Board.hpp"
#include "Button.hpp"
#include "States.hpp"

#define BOMB_COUNT 20

class PlayState : public States {
 private:
    // Minesweeper Area
    Vector2f borderOffset;
    RectangleShape gameArea;
    void CreateGameArea();
    Board board;
    // bomb
    int bombCount;
    void ResetBombs();
    void UpdateBomb();
    // Timer
    Clock timer;
    int playTime;
    Font font;
    bool timeUpdated = true;
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
    bool isMouseClicked;
    void CheckForMouseClick(Vector2i mousePos);
    void CheckForMouseHover(Vector2i mousePos);
    void CheckExitState();

 public:
    bool isGameQuit = false;
    PlayState(RenderWindow& window);
    virtual ~PlayState();
    void MoveToNextState(std::stack<States*>* states);
    void Update();
    void Render();
};
