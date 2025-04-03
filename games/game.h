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
    static Game **games;

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
     * @brief Добавляет игру в статический массив
     *
     * @param game Указатель на игру
     */
    static void AddGame(Game *game);
    /**
     * @brief Получает игру из статического массива
     *
     * @param index Индекс игры
     * @return Указатель на игру
     */
    static void RemoveGame(int index);
    /**
     * @brief Получает игру из статического массива
     *
     * @param index Индекс игры
     * @return Указатель на игру
     */
    static int GetGamesCount();
};
} // namespace game
