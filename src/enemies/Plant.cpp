#include "Plant.h"

Plant::Plant(GameScreen& gameScreen,  
  Background& background, int reference): Entity(gameScreen, background){

  Idle1 = nullptr;
  width = 0;
  height = 0;
  worldX = gameScreen.SCREEN_WIDTH/2;
  worldY = background.groundLine;
  frame = 0;
  jumpHeight = 0;
  weight = 13;

  baseVx = 1;
  baseVy = 18;
  runVx = 2*baseVx;
  vx = baseVx;
  vy = baseVy;
  baseLife = 3;
  currentLife = baseLife;
  damage = 1;
  points = 10;
  initStates("black");

  name = "plant";
  direction = "left";
  type = "enemy";

  invincible = false;
  invincibleTime = 2;
  invincibleCounter = 0;

  currentState = stateList[AvailableStates::Idle_1];
  groundLine =  background.groundLine - currentState->height;

  double rand = gameScreen.utils->random();
  if(rand>0.5){
    x = reference + worldX + currentState->width;
  }else{
    x = reference - worldX - currentState->width;
    direction="right";
  }
  y = groundLine;
  updateHitBox();
}

void Plant::initStates(std::string color){
  stateList[AvailableStates::Idle_1] = new StateIdle1(gameScreen, nullptr, *this, 
    4, 2, 120, 87, 
    87, 0, 0, 50, 
    25, 25, AvailableStates::Idle_1, 0,
    type, "/res/enemy/plant/Plant", "/res/enemy/plant/PlantLeft");

  stateList[AvailableStates::Dead] = new StateDead(gameScreen, nullptr, *this, 
    6, 5, 500, 90, 
    90, 0, 0, 31, 
    14, AvailableStates::Dead, 0,
    type, "/res/enemy/boom", "/res/enemy/boom");
}

void Plant::close(){
  delete currentState;
  currentState = nullptr;
  for (States*& state : stateList) { // Usar referencia a puntero para cambiar el valor en el array
    if (state != nullptr) {
      delete state;
      state = nullptr;
    }
  }
}

Plant::~Plant(){}