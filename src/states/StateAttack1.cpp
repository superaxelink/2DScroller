#include "StateAttack1.h"
#include "../entity/entity.h"
#include <algorithm>

StateAttack1::StateAttack1(GameScreen& gameScreen, KeyHandler* kh, Entity& entity,
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
  knockBackvx = 3;
}

void StateAttack1::inputHandler(){
  if(kh!=nullptr){
    if(std::find(kh->keys.begin(), kh->keys.end(), "left")!= kh->keys.end() 
      || std::find(kh->keys.begin(), kh->keys.end(), "right")!= kh->keys.end()){
      entity.changeState(entity.AvailableStates::Walk,entity.direction);
    }
  }
}

void StateAttack1::update(){
  updateHitboxAttack();
  spriteUpdate();
}

void StateAttack1::spriteUpdate(){
  std::string direction = entity.direction;
  int maxSprites = totalSprites-1;
  frameCounter++;
  entity.gravity();
  if(frameCounter>maxSprites){
    endingAttack(direction, entity.AvailableStates::Attack_2, &entity);
  }
}

void StateAttack1::close(){
  States::close();
}

StateAttack1::~StateAttack1(){}