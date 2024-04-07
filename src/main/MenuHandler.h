#include <string>
#include <vector>
#include <algorithm>
#include "GameScreen.h"
#include "KeyHandler.h"


#ifndef MENUHANDLER_H
#define MENUHANDLER_H

class MenuHandler{
public:

  GameScreen* gameScreen;
  SDL_Rect *rect;
  SDL_Texture* background1;

  int width;
  int height;

  //Font font;
  // Obtiene las dimensiones del texto
  //FontMetrics metrics;

  int textWidth;
  int textHeight;

  int options;
  int menuState;

  int frameCounter;
  int frameThreshold;

  int x;
  int y;

  KeyHandler* kh;

  std::vector<std::string> titles;
  std::vector<std::string> mainMenuOptions;
  std::vector<std::string> subMenuOptions;
  std::vector<std::string> gameOverOptions;

  int totalOptions;

  MenuHandler(GameScreen* gameScreen, KeyHandler* kh);
  ~MenuHandler();
  int update(bool &gameStarted);
  int updateGameOverMenu(bool &gameStarted);
  int updateMainMenu(bool &gameStarted);
  void drawTitle(std::string text, int y);
  void drawOptions(std::string text, int y);
  void drawMenu(std::vector<std::string> menuOptions);
  void draw();
  void drawGameOverMenu();
  void drawWinnerMenu();
};

#endif