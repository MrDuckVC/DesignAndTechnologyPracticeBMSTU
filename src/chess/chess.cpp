#include "chess.h"

#include <cmath>

namespace {}

namespace chess {
void Chess::DrawBoard() {
    // Find selected Figure if exist
    int selectedFigureN = -1;
    int selectedFigureM = -1;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (!desk[i][j].IsEmpty() && desk[i][j].GetFigure().IsSelected()) {
                selectedFigureN = i;
                selectedFigureM = j;
            }
        }
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (i == selectedFigureN && j == selectedFigureM) {
                desk[i][j].GetCellShape().setFillColor(SELECTED_FIGURE_CELL_COLOR);
                if (desk[i][j].GetFigure().GetFigureColor() != whoseTurn) {
                    desk[i][j].GetCellShape().setFillColor(CANT_MOVE_FIGURE_CELL_COLOR);
                }
            } else if (CanMoveTo(selectedFigureN, selectedFigureM, i, j) && CanAttack(selectedFigureN, selectedFigureM, i, j) &&
                       desk[i][j].GetFigure().GetFigureColor() != whoseTurn && !desk[i][j].IsEmpty()) {
                desk[i][j].GetCellShape().setFillColor(CAN_ATTACK_CELL_COLOR);
            } else if (CanMoveTo(selectedFigureN, selectedFigureM, i, j)) {
                desk[i][j].GetCellShape().setFillColor(CAN_MOVE_TO_CELL_COLOR);
            } else {
                desk[i][j].FillCellColor();
            }
            window.draw(desk[i][j].GetCellShape());
        }
    }
}

