#pragma once

#include "../games/game.h"

namespace chess {
/**
 * @brief Максимальный размер доски
 * @details Не более 26 (т.к. в английском алфавите 26 букв, и если привысить это число, то программа будет некоректно работать).
 */
const int BOARD_SIZE = 8;
/**
 * @brief Размер ячейки (количество строчек символов в ячейке)
 * @details Должно быть нечётным числом, чтобы в центре ячейки был символ.
 */
const int CELL_SIZE = 3;

/**
 * @brief Цвета фигур, клеток и т.д.
 */
enum class Color {
    WHITE,
    BLACK,
};
/**
 * @brief Класс шахматной фигуры (пешка, король и т.д.)
 */
enum class FigureType {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
};

/**
 * @brief Класс шахматной фигуры
 */
class Figure {
 private:
    /**
     * @brief Тип фигуры (пешка, король и т.д.)
     */
    FigureType figureType;
    /**
     * @brief Цвет фигуры (белая, чёрная)
     */
    Color figureColor;
    /**
     * @brief Цена фигуры
     */
    int figureValue;

 public:
    /**
     * @brief Создаёт фигуру `заглушку` (белая пешка)
     *
     * @return Объект класса Figure
     */
    Figure();
    /**
     * @brief Создаёт фигуру по параметрам
     *
     * @param figureType Класс фигуры (пешка, король и т.д.)
     * @param figureColor Цвет фигуры
     * @return Объект класса Figure
     */
    Figure(FigureType figureType, Color figureColor);

    /**
     * @brief Выводит фугуру (занимает 2 символа)
     */
    void PrintFigure();

    /**
     * @brief Получить цену фигуры
     *
     * @return Цена фигуры
     */
    int GetFigureValue();
    /**
     * @brief Получить тип фигуры (пешка, колорь и т.д.)
     *
     * @return Тип фигуры
     */
    FigureType GetFigureType();
    /**
     * @brief Получить цвет фигуры
     *
     * @return Цвет фигуры
     */
    Color GetFigureColor();
};

/**
 * @brief Класс клетки доски
 */
class Cell {
 private:
    /**
     * @brief Цвет клетки
     */
    Color cellColor;
    /**
     * @brief Фигура на клетке
     */
    Figure figure;
    /**
     * @brief Пустая ли клетка
     */
    bool isEmpty;

 public:
    /**
     * @brief Создаёт клетку по цвету
     *
     * @param Цвет клетки (по умолчанию белая)
     * @return Объект класса Cell
     */
    Cell(Color cellColor = Color::WHITE);
    /**
     * @brief Создаёт клетку по цвету и фигуре
     *
     * @param Цвет клетки
     * @param Фигура которая находится на клетке
     * @return Объект класса Cell
     */
    Cell(Color cellColor, Figure figure);

    /**
     * @brief Печатает строчку клетки по номеру строчки
     *
     * @param cellLine Номер строчки клетки, отчёт начинается с нуля
     */
    void PrintCell(int cellLine);

    /**
     * @brief Ставит нужную фигуру на клетку
     *
     * @param Объект класса Figure
     */
    void SetFigure(Figure figure);
    /**
     * @brief Получить фигуру на клетке
     *
     * @param Объект класса Figure
     */
    Figure GetFigure();
    /**
     * @brief Получить цвет клетки
     *
     * @return Объект enum-а Color
     */
    Color GetCellColor();
};

/**
 * @brief Класс игры Шахматы
 */
class Chess : public game::Game {
 private:
    /**
     * @brief Шахматная доска
     */
    Cell desk[BOARD_SIZE][BOARD_SIZE];

    /**
     * @brief Выводит доску на экран
     */
    void PrintBoard();

 public:
    /**
     * @brief Создаёт доску с раставленными фигурами по умолчанию
     *
     * @return Объект класса Chess
     */
    Chess();

    /**
     * @brief Запускает игру
     */
    void Run() override;
    /**
     * @brief Получить название игры
     *
     * @return Название игры
     */
    const std::string GetName() override;
    /**
     * @brief Получить описание игры
     *
     * @return Описание игры
     */
    const std::string GetDescription() override;
    /**
     * @brief .txt файл с лого, можно взять с сайта https://textkool.com/en/ascii-art-generator?hl=default&vl=default&font=Delta%20Corps%20Priest%201
     *
     * @return Имя файла с логотипом
     */
    const std::string GetLogoFile() override;
};
}  // namespace chess
