#include "States.h"
#include <string>

#ifndef STATEATTACK1_H
#define STATEATTACK1_H

class StateAttack1 : public States{

public:
  StateAttack1(GameScreen& gameScreen, KeyHandler* kh, Entity& entity,
    int spriteThreshold, int totalSprites, int baseWidth, int baseHeight,
    int height, int yStartSubimage, int widthOffset, int widthHitBox,
    int offsetHitBoxRight, int offsetHitBoxLeft, int speed, int widthAttack, 
    int heightAttack, int xAttackHitboOffset, int yAttackHitboOffset, int spriteContact, 
    int stateNumber, int attackDamage, 
    std::string type, std::string pathRight, std::string pathLeft);
  void spriteUpdate() override;
  void inputHandler() override;
  void update() override;
  void close() override;
  ~StateAttack1();
};

#endif