#include "chess.h"

#include <iostream>

namespace {
const char PAWN_SYMBOL = 'P';
const char KNIGHT_SYMBOL = 'N';
const char BISHOP_SYMBOL = 'B';
const char ROOK_SYMBOL = 'R';
const char QUEEN_SYMBOL = 'Q';
const char KING_SYMBOL = 'K';

const int PAWN_VALUE = 1;
const int KNIGHT_VALUE = 3;
const int BISHOP_VALUE = 3;
const int ROOK_VALUE = 5;
const int QUEEN_VALUE = 9;
const int KING_VALUE = 0;
} // namespace

namespace chess {
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
    switch (figureType) {
    case FigureType::PAWN:
        std::cout << PAWN_SYMBOL;
        break;
    case FigureType::KNIGHT:
        std::cout << KNIGHT_SYMBOL;
        break;
    case FigureType::BISHOP:
        std::cout << BISHOP_SYMBOL;
        break;
    case FigureType::ROOK:
        std::cout << ROOK_SYMBOL;
        break;
    case FigureType::QUEEN:
        std::cout << QUEEN_SYMBOL;
        break;
    case FigureType::KING:
        std::cout << KING_SYMBOL;
        break;
    }
}

int Figure::GetFigureValue() { return figureValue; }

FigureType Figure::GetFigureType() { return figureType; }

Color Figure::GetFigureColor() { return figureColor; }

void Chess::PrintBoard() {}

void Chess::Run() {}

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
} // namespace chess
