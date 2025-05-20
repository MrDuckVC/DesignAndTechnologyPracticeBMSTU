#include <iostream>

#include "field.h"

// Преобразование пиксельных координат в индексы клеток
Field::Position Field::normalizePosition(int x, int y) const {
  if ((x % tileLength0) == 0 && (y % tileLength0) == 0)
    return Position{x / tileLength0, y / tileLength0};
  return Position{0, 0};
}

// Конструктор поля
Field::Field(int width, int height, int tileLength, sf::Texture *texture)
    : width0(width), height0(height), tileLength0(tileLength) {
  fieldRect0.setSize({width0 * tileLength0, height0 * tileLength0});

  texture->setRepeated(true);

  fieldRect0.setTexture(texture);
  fieldRect0.setTextureRect(
      sf::IntRect({0, 0}, {width0 * tileLength0, height0 * tileLength0}));

  // Матрица занятости клеток в виде карты
  matrix0.resize(height0);
  for (int i = 0; i < height0; i++) {
    matrix0[i].resize(width0);
    for (int j = 0; j < width0; j++)
      matrix0[i][j] = false;
  }

  // Матрица занятости клеток с подсчетом количества
  matrixCountFree0.resize(height0);
  for (int i = 0; i < height0; i++)
    matrixCountFree0[i] = 0;
}

Field::~Field() {}

// Пометка заблокированной клетки
void Field::setBlock(int x, int y) {
  Position pos = normalizePosition(x, y);
  matrix0[pos.y][pos.x] = true;
  matrixCountFree0[pos.y]++;
}

// Удаление пометки заблокированной клетки
void Field::removeBlock(int x, int y) {
  Position pos = normalizePosition(x, y);
  matrix0[pos.y][pos.x] = false;
  matrixCountFree0[pos.y]--;
}

// Список строк со свободными клетками
std::vector<std::vector<bool>> Field::getRowsWithFreeTiles() const {
  std::vector<std::vector<bool>> vect;
  for (int i = 0; i < height0; i++)
    if (matrixCountFree0[i] < width0)
      vect.push_back(matrix0[i]);

  return vect;
}

// Нормализует позицию строки в списке в координату строки
int Field::normalizeVerticalPos(int y) const {
  for (int i = 0, j = y; i < height0; i++) {
    if (matrixCountFree0[i] < width0) {
      if (j > 0)
        j--;
      else
        return i * tileLength0;
    }
  }
  return -1;
}

// Нормализует номер позиции в строке в координату
int Field::normalizeHorizontalPos(int y, int x) const {
  int row = y / tileLength0;

  for (int i = 0, j = x; i < width0; i++) {
    if (matrix0[row][i] == false) {
      if (j > 0)
        --j;
      else
        return i * tileLength0;
    }
  }
  return -1;
}

// Получение количества свободных клеток
int Field::getFreeTilesCount(int y) const {
  return width0 - matrixCountFree0[y / tileLength0];
}

// Проверка, чтобы точка была внутри поля
bool Field::isPosInField(int x, int y) const {
  if ((x >= 0 && x < width0 * tileLength0) &&
      (y >= 0 && y < height0 * tileLength0))
    return true;
  return false;
}
