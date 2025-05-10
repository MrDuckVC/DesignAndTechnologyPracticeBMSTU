#include "chess.h"

namespace {}

namespace chess {
sf::Texture Figure::LoadTexture(std::string path) {
    sf::Texture texture;
    if (!texture.loadFromFile(path)) {
        throw std::runtime_error("Failed to load figure texture");
    }
    return texture;
}

std::map<std::pair<FigureType, Color>, sf::Texture> Figure::figureTextures = {
    {{FigureType::PAWN, Color::WHITE},   LoadTexture("assests/chess/pawn.png")},
    {{FigureType::PAWN, Color::BLACK},   LoadTexture("assests/chess/pawn1.png")},
    {{FigureType::KNIGHT, Color::WHITE}, LoadTexture("assests/chess/knight.png")},
    {{FigureType::KNIGHT, Color::BLACK}, LoadTexture("assests/chess/knight1.png")},
    {{FigureType::BISHOP, Color::WHITE}, LoadTexture("assests/chess/bishop.png")},
    {{FigureType::BISHOP, Color::BLACK}, LoadTexture("assests/chess/bishop1.png")},
    {{FigureType::ROOK, Color::WHITE},   LoadTexture("assests/chess/rook.png")},
    {{FigureType::ROOK, Color::BLACK},   LoadTexture("assests/chess/rook1.png")},
    {{FigureType::QUEEN, Color::WHITE},  LoadTexture("assests/chess/queen.png")},
    {{FigureType::QUEEN, Color::BLACK},  LoadTexture("assests/chess/queen1.png")},
    {{FigureType::KING, Color::WHITE},   LoadTexture("assests/chess/king.png")},
    {{FigureType::KING, Color::BLACK},   LoadTexture("assests/chess/king1.png")},
};

Figure::Figure(FigureType figureType, Color figureColor) : figureType(figureType), figureColor(figureColor), figureSprite(Figure::figureTextures[{figureType, figureColor}]) {
    // figureSprite.setScale({(WINDOW_SIZE / static_cast<float>(Figure::figureTextures[{figureType, figureColor}].getSize().x)) / BOARD_SIZE,
    //                        (WINDOW_SIZE / static_cast<float>(Figure::figureTextures[{figureType, figureColor}].getSize().y)) / BOARD_SIZE});
    // figureSprite.setPosition({140, 20});
}

FigureType Figure::GetFigureType() {
    return figureType;
}
Color Figure::GetFigureColor() {
    return figureColor;
}
sf::Sprite Figure::GetFigureSprite() {
    return figureSprite;
}

void Figure::SetFigureSpritePosition(float x, float y) {
    figureSprite.setPosition({x, y});
}

void Cell::FillCellColor() {
    cellShape.setFillColor(cellColor == Color::WHITE ? sf::Color(240, 195, 128) : sf::Color(109, 62, 23));
}

Cell::Cell(Color cellColor) : cellColor(cellColor), figure(), isEmpty(true) {
    FillCellColor();
}
Cell::Cell(Color cellColor, Figure figure) : cellColor(cellColor), figure(figure), isEmpty(false) {
    FillCellColor();
}

void Cell::SetFigure(Figure figure) {
    this->figure = figure;
    isEmpty = false;
}
void Cell::SetCellColor(Color color) {
    cellColor = color;
    FillCellColor();
}
void Cell::SetCellShapPosition(float x, float y) {
    cellShape.setPosition({x, y});
}
void Cell::MakeEmply() {
    this->figure = Figure();
    isEmpty = true;
}
Figure Cell::GetFigure() {
    return figure;
}
Color Cell::GetCellColor() {
    return cellColor;
}
sf::RectangleShape Cell::GetCellShape() {
    return cellShape;
}
bool Cell::IsEmpty() {
    return isEmpty;
}

void Chess::DrawBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            window.draw(desk[j][i].GetCellShape());
        }
    }
}

