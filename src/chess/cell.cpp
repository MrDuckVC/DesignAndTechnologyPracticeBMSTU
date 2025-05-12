#include "cell.h"

namespace chess {
Cell::Cell(Color cellColor) : cellColor(cellColor), figure(), isEmpty(true) {
    FillCellColor();
}

Color Cell::GetCellColor() {
    return cellColor;
}
Figure& Cell::GetFigure() {
    return figure;
}
bool Cell::IsEmpty() {
    return isEmpty;
}
sf::RectangleShape& Cell::GetCellShape() {
    return cellShape;
}
void Cell::SetCellColor(Color color) {
    cellColor = color;
    FillCellColor();
}
void Cell::SetFigure(Figure figure) {
    this->figure = figure;
    isEmpty = false;
}
void Cell::MakeEmpty() {
    this->isEmpty = true;
    this->figure = Figure();
}

void Cell::FillCellColor() {
    cellShape.setFillColor(cellColor == Color::WHITE ? WHITE_CELL_COLOR : BLACK_CELL_COLOR);
}

}  // namespace chess
