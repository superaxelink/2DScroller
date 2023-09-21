#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>

#ifndef UTILS_H
#define UTILS_H
class Utils{

public:
  //Loads individual image
  SDL_Texture* loadTexture( std::string path, SDL_Renderer* gRenderer , int &width, int &height);
  void render(int x, int y, int width, int height, SDL_Renderer* renderer, SDL_Texture* texture);
};

#endif