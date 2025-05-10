#include "menu.h"

namespace menu {
void Menu::updateOptionsSelection() {
    for (size_t i = 0; i < options.size(); ++i) {
        if (i == static_cast<size_t>(selectedOption)) {
            options[i].first.setFillColor(selectedColor);
        } else {
            options[i].first.setFillColor(normalColor);
        }
    }
}

void Menu::updateOptionsPosition() {
    const float startY = titleY + titleAndOptionsSpacing;
    for (size_t i = 0; i < options.size(); ++i) {
        sf::FloatRect optionRect = options[i].first.getLocalBounds();
        options[i].first.setOrigin(optionRect.getCenter());
        options[i].first.setPosition({window.getSize().x / 2.0f, startY + i * optionsYSpacing});
    }
}

Menu::Menu(sf::RenderWindow& window) : window(window) {
    if (!mainFont.openFromFile(fontFile)) {
        throw std::runtime_error("Failed to load font");
    }
    if (!backgroundTexture.loadFromFile(backgroundImageFile)) {
        throw std::runtime_error("Failed to load texture");
    }
    backgroundSprite = sf::Sprite(backgroundTexture);
    backgroundSprite.setScale({static_cast<float>(window.getSize().x) / static_cast<float>(backgroundTexture.getSize().x),
                               static_cast<float>(window.getSize().y) / static_cast<float>(backgroundTexture.getSize().y)});
    titleText = sf::Text(mainFont, "Menu", titleFontSize);
    titleText.setFillColor(normalColor);

    sf::FloatRect titleRect = titleText.getLocalBounds();
    titleText.setOrigin(titleRect.getCenter());
    titleText.setPosition({window.getSize().x / 2.0f, titleY});
    titleText.setStyle(sf::Text::Bold);

    conorText = sf::Text(mainFont, "Developed by:\n\r- Cunev Valentin\n\r- Garanin Erofey\n\r- Akopov Anton", 30);
    sf::FloatRect conorRect = conorText.getLocalBounds();
    conorText.setOrigin({conorRect.size.x, conorRect.size.y * 1.0f});
    conorText.setPosition({window.getSize().x - conorTextBorderXSpacing, window.getSize().y - conorTextBorderYSpacing});
}

void Menu::addOption(std::string optionName, std::function<void()> action) {
    sf::Text optionText(mainFont, optionName, optionsFontSize);
    optionText.setFillColor(normalColor);
    options.push_back({optionText, action});
    updateOptionsPosition();
}

void Menu::handleEvents(const sf::Event& event) {
    if (event.is<sf::Event::MouseMoved>()) {  // Если мышь двигается
        sf::Vector2f mousePos(sf::Mouse::getPosition(window));
        for (std::pair<sf::Text, std::function<void()>>& option : options) {
            if (option.first.getGlobalBounds().contains(mousePos)) {  // Если мышь над текстом
                option.first.setFillColor(hoverColor);
            } else {
                option.first.setFillColor(normalColor);
            }
        }
    } else if (event.is<sf::Event::MouseButtonPressed>() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {  // Если нажата левая кнопка мыши
        sf::Vector2f mousePos(sf::Mouse::getPosition(window));
        for (std::pair<sf::Text, std::function<void()>>& option : options) {
            if (option.first.getGlobalBounds().contains(mousePos)) {  // Если мышь над текстом
                option.second();                                      // Выполняем действие
            }
        }
    } else if (const sf::Event::KeyPressed* keyPressed = event.getIf<sf::Event::KeyPressed>()) {  // Если нажата клавиша
        switch (keyPressed->scancode) {
            case (sf::Keyboard::Scancode::Up):  // Если нажата клавиша вверх
                selectedOption = (selectedOption - 1 + options.size()) % options.size();
                updateOptionsSelection();
                break;
            case (sf::Keyboard::Scancode::Down):  // Если нажата клавиша вниз
                selectedOption = (selectedOption + 1) % options.size();
                updateOptionsSelection();
                break;
            case (sf::Keyboard::Scancode::Enter):  // Если нажата клавиша Enter
                if (selectedOption >= 0 && selectedOption < static_cast<int>(options.size())) {
                    options[selectedOption].second();
                }
                break;
            default:
                break;
        }
    }
}

void Menu::draw() {
    window.draw(backgroundSprite);
    window.draw(titleText);
    window.draw(conorText);
    for (const std::pair<sf::Text, std::function<void()>>& option : options) {
        window.draw(option.first);
    }
}
}  // namespace menu
