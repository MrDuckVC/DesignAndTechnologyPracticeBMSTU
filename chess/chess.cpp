#include "chess.h"

#include <iostream>
#include <iomanip>
#include <string>

namespace {
/// @name Символы для заполнения шахматного поля
/// @{
const std::string WHITE_SQUARE_SYMBOL = "█"; ///< Символ для белого квадрата
const std::string BLACK_SQUARE_SYMBOL = " "; ///< Символ для чёрного квадрата
/// @}

/// @name Символы шахматных фигурок чёрного цвета.
/// @{
const std::string BLACK_PAWN_SYMBOL = "\u2659"; // Чёрная пешка, ♟
const std::string BLACK_KNIGHT_SYMBOL = "\u2658"; // Чёрный конь, ♞
const std::string BLACK_BISHOP_SYMBOL = "\u2657"; // Чёрный слон, ♝
const std::string BLACK_ROOK_SYMBOL = "\u2656"; // Чёрная ладья, ♜
const std::string BLACK_QUEEN_SYMBOL = "\u2655"; // Чёрная ферзь, ♛
const std::string BLACK_KING_SYMBOL = "\u2654"; // Чёрный король, ♚
/// @}

/// @name Символы шахматных фигурок белого цвета.
/// @{
const std::string WHITE_PAWN_SYMBOL = "\u265F"; // Белая пешка, ♙
const std::string WHITE_KNIGHT_SYMBOL = "\u265E"; // Белый конь, ♘
const std::string WHITE_BISHOP_SYMBOL = "\u265D"; // Белый слон, ♗
const std::string WHITE_ROOK_SYMBOL = "\u265C"; // Белая ладья, ♖
const std::string WHITE_QUEEN_SYMBOL = "\u265B"; // Белая ферзь, ♕
const std::string WHITE_KING_SYMBOL = "\u265A"; // Белый король, ♔
/// @}

/// @name Цена шахматных фигур.
/// @{
const int PAWN_VALUE = 1; ///< Цена пешки
const int KNIGHT_VALUE = 3; ///< Цена коня
const int BISHOP_VALUE = 3; ///< Цена слона
const int ROOK_VALUE = 5; ///< Цена ладьи
const int QUEEN_VALUE = 9; ///< Цена ферзя
const int KING_VALUE = 0; ///< Цена короля
/// @}

/**
 * @brief Вывод квадрата нужного цвета (занимает 2 символа)
 *
 * @param color Цвет квадрата
 */
void PrintColorSquare(chess::Color color) {
    if (color == chess::Color::WHITE) {
        std::cout << WHITE_SQUARE_SYMBOL << WHITE_SQUARE_SYMBOL;
    } else {
        std::cout << BLACK_SQUARE_SYMBOL << BLACK_SQUARE_SYMBOL;
    }
}
} // namespace

