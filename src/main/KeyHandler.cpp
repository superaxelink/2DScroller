#include "KeyHandler.h"
#include <algorithm>
#include <iostream>

KeyHandler::KeyHandler(){

	currentKeyStates = SDL_GetKeyboardState( NULL );

}

void KeyHandler::runEventLoop(bool& quit){
  while(SDL_PollEvent( &e )!=0){
    //User request quit
    if(e.type == SDL_QUIT){
      quit = true;
    }else if(e.type == SDL_KEYDOWN){
			SDL_Keycode key = e.key.keysym.sym;
			if(key==SDLK_a){
				if(std::find(keys.begin(), keys.end(), "left") == keys.end()){
					keys.push_back("left");
				}
			}
			if(key==SDLK_d){
				if(std::find(keys.begin(), keys.end(), "right") == keys.end()){
					keys.push_back("right");
				}
			}
		}else if(e.type == SDL_KEYUP){
			SDL_Keycode key = e.key.keysym.sym;
			if(key==SDLK_a){
				auto it = std::find(keys.begin(), keys.end(), "left");
				if( it != keys.end()){
					keys.erase(it);
				}
			}
			if(key==SDLK_d){
				auto it = std::find(keys.begin(), keys.end(), "right");
				if(it != keys.end()){
					keys.erase(it);
				}
			}
		}
/* 		std::cout<<'[';
		for(auto element: keys){
			std::cout<<element<<", ";
		}
		std::cout<<']'<<'\n'; */
  }
}

/* void KeyHandler::keyPressed(){
  if( currentKeyStates[ SDL_SCANCODE_UP ] ){
		currentTexture = &gUpTexture;
	}else if( currentKeyStates[ SDL_SCANCODE_DOWN ] ){
		currentTexture = &gDownTexture;
	}else if( currentKeyStates[ SDL_SCANCODE_LEFT ] ){
		currentTexture = &gLeftTexture;
	}else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] ){
		currentTexture = &gRightTexture;
	}else{
		currentTexture = &gPressTexture;
	}
} */

KeyHandler::~KeyHandler(){}