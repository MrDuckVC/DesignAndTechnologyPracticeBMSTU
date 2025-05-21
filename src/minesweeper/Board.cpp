#include "Board.hpp"

Board::Board() {
    bombCount = 0;
    bombRemaining = 0;
    unrevealedTileCount = 0;
    bombBlasted = false;
    InitTiles();
}

void Board::DeleteAllTiles() {
    if (tiles == NULL) {
        return;
    }
    for (int i = 0; i < tileCount.y; ++i) {
        delete[] tiles[i];
    }
    delete[] tiles;
}

Board::~Board() {
    DeleteAllTiles();
}

void Board::InitTiles() {
    tiles = new Tile*[tileCount.x];
    for (int i = 0; i < tileCount.x; ++i) {
        tiles[i] = new Tile[tileCount.y];
    }
}

void Board::CreateAllTiles() {
    Vector2f tilePos;
    for (int i = 0; i < tileCount.x; ++i) {
        for (int j = 0; j < tileCount.y; ++j) {
            tilePos = areaPosition + Vector2f(i * tileSize.x, j * tileSize.y);
            tiles[i][j].CreateTile(tilePos, tileSize);
        }
    }
    unrevealedTileCount = tileCount.x * tileCount.y;
}

void Board::SetBombs() {
    srand(static_cast<unsigned>(time(0)));
    int x, y;
    for (int i = 1; i <= bombCount; ++i) {
        do {
            x = rand() % tileCount.x;
            y = rand() % tileCount.y;
        } while (tiles[x][y].IsBomb());
        tiles[x][y].SetBomb();
    }
    bombRemaining = bombCount;
}

bool Board::CheckInBounds(int x, int y) {
    return x >= 0 && y >= 0 && x < tileCount.x && y < tileCount.y;
}

int Board::SetSingleAdjacent(int x, int y) {
    Vector2i index;
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            index.x = x + i;
            index.y = y + j;
            if (CheckInBounds(index.x, index.y)) {
                if (tiles[index.x][index.y].IsBomb()) {
                    count++;
                }
            }
        }
    }
    return count;
}

void Board::SetAllAdjacentNumbers() {
    for (int i = 0; i < tileCount.x; ++i) {
        for (int j = 0; j < tileCount.y; ++j) {
            tiles[i][j].SetAdjacent(SetSingleAdjacent(i, j));
        }
    }
}

void Board::SetTileProperities() {
    CreateAllTiles();
    SetBombs();
    SetAllAdjacentNumbers();
}

Vector2i Board::FindTileIndex(Vector2i mousePos) {
    mousePos -= static_cast<Vector2i>(areaPosition);
    mousePos.x /= static_cast<int>(tileSize.x);
    mousePos.y /= static_cast<int>(tileSize.y);

    return mousePos;
}

void Board::CreateNewBoard(RectangleShape area, int bombs) {
    bombCount = bombs;
    areaPosition = area.getPosition();
    tileSize.x = area.getSize().x / tileCount.x;
    tileSize.y = area.getSize().y / tileCount.y;
    ResetBoard();
}

void Board::ResetBoard() {
    bombRemaining = bombCount;
    bombBlasted = false;
    DeleteAllTiles();
    InitTiles();
    SetTileProperities();
}

void Board::FloodFill(Vector2i pos) {
    if (tiles[pos.x][pos.y].GetAdjacentCount() == 0) {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int x = pos.x + i;
                int y = pos.y + j;

                if (x != pos.x || y != pos.y) {
                    if (CheckInBounds(x, y)) {
                        bool revealed = tiles[x][y].Reveal(false);
                        if (revealed) {
                            unrevealedTileCount--;
                            FloodFill(Vector2i(x, y));
                        }
                    }
                }
            }
        }
    }
}

void Board::LeftButton(Vector2i mousePos) {
    Vector2i index = FindTileIndex(mousePos);
    bool revealed = tiles[index.x][index.y].Reveal(true);

    if (revealed) {
        if (tiles[index.x][index.y].IsBomb()) {
            bombBlasted = true;
        } else if (tiles[index.x][index.y].GetAdjacentCount() == 0) {
            FloodFill(index);
            unrevealedTileCount--;
        } else {
            unrevealedTileCount--;
        }
    }
}

void Board::RightButton(Vector2i mousePos) {
    Vector2i index = FindTileIndex(mousePos);
    bool marked = tiles[index.x][index.y].Mark();

    if (tiles[index.x][index.y].IsRevealed()) {
        return;
    }

    if (marked) {
        --bombRemaining;
    } else {
        ++bombRemaining;
    }
}
void Board::RevealAll() {
    for (int i = 0; i < tileCount.x; ++i) {
        for (int j = 0; j < tileCount.y; ++j) {
            tiles[i][j].Reveal(false);
        }
    }
}

bool Board::IsLoss() {
    if (bombBlasted) {
        RevealAll();
    }
    return bombBlasted;
}

bool Board::IsWin() {
    if (bombCount == unrevealedTileCount) {
        RevealAll();
        return true;
    }
    return false;
}

int Board::GetRemainingBombs() {
    return bombRemaining;
}

void Board::RenderBoard(RenderWindow& window) {
    for (int i = 0; i < tileCount.x; ++i) {
        for (int j = 0; j < tileCount.y; ++j) {
            tiles[i][j].Render(window);
        }
    }
}
