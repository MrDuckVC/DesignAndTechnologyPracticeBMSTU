#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

namespace menu {

class Menu {
 private:
    sf::RenderWindow& window;
    sf::Font mainFont;
    sf::Text titleText = sf::Text(mainFont, "Menu", 50);
    sf::Text conorText = sf::Text(mainFont, "", 0);
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite = sf::Sprite(backgroundTexture);

    std::vector<std::pair<sf::Text, std::function<void()>>> options;

    const sf::Color normalColor = sf::Color::White;
    const sf::Color hoverColor = sf::Color::Green;
    const sf::Color selectedColor = sf::Color::Yellow;

    int selectedOption = -1;

    const float titleY = 250.0f;
    const float titleAndOptionsSpacing = 100.0f;
    const float optionsYSpacing = 60.0f;
    const float conorTextBorderYSpacing = 20.0f;
    const float conorTextBorderXSpacing = 20.0f;

    const int titleFontSize = 70;
    const int optionsFontSize = 50;

    const std::string backgroundImageFile = "assets/menuWallpaper.jpg";
    const std::string fontFile = "assets/RuneScape-ENA.ttf";

    void updateOptionsSelection();

    void updateOptionsPosition();

 public:
    Menu(sf::RenderWindow& window);

    void addOption(std::string optionName, std::function<void()> action);

    void handleEvents(const sf::Event& event);

    void draw();
};
}  // namespace menu
