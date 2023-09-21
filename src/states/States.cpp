#include "States.h"

States::States(GameScreen& gameScreen, KeyHandler& kh) : gameScreen(gameScreen), kh(kh){
  frame = 0;
}
States::~States(){}
void States::changeState(){}
void States::changeDirection(){}
void States::inputHandler(){}
void States::update(){}