void Chess::DrawFigures() {
    if (isPromotionPendingOfPawn) {
        sf::Vector2f pawnCellCenter = desk[promotionPosition.first][promotionPosition.second].GetCellShape().getGlobalBounds().getCenter();
        float deltaX = static_cast<float>(WINDOW_SIZE) / (BOARD_SIZE * 4);
        float deltaY = static_cast<float>(WINDOW_SIZE) / (BOARD_SIZE * 4);

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                sf::Sprite figureSprite = Figure(possibleFiguresToChoose[i * 2 + j], whoseTurn).GetFigureSprite();
                figureSprite.setOrigin(figureSprite.getGlobalBounds().getCenter());
                figureSprite.setPosition({pawnCellCenter.x + deltaY * static_cast<float>(std::pow(-1, i)),
                                          pawnCellCenter.y + deltaX * static_cast<float>(std::pow(-1, j))});
                figureSprite.setScale({FIGURE_SCALE / 2, FIGURE_SCALE / 2});
                window.draw(figureSprite);
            }
        }
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (!desk[i][j].IsEmpty()) {
                if (isPromotionPendingOfPawn && i == promotionPosition.first && j == promotionPosition.second) {
                    continue;  // Don't draw the pawn that is being promoted
                }
                Figure fig = desk[i][j].GetFigure();
                sf::Sprite sprite = fig.GetFigureSprite();
                sprite.setOrigin(sprite.getGlobalBounds().getCenter());
                if (fig.IsSelected()) {
                    sprite.setPosition({static_cast<float>(sf::Mouse::getPosition(window).x), static_cast<float>(sf::Mouse::getPosition(window).y)});
                } else {
                    sprite.setPosition(desk[i][j].GetCellShape().getGlobalBounds().getCenter());
                }
                sprite.setScale({FIGURE_SCALE, FIGURE_SCALE});
                window.draw(sprite);
            }
        }
    }
}
void Chess::DrawEndGame() {
    sf::Font font;
    if (!font.openFromFile("assets/menu/RuneScape-ENA.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    sf::Text text(font, "Checkmate!", 50);
    text.setFillColor(sf::Color::Red);
    text.setOrigin(text.getGlobalBounds().getCenter());
    text.setPosition({static_cast<float>(WINDOW_SIZE) / 2, static_cast<float>(WINDOW_SIZE) / 2});

    sf::RectangleShape background({text.getGlobalBounds().size.x + 20, text.getGlobalBounds().size.y + 20});
    background.setFillColor(sf::Color(0, 0, 0, 200));
    background.setOrigin(background.getGlobalBounds().getCenter());
    background.setPosition({static_cast<float>(WINDOW_SIZE) / 2, static_cast<float>(WINDOW_SIZE) / 2});

    window.draw(background);
    window.draw(text);
}
void Chess::Draw() {
    DrawBoard();
    DrawFigures();
}

bool Chess::IsSquareUnderAttack(int x, int y, Color defendingColor, Cell board[BOARD_SIZE][BOARD_SIZE]) {
    // Если board не указан, используем текущую доску (desk)
    Cell(*checkBoard)[BOARD_SIZE] = (board == nullptr) ? desk : board;

    // Проверяем все фигуры противника, атакуют ли они данную клетку
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (!checkBoard[i][j].IsEmpty() && checkBoard[i][j].GetFigure().GetFigureColor() != defendingColor) {
                if (CanAttack(i, j, x, y, board)) {
                    return true;
                }
            }
        }
    }
    return false;
}
bool Chess::CanAttack(int attackerX, int attackerY, int targetX, int targetY, Cell board[BOARD_SIZE][BOARD_SIZE]) {
    // Если board не указан, используем текущую доску (desk)
    Cell(*checkBoard)[BOARD_SIZE] = (board == nullptr) ? desk : board;

    Cell& attackerCell = checkBoard[attackerX][attackerY];
    if (attackerCell.IsEmpty()) {
        return false;
    }

    Figure& attacker = attackerCell.GetFigure();
    int dx = abs(targetX - attackerX);
    int dy = abs(targetY - attackerY);

    switch (attacker.GetFigureType()) {
        case FigureType::PAWN: {
            int direction = attacker.GetFigureColor() == Color::WHITE ? 1 : -1;
            return (dx == 1 && (targetY - attackerY) == direction);
        }
        case FigureType::KNIGHT:
            return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
        case FigureType::BISHOP:
            if (dx != dy)
                return false;
            return IsPathClear(attackerX, attackerY, targetX, targetY, board);
        case FigureType::ROOK:
            if (dx != 0 && dy != 0)
                return false;
            return IsPathClear(attackerX, attackerY, targetX, targetY, board);
        case FigureType::QUEEN:
            if (dx != dy && dx != 0 && dy != 0)
                return false;
            return IsPathClear(attackerX, attackerY, targetX, targetY, board);
        case FigureType::KING:
            return dx <= 1 && dy <= 1;
        default:
            return false;
    }
}
bool Chess::IsPathClear(int fromX, int fromY, int toX, int toY, Cell board[BOARD_SIZE][BOARD_SIZE]) {
    // Если board не указан, используем текущую доску (desk)
    Cell(*checkBoard)[BOARD_SIZE] = (board == nullptr) ? desk : board;

    int stepX = (toX > fromX) ? 1 : (toX < fromX) ? -1 : 0;
    int stepY = (toY > fromY) ? 1 : (toY < fromY) ? -1 : 0;

    int x = fromX + stepX;
    int y = fromY + stepY;

    while (x != toX || y != toY) {
        if (!checkBoard[x][y].IsEmpty()) {
            return false;
        }
        x += stepX;
        y += stepY;
    }
    return true;
}
bool Chess::IsInCheck(Color color) {
    // Находим позицию короля
    int kingX = -1, kingY = -1;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (!desk[i][j].IsEmpty() && desk[i][j].GetFigure().GetFigureType() == FigureType::KING &&
                desk[i][j].GetFigure().GetFigureColor() == color) {
                kingX = i;
                kingY = j;
                break;
            }
        }
        if (kingX != -1)
            break;
    }

    if (kingX == -1)
        return false;  // Король не найден (невозможная ситуация в нормальной игре)

    return IsSquareUnderAttack(kingX, kingY, color);
}
bool Chess::CanMoveTo(int oldN, int oldM, int newN, int newM) {
    // Check if coordinates are valid
    if (oldN < 0 || oldN >= BOARD_SIZE || oldM < 0 || oldM >= BOARD_SIZE || newN < 0 || newN >= BOARD_SIZE || newM < 0 || newM >= BOARD_SIZE) {
        return false;
    }

    if (isPromotionPendingOfPawn) {
        return false;
    }

    Cell& oldCell = desk[oldN][oldM];
    Cell& newCell = desk[newN][newM];

    // Check if there's a piece to move
    if (oldCell.IsEmpty()) {
        return false;
    }

    Figure& figureToMove = oldCell.GetFigure();

    // Check if it's the player's turn
    if (figureToMove.GetFigureColor() != whoseTurn) {
        return false;
    }

    // Check if destination has piece of same color
    if (!newCell.IsEmpty() && newCell.GetFigure().GetFigureColor() == figureToMove.GetFigureColor()) {
        return false;
    }

    int direction = figureToMove.GetFigureColor() == Color::WHITE ? 1 : -1;
    bool isValidMove = false;

    switch (figureToMove.GetFigureType()) {
        case FigureType::PAWN: {
            // Basic pawn movement
            if (newCell.IsEmpty()) {
                // Single move forward
                if (oldN == newN && oldM + direction == newM) {
                    isValidMove = true;
                }
                // Double move from starting position
                else if (oldN == newN && oldM + 2 * direction == newM && figureToMove.GetMovesCount() == 0 &&
                         desk[oldN][oldM + direction].IsEmpty()) {
                    isValidMove = true;
                }
            }
            // Capture
            else {
                if ((oldN + 1 == newN || oldN - 1 == newN) && oldM + direction == newM) {
                    isValidMove = true;
                }
            }
            // TODO: Implement en passant
            // TODO: Implement promotion
            break;
        }

        case FigureType::KNIGHT: {
            int dx = abs(newN - oldN);
            int dy = abs(newM - oldM);
            isValidMove = (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
            break;
        }

        case FigureType::BISHOP: {
            if (abs(newN - oldN) == abs(newM - oldM)) {
                isValidMove = true;
                // Check if path is clear
                int stepX = (newN > oldN) ? 1 : -1;
                int stepY = (newM > oldM) ? 1 : -1;
                for (int x = oldN + stepX, y = oldM + stepY; x != newN && y != newM; x += stepX, y += stepY) {
                    if (!desk[x][y].IsEmpty()) {
                        isValidMove = false;
                        break;
                    }
                }
            }
            break;
        }

        case FigureType::ROOK: {
            if ((newN == oldN && newM != oldM) || (newM == oldM && newN != oldN)) {
                isValidMove = true;
                // Check if path is clear
                if (newN == oldN) {
                    int step = (newM > oldM) ? 1 : -1;
                    for (int y = oldM + step; y != newM; y += step) {
                        if (!desk[oldN][y].IsEmpty()) {
                            isValidMove = false;
                            break;
                        }
                    }
                } else {
                    int step = (newN > oldN) ? 1 : -1;
                    for (int x = oldN + step; x != newN; x += step) {
                        if (!desk[x][oldM].IsEmpty()) {
                            isValidMove = false;
                            break;
                        }
                    }
                }
            }
            break;
        }

        case FigureType::QUEEN: {
            // Like bishop or rook
            if (abs(newN - oldN) == abs(newM - oldM)) {
                // Bishop move
                isValidMove = true;
                int stepX = (newN > oldN) ? 1 : -1;
                int stepY = (newM > oldM) ? 1 : -1;
                for (int x = oldN + stepX, y = oldM + stepY; x != newN && y != newM; x += stepX, y += stepY) {
                    if (!desk[x][y].IsEmpty()) {
                        isValidMove = false;
                        break;
                    }
                }
            } else if ((newN == oldN && newM != oldM) || (newM == oldM && newN != oldN)) {
                // Rook move
                isValidMove = true;
                if (newN == oldN) {
                    int step = (newM > oldM) ? 1 : -1;
                    for (int y = oldM + step; y != newM; y += step) {
                        if (!desk[oldN][y].IsEmpty()) {
                            isValidMove = false;
                            break;
                        }
                    }
                } else {
                    int step = (newN > oldN) ? 1 : -1;
                    for (int x = oldN + step; x != newN; x += step) {
                        if (!desk[x][oldM].IsEmpty()) {
                            isValidMove = false;
                            break;
                        }
                    }
                }
            }
            break;
        }

        case FigureType::KING: {
            // Regular king move
            if (abs(newN - oldN) <= 1 && abs(newM - oldM) <= 1) {
                isValidMove = true;
            } else if (abs(newN - oldN) == 2 && newM == oldM && figureToMove.GetMovesCount() == 0 && !IsInCheck(figureToMove.GetFigureColor())) {
                // Определяем тип рокировки
                bool isKingside = (newN > oldN);  // короткая (королевский фланг)
                int rookCol = isKingside ? 7 : 0;

                // Проверяем, что ладья на месте и не двигалась
                Cell& rookCell = desk[rookCol][oldM];
                if (rookCell.IsEmpty() || rookCell.GetFigure().GetFigureType() != FigureType::ROOK || rookCell.GetFigure().GetMovesCount() != 0) {
                    return false;
                }

                // Проверяем, что клетки между королем и ладьей пусты
                int start = isKingside ? oldN + 1 : newN + 1;
                int end = isKingside ? rookCol - 1 : oldN - 1;
                for (int i = start; i <= end; i++) {
                    if (!desk[i][oldM].IsEmpty()) {
                        return false;
                    }
                }

                return true;
            }

            break;
        }

        default:
            return false;
    }

    if (!isValidMove) {
        return false;
    }

    // Для обычных ходов проверяем, не окажется ли король под шахом
    // Создаем временную копию доски для проверки
    Cell tempDesk[BOARD_SIZE][BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            tempDesk[i][j] = desk[i][j];
        }
    }

    // Делаем "виртуальный" ход
    tempDesk[newN][newM].SetFigure(tempDesk[oldN][oldM].GetFigure());
    tempDesk[oldN][oldM].MakeEmpty();

    // Проверяем, остался ли король под шахом
    int kingX = -1, kingY = -1;
    Color movingColor = figureToMove.GetFigureColor();

    // Находим нового короля (он мог быть перемещен)
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (!tempDesk[i][j].IsEmpty() && tempDesk[i][j].GetFigure().GetFigureType() == FigureType::KING &&
                tempDesk[i][j].GetFigure().GetFigureColor() == movingColor) {
                kingX = i;
                kingY = j;
                break;
            }
        }
    }

    if (kingX == -1) {
        throw std::invalid_argument("There is no king.");
    }

    // Проверяем, атакована ли клетка с королем
    if (IsSquareUnderAttack(kingX, kingY, movingColor, tempDesk)) {
        return false;
    }

    return true;
}
void Chess::PromotePawn(FigureType newType) {
    if (!isPromotionPendingOfPawn)
        return;

    auto [x, y] = promotionPosition;
    Color color = desk[x][y].GetFigure().GetFigureColor();
    desk[x][y].SetFigure(Figure(newType, color));

    isPromotionPendingOfPawn = false;
    // Switch turn after promotion
    whoseTurn = (whoseTurn == Color::WHITE) ? Color::BLACK : Color::WHITE;
}
void Chess::Move(int oldN, int oldM, int newN, int newM) {
    if (!CanMoveTo(oldN, oldM, newN, newM)) {
        return;
    }

    Figure& figureToMove = desk[oldN][oldM].GetFigure();

    if (figureToMove.GetFigureType() == FigureType::PAWN && (newM == 0 || newM == BOARD_SIZE - 1)) {
        isPromotionPendingOfPawn = true;
        promotionPosition = {newN, newM};
        desk[newN][newM].SetFigure(figureToMove);
        desk[oldN][oldM].MakeEmpty();
        desk[newN][newM].GetFigure().CountOneMove();
        return;
    }

    // Проверка на рокировку
    if (figureToMove.GetFigureType() == FigureType::KING && abs(newN - oldN) == 2) {
        // Определяем тип рокировки
        bool isKingside = (newN > oldN);
        int rookOldCol = isKingside ? 7 : 0;
        int rookNewCol = isKingside ? newN - 1 : newN + 1;

        // Перемещаем короля
        desk[newN][newM].SetFigure(figureToMove);
        desk[oldN][oldM].MakeEmpty();
        desk[newN][newM].GetFigure().CountOneMove();

        // Перемещаем ладью
        Figure& rook = desk[rookOldCol][oldM].GetFigure();
        desk[rookNewCol][newM].SetFigure(rook);
        desk[rookOldCol][oldM].MakeEmpty();
        desk[rookNewCol][newM].GetFigure().CountOneMove();
    } else {
        // Обычный ход
        desk[newN][newM].SetFigure(figureToMove);
        desk[oldN][oldM].MakeEmpty();
        desk[newN][newM].GetFigure().CountOneMove();
    }

    // Switch turn
    whoseTurn = (whoseTurn == Color::WHITE) ? Color::BLACK : Color::WHITE;
}

