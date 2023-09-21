#include "States.h"
#include <string>

#ifndef STATEIDLE1_H
#define STATEIDLE1_H

class StateIdle1 : public States{

public:
  StateIdle1(GameScreen& gameScreen, KeyHandler& kh);
  ~StateIdle1();
  void changeState(int newState, std::string direction);
  void changeDirection();
  void inputHandler();
  void update();
  void close();
};

#endif