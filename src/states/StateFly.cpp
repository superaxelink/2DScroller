#include "StateFly.h"
#include "../entity/entity.h"
#include <algorithm>

StateFly::StateFly(GameScreen& gameScreen, 
  KeyHandler* kh, 
  Entity& entity,
  int spriteThreshold, int totalSprites, int baseWidth, int baseHeight,
  int height, int yStartSubimage, int widthOffset, int widthHitBox,
  int offsetHitBoxRight, int offsetHitBoxLeft, int stateNumber, int speed,
  int desiredBaseWidth, int desiredBaseHeight, int desiredHeight,
  std::string type, std::string pathRight, std::string pathLeft) 
  : States(gameScreen, kh, entity,   
    spriteThreshold, totalSprites, baseWidth, baseHeight,
    height, yStartSubimage, widthOffset, widthHitBox,
    offsetHitBoxRight, offsetHitBoxLeft, stateNumber, speed,
    type, pathRight, pathLeft), desiredBaseWidth(desiredBaseWidth), 
    desiredBaseHeight(desiredBaseHeight), desiredHeight(desiredHeight){
  initializeVariables(pathRight, pathLeft);
}

void StateFly::inputHandler(){}

void StateFly::initializeVariables(std::string pathRight, std::string pathLeft){
  //States::initializeVariables(pathRight, pathLeft);
  knockBackvx = 0;
  spriteCounter = 0;
  stateCounter = 0;
  frameCounter = 0;
  path = std::filesystem::current_path().string();

  spriteSheet = gameScreen.utils->loadTexture(path + pathRight + ".png", 
    gameScreen.gRenderer, baseWidth, baseHeight, 
    true, desiredBaseWidth, desiredBaseHeight);
  spriteSheetLeft = gameScreen.utils->loadTexture(path + pathLeft + ".png", 
    gameScreen.gRenderer, baseWidth, baseHeight,
    true, desiredBaseWidth, desiredBaseHeight);

  baseWidth=desiredBaseWidth;
  baseHeight = desiredBaseHeight;
  height = desiredHeight;
  dividedWidth = baseWidth/totalSprites;
  width = dividedWidth;
  currentSpriteSheet = spriteSheet;

  sprite = new SDL_Rect();

  sprite->x = width*frameCounter;
  sprite->y = yStartSubimage;
  sprite->w = width;
  sprite->h = height;

}

void StateFly::spriteUpdate(){
  std::string direction = entity.direction;
  int maxSprites = totalSprites-1;
  frameCounter++;
  if(frameCounter>maxSprites){
    frameCounter=0;
  }
}

void StateFly::close(){
  States::close();
}

StateFly::~StateFly(){}