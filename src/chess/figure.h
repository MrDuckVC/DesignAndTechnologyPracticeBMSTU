#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include "untils.h"
#include "conf.h"

namespace chess {
class Figure {
 private:
    FigureType figureType;
    Color figureColor;
    bool isSelected;
    int movesCount;

    sf::Sprite figureSprite;
 public:
    static std::map<std::pair<FigureType, Color>, sf::Texture> figureTextures;
    static sf::Texture LoadTexture(std::string pat);

    Figure(FigureType figureType = FigureType::PAWN, Color figureColor = Color::WHITE);

    FigureType GetFigureType();
    Color GetFigureColor();
    bool IsSelected();
    int GetMovesCount();
    sf::Sprite GetFigureSprite();
    void SetIsSelected(bool selected);

    void CountOneMove();
};
}  // namespace chess
