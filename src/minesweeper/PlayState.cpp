#include "PlayState.hpp"

PlayState::PlayState(RenderWindow& window) : States(window), timeText(font), bombText(font), PopupText(font) {
    Tile::LoadTexture();
    borderOffset = Vector2f(20.f, 20.f);
    isGameStart = false;
    showPopup = false;
    if (!font.openFromFile("assests/minesweeper/Fonts/static/Orbitron-Regular.ttf")) {
        throw std::runtime_error("Failed to load minesweeper font");
    }
    CreateGameArea();
    CreateButtons();
    ResetGame();
}

void PlayState::CreateGameArea() {
    float screenWidth = window.getSize().x;
    float screenMid = window.getSize().x / 2;
    gameArea.setFillColor(Color(0, 0, 0, 0));
    gameArea.setPosition(Vector2f(borderOffset.x, borderOffset.y));
    gameArea.setSize(Vector2f(screenWidth - borderOffset.x * 2, screenWidth - borderOffset.x * 2));
    gameArea.setOutlineThickness(3.f);
    gameArea.setOutlineColor(Color(120, 120, 120, 255));
}

void PlayState::CreateButtons() {
    resetButton = new Button("RESET", Color(80, 80, 80, 255), 40.f);
    float screenMid = window.getSize().x / 2;
    resetButton->SetPosition(screenMid - resetButton->GetBounds().x / 2, window.getSize().y - resetButton->GetBounds().y - 30.f);
}

void PlayState::ResetGame() {
    isGameStart = false;
    ResetTime();
    ResetBombs();
    board.CreateNewBoard(gameArea, bombCount);
    HidePopup();
}

void PlayState::ResetTime() {
    float textSize = 40.0f;
    timeText.setFont(font);
    timeText.setCharacterSize(textSize);
    timeText.setPosition(Vector2f(gameArea.getPosition().x, gameArea.getPosition().y + gameArea.getGlobalBounds().size.y + 20));
    timeText.setString("TIME : 0");
    timer.restart();
    playTime = 0;
}

void PlayState::ResetBombs() {
    bombCount = BOMB_COUNT;
    float textSize = 40.0f;
    bombText.setFont(font);
    bombText.setCharacterSize(textSize);
    bombText.setPosition(Vector2f(5.0f * gameArea.getGlobalBounds().size.x / 7, gameArea.getPosition().y + gameArea.getGlobalBounds().size.y + 20));
    UpdateBomb();
}

void PlayState::UpdateBomb() {
    std::stringstream ss;
    ss << "Bombs: ";
    ss << bombCount;
    bombText.setString(ss.str());
}

void PlayState::UpdateTime() {
    if (!isGameStart || isGameQuit) {
        return;
    }

    if (timer.getElapsedTime().asSeconds() > 1) {
        playTime += timer.getElapsedTime().asSeconds();
        timer.restart();

        std::stringstream ss;
        ss << "TIME: ";
        ss << playTime;
        timeText.setString(ss.str());
    }
}

void PlayState::ShowPopup(const std::string& message) {
    showPopup = true;
    popupBackground.setSize(Vector2f(400.f, 200.f));
    popupBackground.setFillColor(Color(0, 0, 0, 200));
    popupBackground.setPosition(
        Vector2f(window.getSize().x / 2 - popupBackground.getSize().x / 2, window.getSize().y / 2 - popupBackground.getSize().y / 2));
    PopupText.setFont(font);
    PopupText.setString(message);
    PopupText.setCharacterSize(40);
    PopupText.setFillColor(Color::White);
    PopupText.setPosition(Vector2f(window.getSize().x / 2 - PopupText.getGlobalBounds().size.x / 2, popupBackground.getPosition().y + 20));
    restartButton = new Button("RESTART", Color(80, 80, 80, 255), 30.f);
    restartButton->SetPosition(window.getSize().x / 2 - restartButton->GetBounds().x - 20.f,
                               popupBackground.getPosition().y + popupBackground.getSize().y - restartButton->GetBounds().y - 20.f);
    quitButton = new Button("QUIT", Color(80, 80, 80, 255), 30.f);
    quitButton->SetPosition(window.getSize().x / 2 - quitButton->GetBounds().x + 170.f,
                            popupBackground.getPosition().y + popupBackground.getSize().y - quitButton->GetBounds().y - 20.f);
}

void PlayState::HidePopup() {
    showPopup = false;
}

PlayState::~PlayState() {
    delete resetButton;
    delete restartButton;
    delete quitButton;
}

void PlayState::MoveToNextState(std::stack<States*>* states) {
    return;
}

void PlayState::PlayGame(bool isLeftClick, bool isRightClick, Vector2i mousePos) {
    if (!isGameStart && timer.getElapsedTime().asSeconds() > 0.5f) {
        isGameStart = true;
        timer.restart();
    }

    if (isLeftClick && !isMouseClicked) {
        board.LeftButton(mousePos);
    }
    if (isRightClick && !isMouseClicked) {
        board.RightButton(mousePos);
    }

    if (board.IsWin()) {
        ShowPopup("You Win!");
    } else if (board.IsLoss()) {
        ShowPopup("You Lose!");
    }
    bombCount = board.GetRemainingBombs();
    UpdateBomb();
}

void PlayState::CheckForMouseClick(Vector2i mousePos) {
    bool isLeftClick = Mouse::isButtonPressed(Mouse::Button::Left);
    bool isRightClick = Mouse::isButtonPressed(Mouse::Button::Right);
    if (showPopup) {
        if (restartButton->IsPressed(window) && isLeftClick) {
            ResetGame();
        } else if (quitButton->IsPressed(window) && isLeftClick) {
            isGameQuit = true;
        }
    } else {
        if (resetButton->IsPressed(window) && isLeftClick) {
            ResetGame();
        } else {
            PlayGame(isLeftClick, isRightClick, mousePos);
        }
    }
    isMouseClicked = isLeftClick || isRightClick;
}

void PlayState::CheckForMouseHover(Vector2i mousePos) {
    if (showPopup) {
        restartButton->CheckForMouseHover(window);
        quitButton->CheckForMouseHover(window);
    } else {
        resetButton->CheckForMouseHover(window);
    }
}

void PlayState::CheckExitState() {
    if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
        isGameQuit = true;
    }
}

void PlayState::Update() {
    Vector2i mousePos = Mouse::getPosition(window);
    CheckForMouseHover(mousePos);
    CheckForMouseClick(mousePos);
    CheckExitState();
    UpdateTime();
}

void PlayState::Render() {
    window.draw(gameArea);
    board.RenderBoard(window);

    if (showPopup) {
        window.draw(popupBackground);
        window.draw(PopupText);
        restartButton->Render(window);
        quitButton->Render(window);
    } else {
        resetButton->Render(window);
    }
    window.draw(timeText);
    window.draw(bombText);
}
