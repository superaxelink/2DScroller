#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../utils.h"
#include "../main/GameScreen.h"
#include "../main/KeyHandler.h"

#ifndef STATES_H
#define STATES_H

class States{

public:

  Utils utils;
  GameScreen& gameScreen;
  KeyHandler& kh;

  //Main image characteristics
  int spriteThreshold;
  int totalSprites; 
  int sheetWidth; 
  int sheetHeight;

  SDL_Texture* spriteSheet;
  SDL_Texture* spriteSheetLeft;

  //SubImage characteristics
  int width;
  int height;
  int dividedWidth;
  int widthOffset;
  int xStartSubimage;
  int yStartSubimage; 

  SDL_Texture* sprite;

  //counters
  int spriteCounter;
  int stateCounter;
  int frame;

  States(GameScreen& gameScreen, KeyHandler& kh);
  ~States();
  void changeState();
  void changeDirection();
  void inputHandler();
  void update();
};

#endif