#include "States.h"
#include <string>

#ifndef STATEIDLE1_H
#define STATEIDLE1_H

class StateIdle1 : public States{

public:
  StateIdle1(GameScreen& gameScreen, KeyHandler* kh, Entity& entity,
    int spriteThreshold, int totalSprites, int baseWidth, int baseHeight,
    int height, int yStartSubimage, int widthOffset, int widthHitBox,
    int offsetHitBoxRight, int offsetHitBoxLeft, int stateNumber, int speed,
    std::string type, std::string pathRight, std::string pathLeft
  );
  ~StateIdle1();
  void spriteUpdate() override;
  void inputHandler() override;
  void close() override;
};

#endif