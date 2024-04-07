#include "StateWalk.h"
#include "../entity/entity.h"
#include <algorithm> 

StateWalk::StateWalk(GameScreen& gameScreen, 
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

void StateWalk::inputHandler(){
  if(kh!=nullptr){
    if(entity.direction=="right" && std::find(kh->keys.begin(), kh->keys.end(), "right")== kh->keys.end()){
      entity.changeState(entity.AvailableStates::Idle_1, entity.direction);
    }
    else if(entity.direction=="left" && std::find(kh->keys.begin(), kh->keys.end(), "left")== kh->keys.end()){
      entity.changeState(entity.AvailableStates::Idle_1, entity.direction);
    }
    else if(((std::find(kh->keys.begin(), kh->keys.end(), "space")!= kh->keys.end()) 
      && (std::find(kh->keys.begin(), kh->keys.end(), "right")!= kh->keys.end())) 
      || ((std::find(kh->keys.begin(), kh->keys.end(), "space")!= kh->keys.end()) 
      && (std::find(kh->keys.begin(), kh->keys.end(), "left")!= kh->keys.end()))){
      entity.changeState(entity.AvailableStates::Run,entity.direction);
    }
  }else{
    double rand = gameScreen.utils->random();
    if(rand<0.01){
      entity.changeState(entity.AvailableStates::Idle_1, entity.direction);
    }
    else if(0.11<rand && rand<0.12){
      entity.changeState(entity.AvailableStates::Jump, entity.direction);
    }
    else if(0.21<rand && rand<0.22){
      entity.changeState(entity.AvailableStates::Attack_1, entity.direction);
    }
    else if(0.31<rand && rand<0.32){
      entity.changeState(entity.AvailableStates::Attack_2, entity.direction);
    }
    else if(0.41<rand && rand<0.42){
      entity.changeState(entity.AvailableStates::Attack_3, entity.direction);
    }
  }
}

void StateWalk::spriteUpdate(){
  int maxSprites = totalSprites-1;
  frameCounter++;
  if(frameCounter>maxSprites){
    frameCounter=0;
  }
}

void StateWalk::close(){
  States::close();
}

StateWalk::~StateWalk(){}