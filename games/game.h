#pragma once

#include <string>

class Game {
public:
    virtual void run() = 0;
    virtual const std::string getName() = 0;
    virtual const std::string getDescription() = 0;
};
