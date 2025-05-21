#include "Button.hpp"
#include <iostream>

Button::Button(std::string name, Color color, float size) : buttonText(font, name, static_cast<unsigned int>(size)) {
    if (!font.openFromFile("assests/minesweeper/Fonts/static/Orbitron-Regular.ttf")) {
        std::cerr << "Error\n";
    }

    defaultColor = color;
    highlightedColor = Color(255, 255, 255, 255);
    buttonName = name;

    buttonText.setFillColor(defaultColor);
}

Button::~Button() {
}

void Button::SetPosition(float x, float y) {
    buttonText.setPosition(sf::Vector2f(x, y));
}

// Mouse Input
void Button::CheckForMouseHover(RenderWindow& window) {
    Vector2i pixelPos = Mouse::getPosition(window);
    Vector2f worldPos = window.mapPixelToCoords(pixelPos);
    if (buttonText.getGlobalBounds().contains(worldPos)) {
        buttonText.setFillColor(highlightedColor);
    } else {
        buttonText.setFillColor(defaultColor);
    }
}

bool Button::IsPressed(RenderWindow& window) {
    Vector2i pixelPos = Mouse::getPosition(window);
    Vector2f worldPos = window.mapPixelToCoords(pixelPos);
    return buttonText.getGlobalBounds().contains(worldPos);
}

Vector2f Button::GetBounds() {
    return Vector2f(buttonText.getGlobalBounds().size.x, buttonText.getGlobalBounds().size.y);
}

Vector2f Button::GetPosition() {
    return buttonText.getPosition();
}

void Button::Render(RenderWindow& window) {
    window.draw(buttonText);
}
