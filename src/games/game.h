#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace game {
/**
 * @brief Класс игры
 */
class Game {
 protected:
    sf::RenderWindow& window;

 public:
    Game(sf::RenderWindow& window) : window(window) {}

    /**
     * @brief Запускает игру
     */
    virtual void Run() = 0;

    /**
     * @brief Получить название игры
     *
     * @return Название игры
     */
    virtual const std::string GetName() = 0;
};
}  // namespace game
