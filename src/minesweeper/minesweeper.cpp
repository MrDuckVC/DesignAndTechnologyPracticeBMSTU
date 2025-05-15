#include "minesweeper.hpp"

namespace minesweeper {
void Minesweeper::CreateWindow()
{
}

void Minesweeper::RenderAll()
{
	window.clear(screenBgColor);
	// controller->Render();
	window.display();
}

Minesweeper::Minesweeper(sf::RenderWindow& window) : Game(window)
{
	screenBgColor = Color(20, 20, 20, 225);
	screenSize.size.x = 600;
	screenSize.size.y = 675;
	CreateWindow();
	// controller = new StateController(window);
}

Minesweeper::~Minesweeper()
{
	// delete controller;
}

void Minesweeper::Run()
{
	while(window.isOpen())
	{
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			} else if (const sf::Event::KeyPressed* keyPressed = event->getIf<sf::Event::KeyPressed>()) {  // Если нажата клавиша
				switch (keyPressed->scancode) {
					case (sf::Keyboard::Scancode::Escape):  // Если нажата клавиша Escape
						return;
						break;
					default:
						break;
				}
			}
		}
		RenderAll();
	}
}

const std::string Minesweeper::GetName() {
	return "Minesweeper";
}
}
