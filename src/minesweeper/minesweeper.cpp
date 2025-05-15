#include "minesweeper.hpp"

namespace minesweeper {
void Minesweeper::CreateWindow()
{
}

void Minesweeper::UpdateAll()
{
	while (const std::optional event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed>() || Keyboard::isKeyPressed(Keyboard::Key::Escape))
		{
			window.close();
		}
	}
	controller->Update();
}

void Minesweeper::RenderAll()
{
	window.clear(screenBgColor);
	controller->Render();
	window.display();
}

Minesweeper::Minesweeper(sf::RenderWindow& window) : Game(window)
{
	screenBgColor = Color(20, 20, 20, 225);
	screenSize.size.x = 600;
	screenSize.size.y = 675;
	CreateWindow();
	controller = new StateController(window);
}

Minesweeper::~Minesweeper()
{
	delete controller;
}

void Minesweeper::Run()
{
	while(window.isOpen())
	{
		UpdateAll();
		RenderAll();
	}
}

const std::string Minesweeper::GetName() {
	return "Minesweeper";
}
}
