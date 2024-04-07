#include "States.h"
#include <string>

#ifndef STATEJUMP_H
#define STATEJUMP_H

class StateJump : public States{

public:
  StateJump(GameScreen& gameScreen, KeyHandler* kh, Entity& entity,
    int spriteThreshold, int totalSprites, int baseWidth, int baseHeight,
    int height, int yStartSubimage, int widthOffset, int startingJump, 
    int goingUp, int maxHeight, int falling, int landing, int widthHitBox,
    int offsetHitBoxRight, int offsetHitBoxLeft, int stateNumber, int speed,
    std::string type, std::string pathRight, std::string pathLeft);
  ~StateJump();
  void spriteUpdate() override;
  void inputHandler() override;
  void close();
};

#endif