#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Tile.hpp"

class Board {
 private:
    Vector2f tileSize;
    Vector2i tileCount = Vector2i(12, 12);

    Tile** tiles;

    Vector2f areaPosition;
    Vector2f areaSize;

    int bombCount;
    int bombRemaining;
    int unrevealedTileCount;

    bool bombBlasted;

    void RevealAll();
    void InitTiles();
    bool CheckInBounds(int x, int y);
    void CreateAllTiles();
    void SetBombs();
    int SetSingleAdjacent(int x, int y);
    void SetAllAdjacentNumbers();
    void SetTileProperities();
    Vector2i FindTileIndex(Vector2i mousePos);
    void FloodFill(Vector2i pos);
    void DeleteAllTiles();

 public:
    Board();
    virtual ~Board();

    void CreateNewBoard(RectangleShape area, int bombs);
    void ResetBoard();
    void LeftButton(Vector2i mousePos);
    void RightButton(Vector2i mousePos);
    bool IsLoss();
    bool IsWin();
    int GetRemainingBombs();
    void RenderBoard(RenderWindow& window);
};
