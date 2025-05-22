#include "minesweeper.hpp"

namespace minesweeper {
void Minesweeper::CreateWindow() {
    window.setSize({screenSize.size.x, screenSize.size.y});
}

void Minesweeper::RenderAll() {
    window.clear(screenBgColor);
    playState.Render();
    window.display();
}

Minesweeper::Minesweeper(sf::RenderWindow& window) : Game(window), playState(PlayState(window)) {
    screenBgColor = sf::Color(20, 20, 20, 225);
    screenSize.size.x = 1000;
    screenSize.size.y = 1000;
    CreateWindow();
}

void Minesweeper::Run() {
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (const sf::Event::KeyPressed* keyPressed = event->getIf<sf::Event::KeyPressed>()) {  // Если нажата клавиша
                switch (keyPressed->scancode) {
                    case (sf::Keyboard::Scancode::Escape):  // Если нажата клавиша Escape
                        playState.isGameQuit = true;
                        break;
                    default:
                        break;
                }
            }
        }
        playState.Update();
        RenderAll();
        if (playState.isGameQuit) {
            return;
        }
    }
}

const std::string Minesweeper::GetName() {
    return "Minesweeper";
}
}  // namespace minesweeper
