#include "States.h"

#ifndef STATEIDLE2_H
#define STATEIDLE2_H

class StateIdle2 : public States{

public:
  StateIdle2(GameScreen& gameScreen, KeyHandler& kh);
  ~StateIdle2();
  void close();
};

#endif