#include "MainMenu.hpp"

MainMenu::MainMenu(RenderWindow* window) : States(window), titleText(font) {
    std::cout << "Starting MainMenu \n";
    gameTitle = "MINESWEEPER";
    textColor = Color(255, 255, 255, 255);

    if (!font.openFromFile("Assets/Fonts/static/Orbitron-ExtraBold.ttf")) {
        std::cerr << "Error loading font!\n";
    }



    SetUpText();
}

MainMenu::~MainMenu() {
    std::cout << "Exiting MainMenu\n";
    delete playButton;
    delete quitButton;
}

void MainMenu::SetUpText() {
    titleText.setFont(font);
    titleText.setCharacterSize(80);
    titleText.setFillColor(textColor);
    titleText.setString(gameTitle);
    titleText.setPosition(Vector2f(
        window->getSize().x / 2.f - titleText.getGlobalBounds().size.x / 2.f,
        window->getSize().y / 3.f
	)
    );

    playButton = new Button("PLAY", Color(80, 80, 80, 255), 40);
    playButton->SetPosition(
        window->getSize().x / 2.f - playButton->GetBounds().x / 2.f,
        titleText.getPosition().y + window->getSize().y / 3.f
    );

    quitButton = new Button("QUIT", Color(80, 80, 80, 255), 40);
    quitButton->SetPosition(
        window->getSize().x / 2.f - quitButton->GetBounds().x / 2.f,
        playButton->GetPosition().y + playButton->GetBounds().y + 20.f
    );
}

void MainMenu::MouseInput() {
  	/*Vector2i pixelPos = Mouse::getPosition(*window);
   	Vector2f worldPos = window->mapPixelToCoords(pixelPos);
	*/
    playButton->CheckForMouseHover(*window);
    quitButton->CheckForMouseHover(*window);

    if (Mouse::isButtonPressed(Mouse::Button::Left)) {
        if (playButton->IsPressed(*window)) playState = true;
        if (quitButton->IsPressed(*window)) {
            quitState = true;
            window->close();
        }
    }
}


void MainMenu::MoveToNextState(std::stack<States*>* states)
{
	states->push(new PlayState(window));
}

void MainMenu::Update() {
    MouseInput();
    if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
        quitState = true;
        window->close();
    }
}

void MainMenu::Render() {
    window->draw(titleText);
    playButton->Render(window);
    quitButton->Render(window);
}
