#include "States.h"
#include <string>

#ifndef STATEATTACK2_H
#define STATEATTACK2_H

class StateAttack2 : public States{

public:
  StateAttack2(GameScreen& gameScreen, KeyHandler* kh, Entity& entity,
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
  ~StateAttack2();
};

#endif