#include "States.h"
#include <string>

#ifndef STATERUN_H
#define STATERUN_H

class StateRun : public States{

public:
  StateRun(GameScreen& gameScreen, KeyHandler* kh, Entity& entity,
    int spriteThreshold, int totalSprites, int baseWidth, int baseHeight,
    int height, int yStartSubimage, int widthOffset, int speed, int widthHitBox,
    int offsetHitBoxRight, int offsetHitBoxLeft, int stateNumber,
    std::string type, std::string pathRight, std::string pathLeft);
  ~StateRun();
  void spriteUpdate() override;
  void inputHandler() override;
  void close();

};

#endif