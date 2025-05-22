#pragma once
#include <string.h>
#include <SFML/Graphics.hpp>



class Button {
 private:
    std::string buttonName;
    sf::Font font;
    sf::Text buttonText;
    sf::Color defaultColor;
    sf::Color highlightedColor;

 public:
    Button(std::string name, sf::Color, float size);

    void SetPosition(float x, float y);

    // Mouse Input
    void CheckForMouseHover(sf::RenderWindow& window);
    bool IsPressed(sf::RenderWindow& window);

    sf::Vector2f GetBounds();
    sf::Vector2f GetPosition();

    void Render(sf::RenderWindow& window);
};
