#include "StateIdle1.h"
#include <algorithm>

StateIdle1::StateIdle1(GameScreen& gameScreen, KeyHandler& kh) : States(gameScreen, kh){
  //basic characteristics
  spriteThreshold = 4;
  totalSprites = 8;
  //sheetWidth = 1024;
  //sheetHeight=128;
  sheetWidth = 0;
  sheetHeight= 0;
  dividedWidth = sheetWidth/totalSprites;

  height = 73;
  yStartSubimage = 55;

  widthOffset = 0;
  width = dividedWidth;

  spriteSheet = utils.loadTexture("../../res/player/ChibiMale/Swordsman/Idle.png", gameScreen.gRenderer, sheetWidth, sheetHeight);
}

void StateIdle1::inputHandler(){
  if(std::find(kh.keys.begin(), kh.keys.end(), "left")!= kh.keys.end()){
  }
  if(std::find(kh.keys.begin(), kh.keys.end(), "right")!= kh.keys.end()){
  }
}

void StateIdle1::changeState(int newState, std::string direction){

}

void StateIdle1::update(){
  frame++;
  int maxSprites = totalSprites-1;
  if(frame>spriteThreshold){
    
  }
}

void StateIdle1::close(){
  SDL_DestroyTexture(spriteSheet);
  spriteSheet = NULL;
}

StateIdle1::~StateIdle1(){}