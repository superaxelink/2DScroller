#include "States.h"
#include <string>

#ifndef STATEHURT_H
#define STATEHURT_H

class StateHurt : public States{

public:
  StateHurt(GameScreen& gameScreen, KeyHandler* kh, Entity& entity,
    int spriteThreshold, int totalSprites, int baseWidth, int baseHeight,
    int height, int yStartSubimage, int widthOffset, int widthHitBox,
    int offsetHitBox, int stateNumber, int speed,
    std::string type, std::string pathRight, std::string pathLeft
  );
  ~StateHurt();
  void spriteUpdate() override;
  void inputHandler() override;
  void close() override;
};

#endif