#include "figure.h"

namespace chess {
sf::Texture Figure::LoadTexture(std::string path) {
    sf::Texture texture;
    if (!texture.loadFromFile(path)) {
        throw std::runtime_error("Failed to load figure texture");
    }
    return texture;
}
std::map<std::pair<FigureType, Color>, sf::Texture> Figure::figureTextures = {
    {{FigureType::PAWN, Color::WHITE},   LoadTexture(WHITE_PAWN_IMAGE_PATH)  },
    {{FigureType::PAWN, Color::BLACK},   LoadTexture(BLACK_PAWN_IMAGE_PATH)  },
    {{FigureType::KNIGHT, Color::WHITE}, LoadTexture(WHITE_KNIGHT_IMAGE_PATH)},
    {{FigureType::KNIGHT, Color::BLACK}, LoadTexture(BLACK_KNIGHT_IMAGE_PATH)},
    {{FigureType::BISHOP, Color::WHITE}, LoadTexture(WHITE_BISHOP_IMAGE_PATH)},
    {{FigureType::BISHOP, Color::BLACK}, LoadTexture(BLACK_BISHOP_IMAGE_PATH)},
    {{FigureType::ROOK, Color::WHITE},   LoadTexture(WHITE_ROOK_IMAGE_PATH)  },
    {{FigureType::ROOK, Color::BLACK},   LoadTexture(BLACK_ROOK_IMAGE_PATH)  },
    {{FigureType::QUEEN, Color::WHITE},  LoadTexture(WHITE_QUEEN_IMAGE_PATH) },
    {{FigureType::QUEEN, Color::BLACK},  LoadTexture(BLACK_QUEEN_IMAGE_PATH) },
    {{FigureType::KING, Color::WHITE},   LoadTexture(WHITE_KING_IMAGE_PATH)  },
    {{FigureType::KING, Color::BLACK},   LoadTexture(BLACK_KING_IMAGE_PATH)  },
};

Figure::Figure(FigureType figureType, Color figureColor)
    : figureType(figureType),
      figureColor(figureColor),
      figureSprite(Figure::figureTextures[{figureType, figureColor}]),
      isSelected(false),
      movesCount(0) {
}

FigureType Figure::GetFigureType() {
    return figureType;
}
Color Figure::GetFigureColor() {
    return figureColor;
}
bool Figure::IsSelected() {
    return isSelected;
}
int Figure::GetMovesCount() {
    return movesCount;
}
sf::Sprite Figure::GetFigureSprite() {
    return figureSprite;
}
void Figure::SetIsSelected(bool selected) {
    isSelected = selected;
}

void Figure::CountOneMove() {
    movesCount++;
}
}  // namespace chess
