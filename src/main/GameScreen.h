#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#ifndef GAMESCREEN_H
#define GAMESCREEN_H

class GameScreen{
public:

  //window to which we'll be rendering
  SDL_Window* window;

  //The window renderer
  SDL_Renderer* gRenderer;

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