#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>

#define FLAG "assests/minesweeper/Sprites/flag.png"
#define BOMB "assests/minesweeper/Sprites/mine.png"

using namespace sf;

class Tile {
 private:
    RectangleShape tile;
    bool isBomb;
    bool isBlasted;

    bool isRevealed;
    bool isMarked;

    int adjacentCount;

    Color outline;
    Color default_Color;
    Color reveal;
    Color blasted;
    Color marked;

    Font font;
    Text number;
    static Texture flagTexture;
    static Texture mineTexture;
    Sprite mineSprite;
    Sprite flagSprite;

 public:
    static void LoadTexture();

    Tile();

    void CreateTile(Vector2f pos, Vector2f size);

    void SetAdjacent(int count);
    int GetAdjacentCount();

    void SetBomb();
    bool IsBomb();

    int Mark();

    bool IsRevealed();
    bool Reveal(bool clicked);
    void Render(RenderWindow& window);
};
