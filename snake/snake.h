#pragma once

#include "../games/game.h"

namespace snake {
class Snake : public game::Game {
 private:
    /**
     * @brief Получение нажатой клавиши
     */
    char getInput();

    /**
     * @brief Генерация еды, чтобы она не попала на змею
     */
    void generateFood();

    void setup();

    void draw();

    void input();

    void logic();

 public:
    void Run() override;

    const std::string GetName() override;

    const std::string GetDescription() override;

    const std::string GetLogoFile() override;
};
}  // namespace snake
