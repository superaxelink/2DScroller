#include "States.h"
#include <string>

#ifndef STATEFLY_H
#define STATEFLY_H

class StateFly : public States{

public:
  int desiredBaseWidth;
  int desiredBaseHeight; 
  int desiredHeight;

  StateFly(GameScreen& gameScreen, KeyHandler* kh, Entity& entity,
    int spriteThreshold, int totalSprites, int baseWidth, int baseHeight,
    int height, int yStartSubimage, int widthOffset, int widthHitBox,
    int offsetHitBoxRight, int offsetHitBoxLeft, int stateNumber, int speed,
    int desiredBaseWidth, int desiredBaseHeight, int desiredHeight,
    std::string type, std::string pathRight, std::string pathLeft
  );
  ~StateFly();
  void initializeVariables(std::string pathRight, std::string pathLeft) override;
  void spriteUpdate() override;
  void inputHandler() override;
  void close() override;
};

#endif