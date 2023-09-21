#include "../main/GameScreen.h"
#include "../main/KeyHandler.h"
#include "../utils.h"
#include "../states/States.h"
#include "../states/StateIdle1.h"
#include "../states/StateIdle2.h"
#include "entity.h"


#ifndef PLAYER_H
#define PLAYER_H

class Player : public Entity{

public:

  GameScreen& gameScreen;
  KeyHandler& kh;
  States* currentState;

  States* stateList[10];

  SDL_Texture* Idle1;
  Utils utils;

  enum PlayerState{
    Attack_1,
    Attack_2,
    Attack_3,
    Dead,
    Hurt,
    Idle_1,
    Idle_2,
    Jump,
    Run,
    Walk
  };

  Player(GameScreen& gameScreen, KeyHandler& kh);
  ~Player();

  bool loadMedia();
  void initStates();
  void draw();
  void update();
  void close();
};

#endif