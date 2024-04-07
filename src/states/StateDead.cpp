#include "StateDead.h"
#include "../entity/entity.h"
#include <algorithm>

StateDead::StateDead(GameScreen& gameScreen, 
  KeyHandler* kh, 
  Entity& entity,
  int spriteThreshold, int totalSprites, int baseWidth, int baseHeight,
  int height, int yStartSubimage, int widthOffset, int widthHitBox,
  int offsetHitBox, int stateNumber, int speed,
  std::string type, std::string pathRight, std::string pathLeft) 
  : States(gameScreen, kh, entity,   
    spriteThreshold, totalSprites, baseWidth, baseHeight,
    height, yStartSubimage, widthOffset, widthHitBox,
    0, 0, stateNumber, speed,
    type, pathRight, pathLeft){

}

void StateDead::spriteUpdate(){
  int maxSprites = totalSprites-1;
  if(frameCounter<maxSprites){
    frameCounter++;
  }
}

void StateDead::close(){
  States::close();
}

StateDead::~StateDead(){}