#include "StateAttack2.h"
#include "../entity/entity.h"
#include <algorithm>

StateAttack2::StateAttack2(GameScreen& gameScreen, KeyHandler* kh, Entity& entity,
    int spriteThreshold, int totalSprites, int baseWidth, int baseHeight,
    int height, int yStartSubimage, int widthOffset, int widthHitBox,
    int offsetHitBoxRight, int offsetHitBoxLeft, int speed, int widthAttack, 
    int heightAttack, int xAttackHitboOffset, int yAttackHitboOffset, int spriteContact, 
    int stateNumber, int attackDamage, 
    std::string type, std::string pathRight, std::string pathLeft) 
  : States(gameScreen, kh, entity,
    spriteThreshold, totalSprites, baseWidth, baseHeight,
    height, yStartSubimage, widthOffset, widthHitBox,
    offsetHitBoxRight, offsetHitBoxLeft, speed, widthAttack, 
    heightAttack, xAttackHitboOffset, yAttackHitboOffset, spriteContact, 
    stateNumber, attackDamage, 
    type, pathRight, pathLeft){
  knockBackvx = 4;
}

void StateAttack2::inputHandler(){}

void StateAttack2::update(){
  updateHitboxAttack();
  spriteUpdate();
}

void StateAttack2::spriteUpdate(){
  std::string direction = entity.direction;
  int maxSprites = totalSprites-1;
  frameCounter++;
  entity.gravity();
  if(frameCounter>maxSprites){
    endingAttack(direction, entity.AvailableStates::Attack_3, &entity);
  }
}

void StateAttack2::close(){
  States::close();
}

StateAttack2::~StateAttack2(){}