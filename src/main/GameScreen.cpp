#include "GameScreen.h"

GameScreen::GameScreen() : SCREEN_WIDTH(700), SCREEN_HEIGHT(500){
  //window to which we'll be rendering
  window = NULL;
  //The surface contained by the window
  gRenderer = NULL;
}

//SDL_Window* is a pointer to a window
bool GameScreen::init(){

	//Initialization flag
  bool success = true;

  // Initialize SDL
  //You can't call any SDL functions without initializing SDL first. 
  if(SDL_Init(SDL_INIT_VIDEO)<0){
    //SDL_GetError will let you know if any errors happened inside of any SDL function. 
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    success = false;
    return success;
  }

  //Set texture filtering to linear
	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ){
		printf( "Warning: Linear texture filtering not enabled!" );
	}
    
  //Create window
  //window's caption, x and y position the window is created in, window's width and height,
  //last argument are the creation flags. SDL_WINDOW_SHOWN makes sure the window is shown 
  //when it is created.
	window = SDL_CreateWindow( "Game Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
  if(window == NULL){
    printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    success = false;
    return success;
  }

	//Create renderer for window
	gRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
	if( gRenderer == NULL ){
	  printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
		success = false;
    return success;
	}

	//Initialize renderer color
	//SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF ); //white
	SDL_SetRenderDrawColor( gRenderer, 0x0, 0x0, 0x0, 0x0 ); //black
 
	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
  if( !( IMG_Init( imgFlags ) & imgFlags ) ){
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		success = false;
    return success;
	}

  return success;
}



void GameScreen::close(){

  //Destroy window
  //Destroy screenSurface
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(gRenderer);
  window = NULL;
  gRenderer = NULL;

  //Quit sdl subsystems
  IMG_Quit();
  SDL_Quit();
}

GameScreen::~GameScreen(){}