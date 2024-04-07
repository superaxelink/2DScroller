#include "StateJump.h"
#include "../entity/entity.h"
#include <algorithm>

StateJump::StateJump(GameScreen& gameScreen, KeyHandler* kh, Entity& entity,
    int spriteThreshold, int totalSprites, int baseWidth, int baseHeight,
    int height, int yStartSubimage, int widthOffset, int startingJump, 
    int goingUp, int maxHeight, int falling, int landing, int widthHitBox,
    int offsetHitBoxRight, int offsetHitBoxLeft, int stateNumber, int speed,
    std::string type, std::string pathRight, std::string pathLeft) 
    : States(gameScreen, kh, entity,   
    spriteThreshold, totalSprites, baseWidth, baseHeight,
    height, yStartSubimage, widthOffset, widthHitBox,
    offsetHitBoxRight, offsetHitBoxLeft, stateNumber, speed,
    type, pathRight, pathLeft){
  this->startingJump = startingJump;
  this->goingUp = goingUp;
  this->maxHeight = maxHeight;
  this->falling = falling;
  this->landing = landing;
}

void StateJump::inputHandler(){
  if(kh!=nullptr){
    if(std::find(kh->keys.begin(), kh->keys.end(), "attack")!=kh->keys.end()){
      entity.vy = entity.baseVy;
      entity.changeState(entity.AvailableStates::Attack_1,entity.direction, entity.y);
      stateCounter=0;
    }
  }else{
    double rand = gameScreen.utils->random();
    if(rand<0.33 && 0.34<rand){
      entity.x-=speed;
    }
    else if(0.66<rand && 0.67<rand){
      entity.x+=speed;
    }
  }
}

void StateJump::spriteUpdate(){
  int maxSprites = totalSprites-1;
  if(entity.onGround() && frameCounter<goingUp){
    frameCounter++;
  }
  else if(goingUp<=frameCounter && frameCounter<falling){
    entity.y -= entity.vy;
    if(entity.vy -entity.weight>0){
      entity.vy--;
    }else{
      entity.vy=0;
      frameCounter++;
    }
    if(kh!=nullptr && std::find(kh->keys.begin(), kh->keys.end(), "down")!=kh->keys.end() && entity.type=="player"){
      frameCounter++;
      entity.vy = 0;
    }
  }
  else if(frameCounter==falling){
    if(entity.onGround()){
      frameCounter++;
    }
  }
  else if(falling<frameCounter && frameCounter<landing){
    stateCounter++;
    if(stateCounter<spriteThreshold){
      frameCounter++;
      stateCounter = 0;
    }
  }
  else if(landing<=frameCounter && frameCounter<totalSprites-1){
    frameCounter=0;
    entity.vy = entity.baseVy;
    entity.changeState(entity.AvailableStates::Idle_1, entity.direction);
  }
  entity.gravity();
}

void StateJump::close(){
  States::close();
}

StateJump::~StateJump(){}