#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>

#define FLAG "assets/minesweeper/Sprites/flag.png"
#define BOMB "assets/minesweeper/Sprites/mine.png"


class Tile {
 private:
 	sf::RectangleShape tile;
    bool isBomb;
    bool isBlasted;

    bool isRevealed;
    bool isMarked;

    int adjacentCount;

    sf::Color outline;
    sf::Color default_Color;
    sf::Color reveal;
    sf::Color blasted;
    sf::Color marked;

    sf::Font font;
    sf::Text number;
    static sf::Texture flagTexture;
    static sf::Texture mineTexture;
    sf::Sprite mineSprite;
    sf::Sprite flagSprite;

 public:
    static void LoadTexture();

    Tile();

    void CreateTile(sf::Vector2f pos, sf::Vector2f size);

    void SetAdjacent(int count);
    int GetAdjacentCount();

    void SetBomb();
    bool IsBomb();

    int Mark();

    bool IsRevealed();
    bool Reveal(bool clicked);
    void Render(sf::RenderWindow& window);
};
