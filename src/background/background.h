#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <filesystem>
#include "../utils.h"
#include "../main/GameScreen.h"

#ifndef Background_H
#define Background_H

class Player;

class Background{

public:

  GameScreen& gameScreen;
  SDL_Rect *rect;

  SDL_Texture* background1;
  SDL_Texture* background2;
  SDL_Texture* background3;
  SDL_Texture* background4;
  SDL_Texture* background5;

  Utils utils;
  int width;
  int height;
  int groundLine;
  int x;
  int y;

  //Constructor
  Background(GameScreen& gameScreen);
  //Destructor
  ~Background();
  //Loads media
  //void draw(int x, int y, SDL_Renderer* &gRenderer, SDL_Texture* &texture);
  /* void draw(Player player); */
  void update();
  void draw(Player player);
  void reset();
  //bool loadMedia(SDL_Renderer* &gRenderer);
  bool loadMedia();
  void close();
};

#endif