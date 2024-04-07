#include "KeyHandler.h"
#include <algorithm>
#include <iostream>

KeyHandler::KeyHandler() : keys(), 
	upPressed(false), 
	downPressed(false), 
	leftPressed(false),
	rightPressed(false), 
	spacePressed(false), 
	attackPressed(false), 
	enterPressed(false),
	deletePressed(false),
	currentKeyStates(SDL_GetKeyboardState( NULL )){
	//currentKeyStates = SDL_GetKeyboardState( NULL );
}

void KeyHandler::runEventLoop(bool& quit){
  while(SDL_PollEvent( &e )!=0){
    //User request quit
    if(e.type == SDL_QUIT){
      quit = true;
    }else if(e.type == SDL_KEYDOWN){
			SDL_Keycode key = e.key.keysym.sym;
			if(key==SDLK_a){
				handleKeyDown("left", leftPressed);
			}
			if(key==SDLK_d){
				handleKeyDown("right", rightPressed);
			}
			if(key==SDLK_w){
				handleKeyDown("up", upPressed);
			}
			if(key==SDLK_s){
				handleKeyDown("down", downPressed);
			}
			if(key==SDLK_SPACE){
				handleKeyDown("space", spacePressed);
			}
			if(key==SDLK_RETURN){
				handleKeyDown("enter", enterPressed);
			}
			if(key==SDLK_j){
				handleKeyDown("attack", attackPressed);
			}
			if(key==SDLK_BACKSPACE){
				handleKeyDown("delete", deletePressed);
			}
		}else if(e.type == SDL_KEYUP){
			SDL_Keycode key = e.key.keysym.sym;
			if(key==SDLK_a){
				handleKeyUp("left", leftPressed);
			}
			if(key==SDLK_d){
				handleKeyUp("right", rightPressed);
			}
			if(key==SDLK_w){
				handleKeyUp("up", upPressed);
			}
			if(key==SDLK_s){
				handleKeyUp("down", downPressed);
			}
			if(key==SDLK_SPACE){
				handleKeyUp("space", spacePressed);
			}
			if(key==SDLK_RETURN){
				handleKeyUp("enter", enterPressed);
			}
			if(key==SDLK_j){
				handleKeyUp("attack", attackPressed);
			}
			if(key==SDLK_BACKSPACE){
				handleKeyUp("delete", deletePressed);
			}
		}
  }
}

void KeyHandler::vectorKeysPrint(){
	std::cout << "[";
  for (size_t i = 0; i < keys.size(); ++i) {
    std::cout << keys[i] << ", ";
  }
  std::cout<< "]" << std::endl;
}

void KeyHandler::handleKeyDown(std::string keyName, bool& keyBool) {
	if(std::find(keys.begin(), keys.end(), keyName) == keys.end()){
		keys.push_back(keyName);
	}
	keyBool = true;
}


void KeyHandler::handleKeyUp(std::string keyName, bool& keyBool) {
	auto it = std::find(keys.begin(), keys.end(), keyName);
	if( it != keys.end()){
		keys.erase(it);
	}
	keyBool = false;
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