namespace chess {
Figure::Figure() : figureType(FigureType::PAWN), figureColor(Color::WHITE), figureValue(0) {};
Figure::Figure(FigureType figureType, Color figureColor) : figureType(figureType), figureColor(figureColor) {
    switch (figureType) {
    case FigureType::PAWN:
        figureValue = PAWN_VALUE;
        break;
    case FigureType::KNIGHT:
        figureValue = KNIGHT_VALUE;
        break;
    case FigureType::BISHOP:
        figureValue = BISHOP_VALUE;
        break;
    case FigureType::ROOK:
        figureValue = ROOK_VALUE;
        break;
    case FigureType::QUEEN:
        figureValue = QUEEN_VALUE;
        break;
    case FigureType::KING:
        figureValue = KING_VALUE;
        break;
    default:
        throw std::invalid_argument("Uknown `FigureType` to set `figureValue`.");
        break;
    }
}

void Figure::PrintFigure() {
    if (figureColor == Color::BLACK) {
        switch (figureType) {
        case FigureType::PAWN:
            std::cout << BLACK_PAWN_SYMBOL;
            break;
        case FigureType::KNIGHT:
            std::cout << BLACK_KNIGHT_SYMBOL;
            break;
        case FigureType::BISHOP:
            std::cout << BLACK_BISHOP_SYMBOL;
            break;
        case FigureType::ROOK:
            std::cout << BLACK_ROOK_SYMBOL;
            break;
        case FigureType::QUEEN:
            std::cout << BLACK_QUEEN_SYMBOL;
            break;
        case FigureType::KING:
            std::cout << BLACK_KING_SYMBOL;
            break;
        default:
            throw std::invalid_argument("Uknown `FigureType` to set `figureValue`.");
            break;
        }
    } else if (figureColor == Color::WHITE) {
        switch (figureType) {
        case FigureType::PAWN:
            std::cout << WHITE_PAWN_SYMBOL;
            break;
        case FigureType::KNIGHT:
            std::cout << WHITE_KNIGHT_SYMBOL;
            break;
        case FigureType::BISHOP:
            std::cout << WHITE_BISHOP_SYMBOL;
            break;
        case FigureType::ROOK:
            std::cout << WHITE_ROOK_SYMBOL;
            break;
        case FigureType::QUEEN:
            std::cout << WHITE_QUEEN_SYMBOL;
            break;
        case FigureType::KING:
            std::cout << WHITE_KING_SYMBOL;
            break;
        default:
            throw std::invalid_argument("Uknown `FigureType` to set `figureValue`.");
            break;
        }
    }
    std::cout << BLACK_SQUARE_SYMBOL;
}

int Figure::GetFigureValue() { return figureValue; }
FigureType Figure::GetFigureType() { return figureType; }
Color Figure::GetFigureColor() { return figureColor; }

Cell::Cell(Color cellColor) : cellColor(cellColor), figure(), isEmpty(true) {}
Cell::Cell(Color cellColor, Figure figure) : cellColor(cellColor), figure(figure), isEmpty(false) {}

void Cell::PrintCell(int cellLine) {
    if (!isEmpty && ((CELL_SIZE - 1) / 2) == cellLine) {
        // Если это строчка с фигурой
        for (int i = 0; i < (CELL_SIZE - 1) / 2; ++i) {
            PrintColorSquare(cellColor);
        }
        figure.PrintFigure();
        for (int i = 0; i < (CELL_SIZE - 1) / 2; ++i) {
            PrintColorSquare(cellColor);
        }
    } else {
        for (int i = 0; i < CELL_SIZE; ++i) {
            PrintColorSquare(cellColor);
        }
    }
}

void Cell::SetFigure(Figure figure) {
    this->figure = figure;
    isEmpty = false;
}
Figure Cell::GetFigure() {
    return figure;
}
Color Cell::GetCellColor() {
    return cellColor;
}

Chess::Chess() {
    // Раскрашиваю доску.
    const Color colorForEvenCells = Color::WHITE;
    const Color colorForNonEvenCells = Color::BLACK;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if ((i + j) % 2 == 0) {
                desk[i][j] = Cell(colorForEvenCells);
            } else {
                desk[i][j] = Cell(colorForNonEvenCells);
            }
        }
    }

    // Белые фигуры на 1-2 линиях.
    desk[0][0].SetFigure(Figure(FigureType::ROOK, Color::WHITE));
    desk[0][1].SetFigure(Figure(FigureType::KNIGHT, Color::WHITE));
    desk[0][2].SetFigure(Figure(FigureType::BISHOP, Color::WHITE));
    desk[0][3].SetFigure(Figure(FigureType::QUEEN, Color::WHITE));
    desk[0][4].SetFigure(Figure(FigureType::KING, Color::WHITE));
    desk[0][5].SetFigure(Figure(FigureType::BISHOP, Color::WHITE));
    desk[0][6].SetFigure(Figure(FigureType::KNIGHT, Color::WHITE));
    desk[0][7].SetFigure(Figure(FigureType::ROOK, Color::WHITE));
    for (int i = 0; i < 8; ++i) {
        if (i % 2 == 0) {
            desk[1][i].SetFigure(Figure(FigureType::PAWN, Color::WHITE));
        } else {
            desk[1][i].SetFigure(Figure(FigureType::PAWN, Color::WHITE));
        }
    }

    // Чёрные фигуры на 7-8 линиях.
    for (int i = 0; i < 8; ++i) {
        if (i % 2 == 0) {
            desk[6][i].SetFigure(Figure(FigureType::PAWN, Color::BLACK));
        } else {
            desk[6][i].SetFigure(Figure(FigureType::PAWN, Color::BLACK));
        }
    }
    desk[7][0].SetFigure(Figure(FigureType::ROOK, Color::BLACK));
    desk[7][1].SetFigure(Figure(FigureType::KNIGHT, Color::BLACK));
    desk[7][2].SetFigure(Figure(FigureType::BISHOP, Color::BLACK));
    desk[7][3].SetFigure(Figure(FigureType::QUEEN, Color::BLACK));
    desk[7][4].SetFigure(Figure(FigureType::KING, Color::BLACK));
    desk[7][5].SetFigure(Figure(FigureType::BISHOP, Color::BLACK));
    desk[7][6].SetFigure(Figure(FigureType::KNIGHT, Color::BLACK));
    desk[7][7].SetFigure(Figure(FigureType::ROOK, Color::BLACK));
}

void Chess::PrintBoard() {
    // Пропускаем место для численных координат.
    std::cout << "    ";

    // Печатаем строчку с буквенными координатами.
    char letterCoord = 'a'; // Начальная буква для буквенных координат.
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < (CELL_SIZE - 1) / 2; ++j) {
            std::cout << "  ";
        }
        std::cout << letterCoord << ' ';
        for (int j = 0; j < (CELL_SIZE - 1) / 2; ++j) {
            std::cout << "  ";
        }
        letterCoord++;
    }
    std::cout << std::endl;

    // Печатаем остальную часть.
    int numCord = 1;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int k = 0; k < CELL_SIZE; ++k) {
            // Печатаем численные координаты
            if (k == (CELL_SIZE - 1) / 2) {
                // Функция std::setw(2) имеет параметр 2, так как программа расчитана что поле будет максимум 26х26 (т.е. не более 2 символов в номере).
                std::cout << std::setw(2) << numCord;
            } else {
                std::cout << "  ";  // Тут 2 пробела (чтобы не считали).
            }
            std::cout << "  ";  // Тут 2 пробела (чтобы не считали).

            // Печатаем клеточки.
            for (int j = 0; j < BOARD_SIZE; ++j) {
                desk[i][j].PrintCell(k);
            }
            std::cout << std::endl;
        }
        numCord++;
    }
}

void Chess::Run() {
    // TODO
}

const std::string Chess::GetName() { return "Chess"; }
const std::string Chess::GetDescription() {
    return "Chess is an abstract strategy board game for two players which "
           "involves no hidden information and no elements of chance. It is "
           "played on a square game board called a chessboard containing 64 "
           "squares arranged in an 8×8 grid. The players, referred to as "
           "\"White\" and \"Black\", each control sixteen pieces: one king, one "
           "queen, two rooks, two bishops, two knights, and eight pawns; each "
           "type of piece has a different pattern of movement. An enemy piece "
           "may be \"captured\" (removed from the board) by moving one's own "
           "piece onto the square it occupies; the object of the game is to "
           "\"checkmate\" (threaten with inescapable capture) the enemy king. "
           "There are also several ways a game can end in a draw.";
}
const std::string Chess::GetLogoFile() {return "./chess/chessLogo.txt";}
} // namespace chess
