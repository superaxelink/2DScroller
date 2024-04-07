#include "Fly.h"

Fly::Fly(GameScreen &gameScreen,
  Background &background, int reference) : Entity(gameScreen, background){

  width = 0;
  height = 0;
  worldX = gameScreen.SCREEN_WIDTH/2;
  worldY = (int) std::floor(background.groundLine*(1-gameScreen.utils->random()));
  frame = 0;
  jumpHeight = 0;
  weight = 13;
  direction = "left";
  type = "enemy";
    
  invincible = false;
  invincibleTime = 5;
  invincibleCounter = 0;

  double rand = gameScreen.utils->random();
  if(rand <0.25){
    desiredBaseWidth=360;
    desiredBaseHeight=44; 
    desiredHeight=44;
    baseVx = 4;
    runVx = 2*baseVx;
    baseVy = 18;
    vx = baseVx;
    vy = baseVy;
    baseLife = 3;
    damage = 1;
    points = 20;
    initStates2("black");
  }else if( 0.25<=rand && rand <0.5){
    desiredBaseWidth=120;
    desiredBaseHeight=50; 
    desiredHeight=50;
    baseVx = 4;
    runVx = 2*baseVx;
    baseVy = 18;
    vx = baseVx;
    vy = baseVy;
    baseLife = 3;
    damage = 1;
    points = 30;
    initStates("brown");
  }else if(0.5<=rand && rand<0.8){
    desiredBaseWidth=120;
    desiredBaseHeight=50; 
    desiredHeight=50;
    baseVx = 5;
    runVx = 2*baseVx;
    baseVy = 24;
    vx = baseVx;
    vy = baseVy;
    baseLife = 3;
    damage = 2;
    points = 40;
    initStates("green");
  }else{
    desiredBaseWidth=120;
    desiredBaseHeight=50; 
    desiredHeight=50;
    baseVx = 8;
    runVx = 2*baseVx;
    baseVy = 30;
    vx = baseVx;
    vy = baseVy;
    baseLife = 3;
    damage = 3;
    points = 50;
    initStates("horned");
  }

  currentLife = baseLife;
  currentState = stateList[AvailableStates::Fly];
  groundLine = background.groundLine - currentState->height;

  if(rand>0.5){
    x = reference + worldX + currentState->width;
  }else{
    x = reference - worldX - currentState->width;
    direction="right";
  }
  y = groundLine;
}

void Fly::update(Entity* attacked){
  if(vx!=0){
    knockBack();
  }
  npcHorizontalMovement();
  checkDirection();
  verticalMovement();
  updateHitBox();
  enemyAttackCollision(attacked);
  currentState->inputHandler();
  currentState->update();
  checkEnemyDead();
}

void Fly::verticalMovement(){
  angle += 0.02;
  int rand = (int) (20*gameScreen.utils->random()-10); 
  y += 3*std::sin(angle) + rand;
}

void Fly::initStates(std::string color){
/*   stateList[AvailableStates::Fly] = new StateFly(gameScreen, nullptr, *this, 
    4, 2, 120, 50, 
    50, 0, 0, 45, 
    22, 22, AvailableStates::Fly, 3,
    type, "/res/enemy/" + color + "Fly/spritesheet", "/res/enemy/" + color + "Fly/spritesheetLeft"); */

  stateList[AvailableStates::Fly] = new StateFly(gameScreen, nullptr, *this, 
    4, 2, 1268, 511, 
    511, 0, 0, 45, 
    22, 22, AvailableStates::Fly, 3, 
    desiredBaseWidth, desiredBaseHeight, desiredHeight,
    type, "/res/enemy/" + color + "Fly/spritesheet", "/res/enemy/" + color + "Fly/spritesheetLeft");

  stateList[AvailableStates::Dead] = new StateDead(gameScreen, nullptr, *this, 
    6, 5, 500, 90, 
    90, 0, 0, 31, 
    14, AvailableStates::Dead, 0,
    type, "/res/enemy/boom", "/res/enemy/boom");
}

void Fly::initStates2(std::string color){
  stateList[AvailableStates::Fly] = new StateFly(gameScreen, nullptr, *this, 
    4, 6, 360, 44, 
    44, 0, 0, 45, 
    22, 22, AvailableStates::Fly, 3,
    desiredBaseWidth, desiredBaseHeight, desiredHeight,
    type, "/res/enemy/" + color + "Fly/spritesheet", "/res/enemy/" + color + "Fly/spritesheetLeft");

  stateList[AvailableStates::Dead] = new StateDead(gameScreen, nullptr, *this, 
    6, 5, 500, 90, 
    90, 0, 0, 31, 
    14, AvailableStates::Dead, 0,
    type, "/res/enemy/boom", "/res/enemy/boom");
}

void Fly::close(){
  delete currentState;
  currentState = nullptr;
  for (States*& state : stateList) { // Usar referencia a puntero para cambiar el valor en el array
    if (state != nullptr) {
      delete state;
      state = nullptr;
    }
  }
}

Fly::~Fly(){}