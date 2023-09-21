#include <SDL2/SDL.h>
#include <vector>
#include <string>

#ifndef KEYHANDLER_H
#define KEYHANDLER_H

class KeyHandler{
public:
  SDL_Event e;

  const Uint8* currentKeyStates; //=SDL_GetKeyboardState( NULL );
  //std::vector<std::string> keys;
  std::vector<std::string> keys;

  KeyHandler();
  ~KeyHandler();

  void keyPressed();
  void runEventLoop(bool& quit);

};

#endif