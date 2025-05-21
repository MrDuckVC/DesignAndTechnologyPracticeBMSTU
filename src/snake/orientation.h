#pragma once

#include <SFML/Window/Keyboard.hpp>

class Orientation {
 private:
    Orientation() = delete;

 public:
    enum dirNum {
        Stop,
        Up,
        Right,
        Down,
        Left
    };

    static dirNum fromKeyToDir(sf::Keyboard::Scancode key);

    static Orientation::dirNum reverse(Orientation::dirNum dir);
};

Orientation::dirNum operator-(Orientation::dirNum dir, int num);

Orientation::dirNum operator+(Orientation::dirNum dir, int num);
