#include "player.h"
#include <algorithm>

Player::Player(GameScreen& gameScreen, KeyHandler& kh) : Entity() , gameScreen(gameScreen), kh(kh){
  Idle1 = NULL;
  width = 0;
  height = 0;
  x = 100;
  y = 100;
  frame = 0;
  vx = 0;
  vy = 0;
  jumpHeight = 0;
  weight = 0;
  direction = "left";

  initStates();

  currentState = stateList[PlayerState::Idle_1];
}

void Player::initStates(){
  stateList[PlayerState::Idle_1] = new StateIdle1(gameScreen,kh);
  stateList[PlayerState::Idle_2] = new StateIdle2(gameScreen,kh);
}

bool Player::loadMedia(){
  //Loading success flag;
  bool success = true;
  //Load splash image
  Idle1 = utils.loadTexture("../../res/player/ChibiMale/Swordsman/Idle.png", gameScreen.gRenderer, sheetWidth, sheetHeight);
	if( Idle1 == NULL ){
	  printf("Failed to load PNG image!\n");
	  success = false;
  }
  return success;
}

void Player::update(){

  if(std::find(kh.keys.begin(), kh.keys.end(), "left")!= kh.keys.end()){
    /* std::cout<<"tacos"<<'\n'; */
    currentState = stateList[PlayerState::Idle_2];
  }
  if(std::find(kh.keys.begin(), kh.keys.end(), "right")!= kh.keys.end()){
    /* std::cout<<"de canasta"<<'\n'; */
    currentState = stateList[PlayerState::Idle_1];
  }
}

void Player::draw(){
	//Set rendering space and render to screen
  utils.render(x, y, currentState->sheetWidth, currentState->sheetHeight, gameScreen.gRenderer, currentState->spriteSheet);
}

void Player::close(){
  delete currentState;
  for (States* state : stateList) {
    if (state != nullptr) {
        delete state;
        state = nullptr;
    }
  }
}

Player::~Player(){}