bool Chess::isGameOver() {
    // Don't check for game over during promotion
    if (isPromotionPendingOfPawn) {
        return false;
    }

    if (IsInCheck(whoseTurn)) {
        // Check if king can move
        int kingX = -1, kingY = -1;
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (!desk[i][j].IsEmpty() && desk[i][j].GetFigure().GetFigureType() == FigureType::KING &&
                    desk[i][j].GetFigure().GetFigureColor() == whoseTurn) {
                    kingX = i;
                    kingY = j;
                    break;
                }
            }
        }
        if (kingX == -1) {
            throw std::invalid_argument("There is no king.");
        }

        // Check if king can move to any adjacent square
        for (int i = kingX - 1; i <= kingX + 1; i++) {
            for (int j = kingY - 1; j <= kingY + 1; j++) {
                if (i < 0 || i >= BOARD_SIZE || j < 0 || j >= BOARD_SIZE || (i == kingX && j == kingY)) {
                    continue;
                }
                if (CanMoveTo(kingX, kingY, i, j)) {
                    return false;  // King can escape
                }
            }
        }

        // Check if any piece can block the check or capture the attacker
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (!desk[i][j].IsEmpty() && desk[i][j].GetFigure().GetFigureColor() == whoseTurn) {
                    // Try all possible moves for this piece
                    for (int x = 0; x < BOARD_SIZE; x++) {
                        for (int y = 0; y < BOARD_SIZE; y++) {
                            if (CanMoveTo(i, j, x, y)) {
                                // Make a temporary move
                                Cell tempDesk[BOARD_SIZE][BOARD_SIZE];
                                for (int a = 0; a < BOARD_SIZE; a++) {
                                    for (int b = 0; b < BOARD_SIZE; b++) {
                                        tempDesk[a][b] = desk[a][b];
                                    }
                                }

                                tempDesk[x][y].SetFigure(tempDesk[i][j].GetFigure());
                                tempDesk[i][j].MakeEmpty();

                                // Check if king is still in check
                                int tempKingX = (x == kingX && y == kingY) ? x : kingX;
                                int tempKingY = (x == kingX && y == kingY) ? y : kingY;

                                if (!IsSquareUnderAttack(tempKingX, tempKingY, whoseTurn, tempDesk)) {
                                    return false;  // Found a move that gets king out of check
                                }
                            }
                        }
                    }
                }
            }
        }

        // If we get here, no moves can save the king - checkmate
        return true;
    }

    // Check for stalemate (no legal moves but not in check)
    bool hasLegalMoves = false;
    for (int i = 0; i < BOARD_SIZE && !hasLegalMoves; i++) {
        for (int j = 0; j < BOARD_SIZE && !hasLegalMoves; j++) {
            if (!desk[i][j].IsEmpty() && desk[i][j].GetFigure().GetFigureColor() == whoseTurn) {
                for (int x = 0; x < BOARD_SIZE && !hasLegalMoves; x++) {
                    for (int y = 0; y < BOARD_SIZE && !hasLegalMoves; y++) {
                        if (CanMoveTo(i, j, x, y)) {
                            hasLegalMoves = true;
                        }
                    }
                }
            }
        }
    }

    return !hasLegalMoves;  // Game over if no legal moves (stalemate)
}

