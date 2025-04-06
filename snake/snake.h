#pragma once

#include "../games/game.h"

namespace snake {
class Snake : public game::Game {
  public:

  void Run() override;

  const std::string GetName() override;

  const std::string GetDescription() override;

  const std::string GetLogoFile() override;
};
}
