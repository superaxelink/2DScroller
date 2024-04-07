#include "../states/StateIdle1.h"
#include "../states/StateIdle2.h"
#include "../states/StateWalk.h"
#include "../states/StateJump.h"
#include "../states/StateRun.h"
#include "../states/StateAttack1.h"
#include "../states/StateAttack2.h"
#include "../states/StateAttack3.h"
#include "../states/StateHurt.h"
#include "../states/StateDead.h"

#include "entity.h"


#ifndef PLAYER_H
#define PLAYER_H

class Player : public Entity{

public:

  SDL_Texture* Idle1;
  Player(GameScreen& gameScreen, KeyHandler* kh, Background& background);
  ~Player();

  void initStates();
};

#endif