#include "Button.hpp"
#include <iostream>

Button::Button(std::string name, sf::Color color, float size) : buttonText(font, name, static_cast<unsigned int>(size)) {
    if (!font.openFromFile("assests/minesweeper/Fonts/static/Orbitron-Regular.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    defaultColor = color;
    highlightedColor = sf::Color(255, 255, 255, 255);
    buttonName = name;

    buttonText.setFillColor(defaultColor);
}


void Button::SetPosition(float x, float y) {
    buttonText.setPosition(sf::Vector2f(x, y));
}

// Mouse Input
void Button::CheckForMouseHover(sf::RenderWindow& window) {
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
    if (buttonText.getGlobalBounds().contains(worldPos)) {
        buttonText.setFillColor(highlightedColor);
    } else {
        buttonText.setFillColor(defaultColor);
    }
}

bool Button::IsPressed(sf::RenderWindow& window) {
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
    return buttonText.getGlobalBounds().contains(worldPos);
}

sf::Vector2f Button::GetBounds() {
    return sf::Vector2f(buttonText.getGlobalBounds().size.x, buttonText.getGlobalBounds().size.y);
}

sf::Vector2f Button::GetPosition() {
    return buttonText.getPosition();
}

void Button::Render(sf::RenderWindow& window) {
    window.draw(buttonText);
}
