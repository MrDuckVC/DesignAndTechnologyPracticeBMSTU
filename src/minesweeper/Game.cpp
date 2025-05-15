#include "Game.hpp"

void Game::CreateWindow()
{
	window = new RenderWindow(screenSize, "MINESWEEPER");
	window->setFramerateLimit(30);
}

void Game::UpdateAll()
{
	while (const std::optional event = window->pollEvent())
	{
		if (event->is<sf::Event::Closed>() || Keyboard::isKeyPressed(Keyboard::Key::Escape))
		{
			window->close();
		}
	}
	controller->Update();
}

void Game::RenderAll()
{
	window->clear(screenBgColor);
	controller->Render();
	window->display();
}

Game::Game()
{
	screenBgColor = Color(20, 20, 20, 225);
	screenSize.size.x = 600;
	screenSize.size.y = 675;
	CreateWindow();
	controller = new StateController(window);
}

Game::~Game()
{
	delete window;
	delete controller;
}

void Game::Run()
{
	while(window->isOpen())
	{
		UpdateAll();
		RenderAll();
	}
}