Chess::Chess(sf::RenderWindow& window) : Game(window), whoseTurn(Color::WHITE) {
    // Растановка клеток.
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            desk[i][j].GetCellShape().setPosition(
                {static_cast<float>(i * (WINDOW_SIZE / BOARD_SIZE)), static_cast<float>(j * (WINDOW_SIZE / BOARD_SIZE))});
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
                if (isPromotionPendingOfPawn) {
                    sf::Vector2f pawnCellCenter =
                        desk[promotionPosition.first][promotionPosition.second].GetCellShape().getGlobalBounds().getCenter();
                    float deltaX = static_cast<float>(WINDOW_SIZE) / (BOARD_SIZE * 4);
                    float deltaY = static_cast<float>(WINDOW_SIZE) / (BOARD_SIZE * 4);

                    if (desk[promotionPosition.first][promotionPosition.second].GetCellShape().getGlobalBounds().contains(mousePos)) {
                        if (mousePos.x < pawnCellCenter.x) {
                            if (mousePos.y < pawnCellCenter.y) {
                                desk[promotionPosition.first][promotionPosition.second].SetFigure(Figure(FigureType::ROOK, whoseTurn));
                            } else {
                                desk[promotionPosition.first][promotionPosition.second].SetFigure(Figure(FigureType::KNIGHT, whoseTurn));
                            }
                        } else {
                            if (mousePos.y < pawnCellCenter.y) {
                                desk[promotionPosition.first][promotionPosition.second].SetFigure(Figure(FigureType::BISHOP, whoseTurn));
                            } else {
                                desk[promotionPosition.first][promotionPosition.second].SetFigure(Figure(FigureType::QUEEN, whoseTurn));
                            }
                        }
                        isPromotionPendingOfPawn = false;
                        whoseTurn = (whoseTurn == Color::WHITE) ? Color::BLACK : Color::WHITE;
                    }
                }

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
                        if (desk[i][j].GetFigure().IsSelected()) {
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

        Draw();
        if (isGameOver()) {
            DrawEndGame();
        }

        window.display();
    }
}

const std::string Chess::GetName() {
    return "Chess";
}
}  // namespace chess
