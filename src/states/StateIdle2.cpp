#include "StateIdle2.h"
#include "../entity/entity.h"
#include <algorithm>

StateIdle2::StateIdle2(GameScreen& gameScreen, 
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

void StateIdle2::inputHandler(){
  if(kh !=nullptr){
    if(std::find(kh->keys.begin(), kh->keys.end(), "left")!= kh->keys.end()){
      entity.changeState(entity.AvailableStates::Walk,entity.direction);
    }
    else if(std::find(kh->keys.begin(), kh->keys.end(), "right")!= kh->keys.end()){
      entity.changeState(entity.AvailableStates::Walk,entity.direction);
    }
    else if(((std::find(kh->keys.begin(), kh->keys.end(), "space")!= kh->keys.end()) 
        && (std::find(kh->keys.begin(), kh->keys.end(), "right")!= kh->keys.end())) 
        || ((std::find(kh->keys.begin(), kh->keys.end(), "space")!= kh->keys.end()) 
        && (std::find(kh->keys.begin(), kh->keys.end(), "left")!= kh->keys.end()))){
      entity.changeState(entity.AvailableStates::Run,entity.direction);
    }
    else if(std::find(kh->keys.begin(), kh->keys.end(), "up")!= kh->keys.end()){
      entity.changeState(entity.AvailableStates::Jump, entity.direction);
    }
  }
}

void StateIdle2::spriteUpdate(){
  int maxSprites = totalSprites-1;
  if(frameCounter<maxSprites){
    frameCounter++;
  }
}

void StateIdle2::close(){
  States::close();
}

StateIdle2::~StateIdle2(){}