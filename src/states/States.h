#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <filesystem>
#include <algorithm>
#include "../main/GameScreen.h"
#include "../main/KeyHandler.h"
#include "../entity/entity.h"

#ifndef STATES_H
#define STATES_H

class States{

public:

  GameScreen& gameScreen;
  Entity& entity;

  KeyHandler* kh;

  //Main image characteristics
  int spriteThreshold;
  int totalSprites; 
  int baseWidth; 
  int baseHeight;

  SDL_Texture* spriteSheet;
  SDL_Texture* spriteSheetLeft;
  SDL_Texture* currentSpriteSheet;

  //SubImage characteristics
  int width;
  int height;
  int dividedWidth;
  int widthOffset;
  int xStartSubimage;
  int yStartSubimage; 
  //State characteristics
  int speed;

/*   SDL_Texture* sprite;   */
  SDL_Rect* sprite;

  int stateNumber;

  //hitbox
  int widthHitBox;
  int offsetHitBoxRight;
  int offsetHitBoxLeft;

  //Attack hitbox
  int xAttackHitboOffset;
  int yAttackHitboOffset;
  int xStartSquare;
  int xEndSquare;
  int yStartSquare;
  int yEndSquare;
  int widthAttack;
  int heightAttack;
  int spriteContact;
  
  //Attack properties
  int knockBackvx;
  int attackDamage;

  //character characteristics
  std::string type;

  //For on air states
  int startingJump;
  int goingUp;
  int maxHeight;
  int falling;
  int landing;

  //counters
  int spriteCounter;
  int stateCounter;
  int frameCounter;

  // Path of the project
  std::string path;

  States(GameScreen& gameScreen, KeyHandler* kh, Entity& entity,
  int spriteThreshold, int totalSprites, int baseWidth, int baseHeight,
  int height, int yStartSubimage, int widthOffset, int widthHitBox,
  int offsetHitBoxRight, int offsetHitBoxLeft, int stateNumber, int speed,
  std::string type, std::string pathRight, std::string pathLeft);
  States(GameScreen& gameScreen, KeyHandler* kh, Entity& entity,
    int spriteThreshold, int totalSprites, int baseWidth, int baseHeight,
    int height, int yStartSubimage, int widthOffset, int widthHitBox,
    int offsetHitBoxRight, int offsetHitBoxLeft, int speed, int widthAttack, 
    int heightAttack, int xAttackHitboOffset, int yAttackHitboOffset, int spriteContact, 
    int stateNumber, int attackDamage, 
    std::string type, std::string pathRight, std::string pathLeft);
  void draw(int x, int y);
  void drawMonsterLife(int x, int y);
  void updateHitboxAttack();
  void endingAttack(std::string direction, int nextAttackState, Entity* entity);
  //NPC movement
  void npcHorizontalMovement();
  ~States();
  virtual void initializeVariables(std::string pathRight, std::string pathLeft);
  virtual void close();
  virtual void inputHandler();
  virtual void update();
  virtual void spriteUpdate();
};

#endif