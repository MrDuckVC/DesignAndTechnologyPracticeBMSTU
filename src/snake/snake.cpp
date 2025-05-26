#include "snake.h"

// Получение смещения головы
sf::Vector2f Snake::getNewPosOffset(Orientation::dirNum direction) const {
    sf::Vector2f pos;
    switch (direction) {
        case Orientation::Left: {
            pos.x -= tileLength0;
            break;
        }
        case Orientation::Right: {
            pos.x += tileLength0;
            break;
        }
        case Orientation::Up: {
            pos.y -= tileLength0;
            break;
        }
        case Orientation::Down: {
            pos.y += tileLength0;
            break;
        }
        default: {
            break;
        }
    }
    return pos;
}

// Получение направления по двум точкам
Orientation::dirNum Snake::getDirectionFromPositions(sf::Vector2f pos1, sf::Vector2f pos2) const {
    // Либо dx, либо dy будут равны нулю
    float dx = pos2.x - pos1.x;
    float dy = pos2.y - pos1.y;

    if (std::abs(dx) >= std::abs(dy)) {
        if (dx > 0)
            return Orientation::Right;
        else
            return Orientation::Left;
    } else {
        if (dy > 0)
            return Orientation::Down;
        else
            return Orientation::Up;
    }
}

// Получение угла поворота
int Snake::getCorner(Orientation::dirNum dir1, Orientation::dirNum dir2) const {
    int corner = 0;

    if (dir2 != Orientation::Stop) {
        if (dir1 - 1 == dir2)
            corner += 180;
        else if (dir1 + 1 == dir2)
            corner += 90;
    }

    switch (dir1) {
        case Orientation::Left:
            corner += 270;
            break;
        case Orientation::Right:
            corner += 90;
            break;
        case Orientation::Up:
            corner += 0;
            break;
        case Orientation::Down:
            corner += 180;
            break;
        default:
            break;
    }

    if (corner >= 360)
        return corner - 360;
    else
        return corner;
}

bool Snake::isPosOnSnake(sf::Vector2f pos) const {
    for (Segment* segm : segmentList0)
        if (pos == segm->position())
            return true;
    return false;
}

Snake::Snake(Field* field, sf::Texture* textures) : field0(field), tileLength0(field0->getTileLength()), textures0(textures) {
    timer0 = sf::Clock();

    // Голова
    Segment* bufferSegm = new Segment({tileLength0 * 2, 0}, tileLength0, Segment::Type::Head, Orientation::Right);

    bufferSegm->setTexture(textures0).setRotation(getCorner(Orientation::Right));

    segmentList0.push_back(bufferSegm);
    field0->setBlock(tileLength0 * 2, 0);

    // Тело
    bufferSegm = new Segment({tileLength0, 0}, tileLength0, Segment::Type::Body, Orientation::Right);

    bufferSegm->setTexture(textures0).setRotation(getCorner(Orientation::Right));

    segmentList0.push_back(bufferSegm);
    field0->setBlock(tileLength0, 0);

    // Хвост
    bufferSegm = new Segment({0, 0}, tileLength0, Segment::Type::Tail, Orientation::Right);

    bufferSegm->setTexture(textures0).setRotation(getCorner(Orientation::Right));

    segmentList0.push_back(bufferSegm);
    field0->setBlock(0, 0);
}

Snake::~Snake() {
    for (Segment* pointer : segmentList0)
        delete pointer;
}

void Snake::update(Orientation::dirNum direction, sf::Vector2f foodPos) {
    deltaTime0 += timer0.getElapsedTime().asSeconds();
    timer0.restart();

    isFoodEaten0 = false;

    if (deltaTime0 >= speed0) {
        deltaTime0 = 0;

        // Движение головы
        Segment* head = segmentList0.front();
        if (direction != Orientation::reverse(head->getDirection()) && direction != Orientation::Stop) {
            head->setDirection(direction).setRotation(getCorner(direction));
        }

        Segment* bufferSegm = new Segment(*head);

        sf::Vector2f newPosOffset = getNewPosOffset(head->getDirection());
        sf::Vector2f newPos = head->position() + newPosOffset;

        if (!field0->isPosInField(newPos.x, newPos.y) || isPosOnSnake(newPos)) {
            delete bufferSegm;
            isDead0 = true;
            return;
        }

        head->setPosition(newPos);
        field0->setBlock(newPos.x, newPos.y);

        // Тело после движения головы
        if (newPos == foodPos) {
            isFoodEaten0 = true;
        } else {
            sf::Vector2f pos = bufferSegm->position();
            delete bufferSegm;

            bufferSegm = new Segment(**std::prev(segmentList0.end(), 2));
            bufferSegm->setDirection(head->getDirection());
            bufferSegm->setPosition(pos);
        }

        segmentList0.insert(std::next(segmentList0.begin()), bufferSegm);

        if (head->getDirection() == (*std::next(segmentList0.begin(), 2))->getDirection()) {
            bufferSegm->setRotation(getCorner(head->getDirection())).setType(Segment::Type::Body);

        } else {
            bufferSegm->setRotation(getCorner(head->getDirection(), (*std::next(segmentList0.begin(), 2))->getDirection()))
                .setType(Segment::Type::Turn);
        }

        // Движение хвоста
        if (!isFoodEaten0) {
            bufferSegm = segmentList0.back();
            segmentList0.pop_back();

            sf::Vector2f pos = bufferSegm->position();
            field0->removeBlock(pos.x, pos.y);

            Segment* segmentToDelete = segmentList0.back();
            pos = segmentToDelete->position();
            delete segmentToDelete;

            bufferSegm->setPosition(pos);

            Orientation::dirNum newDirection = getDirectionFromPositions(bufferSegm->position(), (*std::prev(segmentList0.end(), 2))->position());

            bufferSegm->setDirection(newDirection);
            bufferSegm->setRotation(getCorner(bufferSegm->getDirection()));

            segmentList0.back() = bufferSegm;
        }
    }
}

bool Snake::isFoodEaten() const {
    return isFoodEaten0;
}

bool Snake::isDead() const {
    return isDead0;
}

const std::vector<const sf::Drawable*> Snake::getRectsToDraw() const {
    std::vector<const sf::Drawable*> vect;
    for (Segment* segment : segmentList0)
        vect.push_back(segment->getRectToDraw());

    return vect;
}
