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
    {{FigureType::PAWN, Color::WHITE},   LoadTexture("assests/chess/pawn.png")   },
    {{FigureType::PAWN, Color::BLACK},   LoadTexture("assests/chess/pawn1.png")  },
    {{FigureType::KNIGHT, Color::WHITE}, LoadTexture("assests/chess/knight.png") },
    {{FigureType::KNIGHT, Color::BLACK}, LoadTexture("assests/chess/knight1.png")},
    {{FigureType::BISHOP, Color::WHITE}, LoadTexture("assests/chess/bishop.png") },
    {{FigureType::BISHOP, Color::BLACK}, LoadTexture("assests/chess/bishop1.png")},
    {{FigureType::ROOK, Color::WHITE},   LoadTexture("assests/chess/rook.png")   },
    {{FigureType::ROOK, Color::BLACK},   LoadTexture("assests/chess/rook1.png")  },
    {{FigureType::QUEEN, Color::WHITE},  LoadTexture("assests/chess/queen.png")  },
    {{FigureType::QUEEN, Color::BLACK},  LoadTexture("assests/chess/queen1.png") },
    {{FigureType::KING, Color::WHITE},   LoadTexture("assests/chess/king.png")   },
    {{FigureType::KING, Color::BLACK},   LoadTexture("assests/chess/king1.png")  },
};

Figure::Figure(FigureType figureType, Color figureColor)
    : figureType(figureType), figureColor(figureColor), figureSprite(Figure::figureTextures[{figureType, figureColor}]), isSelected(false) {
    // figureSprite.setScale({(WINDOW_SIZE / static_cast<float>(Figure::figureTextures[{figureType, figureColor}].getSize().x)) / BOARD_SIZE,
    //                        (WINDOW_SIZE / static_cast<float>(Figure::figureTextures[{figureType, figureColor}].getSize().y)) / BOARD_SIZE});
    // figureSprite.setPosition({140, 20});
}

void Figure::SetIsSelected(bool selected) {
    isSelected = selected;
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
bool Figure::GetIsSelected() {
    return isSelected;
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
Figure& Cell::GetFigure() {
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
            window.draw(desk[i][j].GetCellShape());
        }
    }
}

void Chess::DrawFigures() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (!desk[i][j].IsEmpty()) {
                Figure fig = desk[i][j].GetFigure();
                sf::Sprite sprite = fig.GetFigureSprite();
                sprite.setOrigin(sprite.getGlobalBounds().getCenter());
                if (fig.GetIsSelected()) {
                    sprite.setPosition({static_cast<float>(sf::Mouse::getPosition(window).x), static_cast<float>(sf::Mouse::getPosition(window).y)});
                } else {
                    sprite.setPosition(desk[i][j].GetCellShape().getGlobalBounds().getCenter());
                }
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
        desk[i][1].SetFigure(Figure(FigureType::PAWN, Color::WHITE));
    }
    desk[0][0].SetFigure(Figure(FigureType::ROOK, Color::WHITE));
    desk[1][0].SetFigure(Figure(FigureType::KNIGHT, Color::WHITE));
    desk[2][0].SetFigure(Figure(FigureType::BISHOP, Color::WHITE));
    desk[3][0].SetFigure(Figure(FigureType::QUEEN, Color::WHITE));
    desk[4][0].SetFigure(Figure(FigureType::KING, Color::WHITE));
    desk[5][0].SetFigure(Figure(FigureType::BISHOP, Color::WHITE));
    desk[6][0].SetFigure(Figure(FigureType::KNIGHT, Color::WHITE));
    desk[7][0].SetFigure(Figure(FigureType::ROOK, Color::WHITE));
    // Чёрные фигуры на 7-8 линиях.
    for (int i = 0; i < BOARD_SIZE; i++) {
        desk[i][6].SetFigure(Figure(FigureType::PAWN, Color::BLACK));
    }
    desk[0][7].SetFigure(Figure(FigureType::ROOK, Color::BLACK));
    desk[1][7].SetFigure(Figure(FigureType::KNIGHT, Color::BLACK));
    desk[2][7].SetFigure(Figure(FigureType::BISHOP, Color::BLACK));
    desk[3][7].SetFigure(Figure(FigureType::QUEEN, Color::BLACK));
    desk[4][7].SetFigure(Figure(FigureType::KING, Color::BLACK));
    desk[5][7].SetFigure(Figure(FigureType::BISHOP, Color::BLACK));
    desk[6][7].SetFigure(Figure(FigureType::KNIGHT, Color::BLACK));
    desk[7][7].SetFigure(Figure(FigureType::ROOK, Color::BLACK));
}

void Chess::Run() {
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
            } else if (event->is<sf::Event::MouseButtonPressed>() &&
                       sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {  // Если нажата кнопка мыши
                // Получаем координаты мыши
                sf::Vector2f mousePos = {static_cast<float>(sf::Mouse::getPosition(window).x), static_cast<float>(sf::Mouse::getPosition(window).y)};
                // Проверяем, попадает ли мышь в клетку
                for (int i = 0; i < BOARD_SIZE; i++) {
                    for (int j = 0; j < BOARD_SIZE; j++) {
                        desk[i][j].GetFigure().SetIsSelected(false);
                        if (desk[i][j].GetCellShape().getGlobalBounds().contains(mousePos)) {
                            desk[i][j].GetFigure().SetIsSelected(true);
                        }
                    }
                }
            } else if (event->is<sf::Event::MouseButtonReleased>()) {
                sf::Vector2f mousePos = {static_cast<float>(sf::Mouse::getPosition(window).x), static_cast<float>(sf::Mouse::getPosition(window).y)};
                int oldN = -1;
                int oldM = -1;
                int newN = -1;
                int newM = -1;
                for (int i = 0; i < BOARD_SIZE; i++) {
                    for (int j = 0; j < BOARD_SIZE; j++) {
                        if (desk[i][j].GetFigure().GetIsSelected()) {
                            oldN = i;
                            oldM = j;
                            desk[i][j].GetFigure().SetIsSelected(false);
                        }
                        if (desk[i][j].GetCellShape().getGlobalBounds().contains(mousePos)) {
                            newN = i;
                            newM = j;
                        }
                    }
                }
                Move(oldN, oldM, newN, newM);
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

void Chess::Move(int oldN, int oldM, int newN, int newM) {
    if (!desk[newN][newM].IsEmpty() || desk[oldN][oldM].IsEmpty()) {
        return;
    }
    if (oldN < 0 || oldN >= BOARD_SIZE || oldM < 0 || oldM >= BOARD_SIZE || newN < 0 || newN >= BOARD_SIZE || newM < 0 || newM >= BOARD_SIZE) {
        return;
    }

    desk[newN][newM].SetFigure(desk[oldN][oldM].GetFigure());
    desk[oldN][oldM].MakeEmply();
}

void Chess::draw() {
    DrawBoard();
    DrawFigures();
}
}  // namespace chess
