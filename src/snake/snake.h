#pragma once

#include <list>

#include "field.h"
#include "segment.h"

class Snake {
private:
  sf::Vector2f getNewPosOffset(Orientation::dirNum direction) const;
  Orientation::dirNum getDirectionFromPositions(sf::Vector2f pos1,
                                                sf::Vector2f pos2) const;

  int getCorner(Orientation::dirNum dir1,
                Orientation::dirNum dir2 = Orientation::Stop) const;

  bool isPosOnSnake(sf::Vector2f pos) const;

  std::list<Segment *> segmentList0;

  Field *field0;
  float tileLength0;
  float speed0;

  sf::Texture *textures0;

  sf::Clock timer0;
  float deltaTime0 = 0;

  bool isFoodEaten0{false};
  bool isDead0{false};

public:
  Snake(Field *field, sf::Texture *textures, float speed = 0.2);
  ~Snake();

  void update(Orientation::dirNum direction, sf::Vector2f foodPos);
  bool isFoodEaten() const { return isFoodEaten0; }
  bool isDead() const { return isDead0; }

  const std::vector<const sf::Drawable *> getRectsToDraw() const;
};
