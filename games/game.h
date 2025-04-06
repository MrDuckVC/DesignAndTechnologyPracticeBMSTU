#pragma once

#include <string>

namespace game {
/**
 * @brief Класс игры
 */
class Game {
 private:
    /**
     * @brief Количество игр в массиве games
     */
    static int gamesCount;
    /**
     * @brief Максимальное количество игр в массиве games
     */
    static Game** games;

 public:
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
    /**
     * @brief Получить описание игры
     *
     * @return Описание игры
     */
    virtual const std::string GetDescription() = 0;
    /**
     * @brief .txt файл с лого, можно взять с сайта https://textkool.com/en/ascii-art-generator?hl=default&vl=default&font=Delta%20Corps%20Priest%201
     *
     * @return Имя файла с логотипом
     */
    virtual const std::string GetLogoFile() = 0;

    /**
     * @brief Печатает лого игры
     */
    void PrintLogo();

    /**
     * @brief Добавляет игру в статический массив
     *
     * @param game Указатель на игру
     */
    static void AddGame(Game* game);
    /**
     * @brief Удаляет игру из статического массива
     *
     * @param index Индекс игры
     */
    static void RemoveGame(int index);
    /**
     * @brief Получает актуальное количество игр
     *
     * @return Количество игр
     */
    static int GetGamesCount();
};
}  // namespace game
