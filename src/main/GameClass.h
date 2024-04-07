#include "GameScreen.h"
#include "KeyHandler.h"
#include "MenuHandler.h"
#include "../background/background.h"
#include "../entity/player.h"
#include "../enemies/Slime.h"
#include "../enemies/Plant.h"
#include "../enemies/Fly.h"
#include "../timer.h"
#include <sstream>

#ifndef GAMECLASS_H
#define GAMECLASS_H

class GameClass{

public:

    //Main screen functions
  GameScreen gameScreen;
	//Event handler
  KeyHandler keyHandler;
  KeyHandler *kh;

  MenuHandler *menuHandler;
  Background *background;
  Player *player;
  std::unordered_set<Entity*> enemies;

  //gameGoing
  bool gameStarted;
  bool gameOver;
  bool drawHitboxes;

  int pointsToWin;


  GameClass();
  ~GameClass();
  void updateGame(bool &quit);
  void drawGame();
  void resetGame();
  void stopGame(bool &quit);
  void close();
};

#endif