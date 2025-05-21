#include "foodSpawner.h"

// Получение рандомного числа
int FoodSpawner::getRand(int max) const {
    std::uniform_int_distribution<> d(0, max - 1);
    return d(*gen0);
}

// Конструктор генератора еды
FoodSpawner::FoodSpawner(Field* field, sf::Texture* texture) : field0(field) {
    std::random_device rd;
    gen0 = new std::mt19937(rd());

    foodUnit0.setSize({static_cast<float>(field0->getTileLength()), static_cast<float>(field0->getTileLength())});
    foodUnit0.setTexture(texture);

    respawn();
}

FoodSpawner::~FoodSpawner() {
    delete gen0;
}

// Регенерация еды на новом месте
void FoodSpawner::respawn() {
    // Строчки со свободными клетками
    std::vector<std::vector<bool>> rows = field0->getRowsWithFreeTiles();

    // Получение произвольной строки
    int yPos = getRand(rows.size());
    // Получение координаты произвольной строки в пиксельном виде
    yPos = field0->normalizeVerticalPos(yPos);

    // Получение количества свободных клеток в строке и выбор клетки
    int freeCount = field0->getFreeTilesCount(yPos);
    int xPos = getRand(freeCount);
    xPos = field0->normalizeHorizontalPos(yPos, xPos);

    // Перемещаем еду в новую позицию
    foodUnit0.setPosition({static_cast<float>(xPos), static_cast<float>(yPos)});
}

sf::Vector2f FoodSpawner::getCurrentPos() const {
    return foodUnit0.getPosition();
}

sf::Drawable* FoodSpawner::getRectToDraw() const {
    return (sf::Drawable*)&foodUnit0;
}
