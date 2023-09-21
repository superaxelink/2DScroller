#include "StateIdle2.h"

StateIdle2::StateIdle2(GameScreen& gameScreen, KeyHandler& kh) : States(gameScreen, kh){
  //basic characteristics
  spriteThreshold = 6;
  totalSprites = 3;
  //sheetWidth = 1024;
  //sheetHeight=128;
  sheetWidth = 0;
  sheetHeight= 0;
  dividedWidth = sheetWidth/totalSprites;

  height = 73;
  yStartSubimage = 55;

  widthOffset = 0;
  width = dividedWidth;

  spriteSheet = utils.loadTexture("../../res/player/ChibiMale/Swordsman/Idle_2.png", gameScreen.gRenderer, sheetWidth, sheetHeight);;
}

void StateIdle2::close(){
  SDL_DestroyTexture(spriteSheet);
  spriteSheet = NULL;
}

StateIdle2::~StateIdle2(){}