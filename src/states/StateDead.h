#include "States.h"
#include <string>

#ifndef STATEDEAD_H
#define STATEDEAD_H

class StateDead : public States{

public:
  StateDead(GameScreen& gameScreen, KeyHandler* kh, Entity& entity,
    int spriteThreshold, int totalSprites, int baseWidth, int baseHeight,
    int height, int yStartSubimage, int widthOffset, int widthHitBox,
    int offsetHitBox, int stateNumber, int speed,
    std::string type, std::string pathRight, std::string pathLeft
  );
  ~StateDead();
  void spriteUpdate() override;
  void close() override;
};

#endif