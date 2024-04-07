#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>


#ifndef UTILS_H
#define UTILS_H

class Utils{

public:
  //Loads individual image
  SDL_Texture* loadTexture( std::string path, SDL_Renderer* gRenderer , 
    int &width, int &height, bool rescale = false, int newWidth = 0, int newHeight = 0  
  );
  void render(int x, int y, int w, int h, SDL_Rect* clip, SDL_Renderer* renderer, SDL_Texture* texture);
  void drawText(const std::string& text, SDL_Renderer* const renderer, TTF_Font* const font, int x, int y, bool centered=false);
  bool squareCollision(int o1x1, int o1x2, int o1y1, int o1y2, int o2x1, int o2x2, int o2y1, int o2y2);
  double random();
  static double randomness();
};

#endif