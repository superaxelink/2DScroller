#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <filesystem>
#include "../utils.h"

#ifndef GAMESCREEN_H
#define GAMESCREEN_H

class Utils;

class GameScreen{
public:

  //window to which we'll be rendering
  SDL_Window* window;

  //The window renderer
  SDL_Renderer* gRenderer;

  //font
  TTF_Font* font;

  Utils* utils;

  //constructor
  GameScreen();

  //Destructor 
  ~GameScreen();

  //Screen dimension
  const int SCREEN_WIDTH;
  const int SCREEN_HEIGHT;

  //bool init(SDL_Window* &window, SDL_Surface* &screenSurface);
  bool init();

  //void close(SDL_Window* &window);
  void close();
};

#endif