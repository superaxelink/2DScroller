#include "Slime.h"

Slime::Slime(GameScreen& gameScreen,  
  Background& background, int reference): Entity(gameScreen, background){

  Idle1 = nullptr;
  width = 0;
  height = 0;
  worldX = gameScreen.SCREEN_WIDTH/2;
  worldY = background.groundLine;
  frame = 0;
  jumpHeight = 0;
  weight = 13;
  double rand = gameScreen.utils->random();
  if(rand <0.5){
    baseVx = 5;
    baseVy = 27;
    runVx = baseVx*2;
    
    vx = baseVx;
    vy = baseVy;
    
    baseLife = 3;
    damage = 1;
    points = 10;
    initStates("green");
  }else if(0.5<=rand && rand<0.8){
    baseVx = 6;
    baseVy = 30;
    runVx = baseVx*2;
    baseLife = 6;
    vx = baseVx;
    vy = baseVy;
    damage = 1;
    points = 20;
    initStates("blue");
  }else{
    baseVx = 8;
    runVx = baseVx*2;
    baseVy = 33;
    baseLife = 9;
    vx = baseVx;
    vy = baseVy;
    damage = 2;
    points = 30;
    initStates("red");
  }

  currentLife = baseLife;

  name = "slime";
  direction = "left";
  type = "enemy"; 

  invincible = false;
  invincibleTime = 5;
  invincibleCounter = 0;

  currentState = stateList[AvailableStates::Idle_1];
  groundLine = background.groundLine - currentState->height;

  if(rand>0.5){
    x = reference + worldX + currentState->width;
  }else{
    x = reference - worldX - currentState->width;
    direction ="right";
  }
  y = groundLine;
  updateHitBox();
}

void Slime::initStates(std::string slimeColor){
  stateList[AvailableStates::Idle_1] = new StateIdle1(gameScreen, nullptr, *this, 
    4, 8,1024, 128, 
    33, 95, 0, 42, 
    23, 20, AvailableStates::Idle_1, 0,
    type, "/res/enemy/"+slimeColor+"Slime/Idle", "/res/enemy/"+slimeColor+"Slime/IdleLeft");
  
  stateList[AvailableStates::Walk] = new StateWalk(gameScreen, nullptr, *this, 
    4, 8, 1024, 128, 
    33, 95, 0, 42, 
    23, 18, AvailableStates::Walk, baseVx,
    type, "/res/enemy/"+slimeColor+"Slime/Walk", "/res/enemy/"+slimeColor+"Slime/WalkLeft");
  stateList[AvailableStates::Run] = new StateRun(gameScreen, nullptr, *this, 
    4, 7, 896, 128, 
    33, 95, 0, 42, 
    23, 10, AvailableStates::Run, runVx,
    type, "/res/enemy/"+slimeColor+"Slime/Run", "/res/enemy/"+slimeColor+"Slime/RunLeft");
  stateList[AvailableStates::Jump] = new StateJump(gameScreen, nullptr, *this, 
    5, 13, 1664, 128,
    62, 66, 0,
    2, 4, 7, 8, 11,
    34, 8, 25, AvailableStates::Jump, baseVx,
    type, "/res/enemy/"+slimeColor+"Slime/Jump","/res/enemy/" +slimeColor+"Slime/Jump");
  stateList[AvailableStates::Attack_1] = new StateAttack1(gameScreen, nullptr, *this, 
    6, 4, 512, 128, 
    33, 95, 0, 35, 
    28, 10, 0, 30, 
    30, 0, 0, 3,
    AvailableStates::Attack_1, 1,
    type, "/res/enemy/"+slimeColor+"Slime/Attack_1", "/res/enemy/"+slimeColor+"Slime/AttackLeft_1");
    
  stateList[AvailableStates::Attack_2] = new StateAttack2(gameScreen, nullptr, *this, 
    6, 4, 512, 128, 
    33, 95, 0, 33, 
    24, 8,  0, 30, 
    20, 0, 0, 3, 
    AvailableStates::Attack_2, 2,
    type, "/res/enemy/"+slimeColor+"Slime/Attack_2","/res/enemy/"+slimeColor+"Slime/AttackLeft_2");
    
  stateList[AvailableStates::Attack_3] = new StateAttack3(gameScreen, nullptr, *this, 
    6, 5, 640, 128, 
    33, 95, 0, 35, 
    20, 14, 0, 22, 
    30, 0, 0, 2,
    AvailableStates::Attack_3, 3,
    type, "/res/enemy/"+slimeColor+"Slime/Attack_3","/res/enemy/"+slimeColor+"Slime/AttackLeft_3");
    
  stateList[AvailableStates::Hurt] = new StateHurt(gameScreen, nullptr, *this, 
    6, 6, 768, 128, 
    73, 55, 0, 31, 
    14, AvailableStates::Hurt, 0,
    type, "/res/enemy/"+slimeColor+"Slime/Hurt", "/res/enemy/"+slimeColor+"Slime/HurtLeft");
    
/*   stateList[AvailableStates::Dead] = new StateDead(gameScreen, nullptr, *this, 
    6, 5, 500, 90, 
    90, 0, 0, 31, 
    14, AvailableStates::Dead, 0,
    type, "/res/enemy/"+slimeColor+"Slime/Dead", "/res/enemy/"+slimeColor+"Slime/Dead"); */

  stateList[AvailableStates::Dead] = new StateDead(gameScreen, nullptr, *this, 
    6, 5, 500, 90, 
    90, 0, 0, 31, 
    14, AvailableStates::Dead, 0,
    type, "/res/enemy/boom", "/res/enemy/boom");
}

void Slime::close(){
  delete currentState;
  currentState = nullptr;
  for (States*& state : stateList) { // Usar referencia a puntero para cambiar el valor en el array
    if (state != nullptr) {
      delete state;
      state = nullptr;
    }
  }
}

Slime::~Slime(){}