void Chess::DrawFigures() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (!desk[j][i].IsEmpty()) {
                sf::Sprite sprite = desk[j][i].GetFigure().GetFigureSprite();
                sprite.setOrigin(sprite.getGlobalBounds().getCenter());
                sprite.setPosition(desk[i][j].GetCellShape().getGlobalBounds().getCenter());
                sprite.setScale({2.0f, 2.0f});
                window.draw(sprite);
            }
        }
    }
}

Chess::Chess(sf::RenderWindow& window) : Game(window) {
    // Растановка клеток.
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            desk[i][j].SetCellShapPosition(i * (WINDOW_SIZE / BOARD_SIZE), j * (WINDOW_SIZE / BOARD_SIZE));
        }
    }

    // Раскрашиваю доску.
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if ((i + j) % 2 == 0) {
                desk[i][j].SetCellColor(Color::BLACK);
            } else {
                desk[i][j].SetCellColor(Color::WHITE);
            }
        }
    }

    // Расставляю фигуры.
    // Белые фигуры на 1-2 линиях.
    for (int i = 0; i < BOARD_SIZE; i++) {
        desk[1][i].SetFigure(Figure(FigureType::PAWN, Color::WHITE));
    }
    desk[0][0].SetFigure(Figure(FigureType::ROOK, Color::WHITE));
    desk[0][1].SetFigure(Figure(FigureType::KNIGHT, Color::WHITE));
    desk[0][2].SetFigure(Figure(FigureType::BISHOP, Color::WHITE));
    desk[0][3].SetFigure(Figure(FigureType::QUEEN, Color::WHITE));
    desk[0][4].SetFigure(Figure(FigureType::KING, Color::WHITE));
    desk[0][5].SetFigure(Figure(FigureType::BISHOP, Color::WHITE));
    desk[0][6].SetFigure(Figure(FigureType::KNIGHT, Color::WHITE));
    desk[0][7].SetFigure(Figure(FigureType::ROOK, Color::WHITE));
    // Чёрные фигуры на 7-8 линиях.
    for (int i = 0; i < BOARD_SIZE; i++) {
        desk[6][i].SetFigure(Figure(FigureType::PAWN, Color::BLACK));
    }
    desk[7][0].SetFigure(Figure(FigureType::ROOK, Color::BLACK));
    desk[7][1].SetFigure(Figure(FigureType::KNIGHT, Color::BLACK));
    desk[7][2].SetFigure(Figure(FigureType::BISHOP, Color::BLACK));
    desk[7][3].SetFigure(Figure(FigureType::QUEEN, Color::BLACK));
    desk[7][4].SetFigure(Figure(FigureType::KING, Color::BLACK));
    desk[7][5].SetFigure(Figure(FigureType::BISHOP, Color::BLACK));
    desk[7][6].SetFigure(Figure(FigureType::KNIGHT, Color::BLACK));
    desk[7][7].SetFigure(Figure(FigureType::ROOK, Color::BLACK));
}

void Chess::PlaceFigures() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            desk[i][j].GetFigure().SetFigureSpritePosition(i * (WINDOW_SIZE / BOARD_SIZE), j * (WINDOW_SIZE / BOARD_SIZE));
        }
    }
}

void Chess::Run() {
    PlaceFigures();
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (event->is<sf::Event::Resized>()) {
                window.setSize({WINDOW_SIZE, WINDOW_SIZE});
            } else if (const sf::Event::KeyPressed* keyPressed = event->getIf<sf::Event::KeyPressed>()) {  // Если нажата клавиша
                switch (keyPressed->scancode) {
                    case (sf::Keyboard::Scancode::Escape):  // Если нажата клавиша Escape
                        return;
                        break;
                    default:
                        break;
                }
            }
        }

        window.clear();

        draw();

        window.display();
    }
}

const std::string Chess::GetName() {
    return "Chess";
}

void Chess::draw() {
    DrawBoard();
    DrawFigures();
}
}  // namespace chess
