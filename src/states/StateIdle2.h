#include "States.h"

#ifndef STATEIDLE2_H
#define STATEIDLE2_H

class StateIdle2 : public States{

public:
  StateIdle2(GameScreen& gameScreen, KeyHandler* kh, Entity& entity,
    int spriteThreshold, int totalSprites, int baseWidth, int baseHeight,
    int height, int yStartSubimage, int widthOffset, int widthHitBox,
    int offsetHitBoxRight, int offsetHitBoxLeft, int stateNumber, int speed,
    std::string type, std::string pathRight, std::string pathLeft);
  ~StateIdle2();
  void spriteUpdate() override;
  void inputHandler() override;
  void close() override;
};

#endif