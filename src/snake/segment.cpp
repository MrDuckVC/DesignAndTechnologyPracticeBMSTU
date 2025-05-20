#include "segment.h"

Segment::Segment(sf::Vector2f pos, float size, Segment::Type type,
                 Orientation::dirNum direction) {
  rect0 = sf::RectangleShape({size, size});

  // Устанавливаем точку опоры в центр квадрата, чтобы его можно было вращать и
  // проще было работать
  centre0 = size / 2;
  rect0.setOrigin({centre0, centre0});
  setPosition(pos);

  type0 = type;
  direction0 = direction;
}

Segment::Segment(const Segment &segment) {
  rect0 = sf::RectangleShape(segment.rect0);
  textureSegmentWidth0 = rect0.getTexture()->getSize().x / 2;
  centre0 = segment.centre0;
  type0 = segment.getType();
  direction0 = segment.getDirection();
}

Segment &Segment::setType(Segment::Type other) {
  type0 = other;
  updateTextureRect();
  return *this;
}

Segment &Segment::setDirection(Orientation::dirNum other) {
  direction0 = other;
  return *this;
};

// Получение координат угла сегмента
sf::Vector2f Segment::position() const {
  return rect0.getPosition() - sf::Vector2f{centre0, centre0};
}

// Привязываем прямоугольник к центру
Segment &Segment::setPosition(const sf::Vector2f &pos) {
  rect0.setPosition(pos + sf::Vector2f{centre0, centre0});
  return *this;
}

// Установить угол наклона
Segment &Segment::setRotation(float degrees0) {
  rect0.setRotation(sf::degrees(degrees0));
  return *this;
}

Segment &Segment::setTexture(sf::Texture *texture) {
  rect0.setTexture(texture);
  textureSegmentWidth0 = texture->getSize().x / 2;
  updateTextureRect();
  return *this;
}

void Segment::updateTextureRect() {
  int &w = textureSegmentWidth0;

  switch (type0) {
  case Segment::Type::Head:
    return rect0.setTextureRect({{0, 0}, {w, w}});
  case Segment::Type::Body:
    return rect0.setTextureRect({{w, 0}, {w, w}});
  case Segment::Type::Tail:
    return rect0.setTextureRect({{w, w}, {w, w}});
  case Segment::Type::Turn:
    return rect0.setTextureRect({{0, w}, {w, w}});
  }
}
