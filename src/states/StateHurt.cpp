#include "StateHurt.h"
#include "../entity/entity.h"
#include <algorithm>

StateHurt::StateHurt(GameScreen& gameScreen, 
  KeyHandler* kh, 
  Entity& entity,
  int spriteThreshold, int totalSprites, int baseWidth, int baseHeight,
  int height, int yStartSubimage, int widthOffset, int widthHitBox,
  int offsetHit, int stateNumber, int speed,
  std::string type, std::string pathRight, std::string pathLeft) 
  : States(gameScreen, kh, entity,   
    spriteThreshold, totalSprites, baseWidth, baseHeight,
    height, yStartSubimage, widthOffset, widthHitBox,
    0, 0, stateNumber, speed,
    type, pathRight, pathLeft){

}

void StateHurt::inputHandler(){}

void StateHurt::spriteUpdate(){
  std::string direction = entity.direction;
  int maxSprites = totalSprites-1;
  frameCounter++;
  entity.gravity();
  if(frameCounter>maxSprites){
    frameCounter=0;
    if(entity.type == "player" && entity.currentLife<=0){
      entity.changeState(entity.AvailableStates::Dead, entity.direction);
    }else{
      entity.changeState(entity.AvailableStates::Idle_1, entity.direction);
    }
  }
}

void StateHurt::close(){
  States::close();
}

StateHurt::~StateHurt(){}