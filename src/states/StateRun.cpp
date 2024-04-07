#include "StateRun.h"
#include "../entity/entity.h"
#include <algorithm>

StateRun::StateRun(GameScreen& gameScreen, 
  KeyHandler* kh, 
  Entity& entity,
  int spriteThreshold, int totalSprites, int baseWidth, int baseHeight,
  int height, int yStartSubimage, int widthOffset, int widthHitBox,
  int offsetHitBoxRight, int offsetHitBoxLeft, int stateNumber, int speed,
  std::string type, std::string pathRight, std::string pathLeft) 
  : States(gameScreen, kh, entity,   
    spriteThreshold, totalSprites, baseWidth, baseHeight,
    height, yStartSubimage, widthOffset, widthHitBox,
    offsetHitBoxRight, offsetHitBoxLeft, stateNumber, speed,
    type, pathRight, pathLeft){
}

void StateRun::inputHandler(){
  if(kh!=nullptr){
    if((std::find(kh->keys.begin(), kh->keys.end(), "space")== kh->keys.end()) 
    || (entity.direction=="left" && std::find(kh->keys.begin(), kh->keys.end(), "left")== kh->keys.end())
    || (entity.direction=="right" && std::find(kh->keys.begin(), kh->keys.end(), "right")== kh->keys.end())){
    entity.changeState(entity.AvailableStates::Idle_1, entity.direction);
    }
  }else{
    double rand = gameScreen.utils->random();
    if(rand<0.01){
      entity.changeState(entity.AvailableStates::Walk, entity.direction);
    }
    else if(0.11<rand && rand<0.12){
      entity.changeState(entity.AvailableStates::Idle_1, entity.direction);
    }
    else if(0.21<rand && rand<0.22){
      entity.changeState(entity.AvailableStates::Jump, entity.direction);
    }
    else if(0.31<rand && rand<0.32){
      entity.changeState(entity.AvailableStates::Attack_1, entity.direction);
    }
    else if(0.41<rand && rand<0.42){
      entity.changeState(entity.AvailableStates::Attack_2, entity.direction);
    }
    else if(0.51<rand && rand<0.52){
      entity.changeState(entity.AvailableStates::Attack_3, entity.direction);
    }
  }
}

void StateRun::spriteUpdate(){
  int maxSprites = totalSprites-1;
  frameCounter++;
  if(frameCounter>maxSprites){
    frameCounter=0;
  }
}

void StateRun::close(){
  States::close();
}

StateRun::~StateRun(){}