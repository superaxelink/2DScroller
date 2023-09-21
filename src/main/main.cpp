#include "GameScreen.h"
#include "KeyHandler.h"
#include "../background/background.h"
#include "../entity/player.h"
#include <sstream>

/* Here I've been using surface or software rendering with SDL_SURFACE

SDL_Texture on the other hand, is used in a hardware rendering, textures are stored in VRAM and you 
don't have access to it directly as with SDL_Surface. 
The rendering operations are accelerated by GPU, using, internally, 
either OpenGL or DirectX (available only on Windows) API, which in turn are using your video hardware, 
hence hardware rendering name

Hardware rendering is by orders of magnitude faster than software rendering and should be always be 
considered as primary option.
*/
int main(int argc, char* args[]){

  //Main screen functions
  GameScreen gameScreen;
	//Event handler
  KeyHandler kh;

  if(!gameScreen.init()){
		printf( "Failed to initialize!\n" );
    gameScreen.close();
    return 0;
  }

  //Background background(gameScreen.screenSurface);
  Background background(gameScreen);
  if(!background.loadMedia()){
  	printf( "Failed to load media!\n" );
    background.close();
    return 0;
  }

  Player player(gameScreen,kh);
  if(!player.loadMedia()){
    printf( "Failed to load media!\n" );
    background.close();
    return 0;
  }

  //Current time start time
  Uint32 startTime = 0;

  //In memory text stream
  std::string timeText;
  //Main loop flag
	bool quit = false;
  //while application is running
  startTime = SDL_GetTicks();
  while(!quit){
    std::cout<<SDL_GetTicks()-startTime<<'\n';
  	//Handle events on queue
    kh.runEventLoop(quit);
		//Clear screen
		SDL_RenderClear( gameScreen.gRenderer );
    player.update();
    background.draw();
    player.draw();
    SDL_RenderPresent(gameScreen.gRenderer);
  }

  //Free resources background
  background.close();
  player.close();
  //Free resources and close SDL
  gameScreen.close();

  return 0;
}