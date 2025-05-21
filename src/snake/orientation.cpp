#include "orientation.h"

#include <cstdlib>

// Получить направление по нажатию
Orientation::dirNum Orientation::fromKeyToDir(sf::Keyboard::Scancode key) {
    switch (key) {
        case sf::Keyboard::Scancode::A:
        case sf::Keyboard::Scancode::Left:
            return Orientation::Left;
        case sf::Keyboard::Scancode::D:
        case sf::Keyboard::Scancode::Right:
            return Orientation::Right;
        case sf::Keyboard::Scancode::W:
        case sf::Keyboard::Scancode::Up:
            return Orientation::Up;
        case sf::Keyboard::Scancode::S:
        case sf::Keyboard::Scancode::Down:
            return Orientation::Down;
        default:
            return Orientation::Stop;
    }
}

// Получить обратное направление
Orientation::dirNum Orientation::reverse(Orientation::dirNum dir) {
    switch (dir) {
        case Orientation::Left:
            return Orientation::Right;
        case Orientation::Right:
            return Orientation::Left;
        case Orientation::Up:
            return Orientation::Down;
        case Orientation::Down:
            return Orientation::Up;
    }
    return Orientation::Stop;
}

Orientation::dirNum operator-(Orientation::dirNum dir, int num) {
    if (dir != 0 && num != 0) {
        if (num < 0)
            return operator+(dir, std::abs(num));
        return (Orientation::dirNum)(5 - (int)operator+((Orientation::dirNum)(5 - (int)dir), num));
    }
    return dir;
}

Orientation::dirNum operator+(Orientation::dirNum dir, int num) {
    if (dir != 0 && num != 0) {
        if (num < 0)
            return operator-(dir, std::abs(num));

        int res = num - num / 4 * 4 + (int)dir;
        if (res > 4)
            return (Orientation::dirNum)(res % 4);
        else
            return (Orientation::dirNum)res;
    }
    return dir;
}
