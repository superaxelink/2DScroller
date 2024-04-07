#include "States.h"
#include <string>

#ifndef STATEWALK_H
#define STATEWALK_H

class StateWalk : public States{

public:
  StateWalk(GameScreen& gameScreen, KeyHandler* kh, Entity& entity,
    int spriteThreshold, int totalSprites, int baseWidth, int baseHeight,
    int height, int yStartSubimage, int widthOffset, int speed, int widthHitBox,
    int offsetHitBoxRight, int offsetHitBoxLeft, int stateNumber,
    std::string type, std::string pathRight, std::string pathLeft);
  ~StateWalk();
  void spriteUpdate() override;
  void inputHandler() override;
  void close();
};

#endif