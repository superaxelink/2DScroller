#include "../states/StateIdle1.h"
#include "../states/StateIdle2.h"
#include "../states/StateWalk.h"
#include "../states/StateRun.h"
#include "../states/StateJump.h"
#include "../states/StateAttack1.h"
#include "../states/StateAttack2.h"
#include "../states/StateAttack3.h"
#include "../states/StateHurt.h"
#include "../states/StateDead.h"

#include "../entity/entity.h"


#ifndef SLIME_H
#define SLIME_H

class Slime : public Entity{

public:

  SDL_Texture* Idle1;
  Slime(GameScreen& gameScreen, Background& background, int reference);
  ~Slime();

  void initStates(std::string color);
  void close();
};

#endif