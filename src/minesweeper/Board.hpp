#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Tile.hpp"

class Board {
 private:
    sf::Vector2f tileSize;
    sf::Vector2i tileCount = sf::Vector2i(12, 12);

    Tile** tiles;

    sf::Vector2f areaPosition;
    sf::Vector2f areaSize;

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
    sf::Vector2i FindTileIndex(sf::Vector2i mousePos);
    void FloodFill(sf::Vector2i pos);
    void DeleteAllTiles();

 public:
    Board();
    virtual ~Board();

    void CreateNewBoard(sf::RectangleShape area, int bombs);
    void ResetBoard();
    void LeftButton(sf::Vector2i mousePos);
    void RightButton(sf::Vector2i mousePos);
    bool IsLoss();
    bool IsWin();
    int GetRemainingBombs();
    void RenderBoard(sf::RenderWindow& window);
};
