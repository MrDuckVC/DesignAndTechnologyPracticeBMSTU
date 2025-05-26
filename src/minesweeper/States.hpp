#pragma once
#include <SFML/Graphics.hpp>
#include <stack>


class States {
 protected:
 	sf::RenderWindow& window;
    bool quitState;
    bool playState;

 public:
    States(sf::RenderWindow& window);
    virtual void Update() = 0;
    virtual void Render() = 0;
};
