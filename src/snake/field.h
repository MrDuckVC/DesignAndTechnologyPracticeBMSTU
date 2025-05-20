#pragma once

#include <SFML/Graphics.hpp>

class Field {
 private:
    struct Position {
        int x, y;
    };

    Position normalizePosition(int x, int y) const;
    int tileLength0;

    sf::RectangleShape fieldRect0;
    int width0;
    int height0;

    std::vector<std::vector<bool>> matrix0;
    std::vector<int> matrixCountFree0;

 public:
    Field(int width, int height, int tileLength, sf::Texture* texture);
    ~Field();

    int getTileLength() { return tileLength0; }
    int getWidth() { return width0; }
    int getHeight() { return height0; }

    void setBlock(int x, int y);
    void removeBlock(int x, int y);

    std::vector<std::vector<bool>> getRowsWithFreeTiles() const;

    int normalizeVerticalPos(int y) const;
    int normalizeHorizontalPos(int y, int x) const;

    int getFreeTilesCount(int rowIndex) const;

    bool isPosInField(int x, int y) const;

    sf::Drawable* getRectToDraw() const { return (sf::Drawable*)&fieldRect0; };
};
