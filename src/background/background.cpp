#include "background.h"
#include "../entity/player.h"


Background::Background(GameScreen& gameScreen) : gameScreen(gameScreen){

  background1 = NULL;
  background2 = NULL;
  background3 = NULL;
  background4 = NULL;
  background5 = NULL;
  width = 0;
  height = 0;
  groundLine = gameScreen.SCREEN_HEIGHT- 83;
  x=0;
  y=0;
  //Load media
  loadMedia();
  rect = new SDL_Rect();
  rect->x = 0;
  rect->y = 0;
  rect->w = gameScreen.SCREEN_WIDTH;
  rect->h = gameScreen.SCREEN_HEIGHT;
}

//bool Background::loadMedia(SDL_Renderer* &gRenderer){
bool Background::loadMedia(){

  std::filesystem::path currentPath = std::filesystem::current_path();
  //Loading success flag;
  bool success = true;
  //Load splash image
  background1 = utils.loadTexture(currentPath.string() + "/res/background/layerCity1.png", gameScreen.gRenderer, width, height);
  background2 = utils.loadTexture(currentPath.string() + "/res/background/layerCity2.png", gameScreen.gRenderer, width, height);
  background3 = utils.loadTexture(currentPath.string() + "/res/background/layerCity3.png", gameScreen.gRenderer, width, height);
  background4 = utils.loadTexture(currentPath.string() + "/res/background/layerCity4.png", gameScreen.gRenderer, width, height);
  background5 = utils.loadTexture(currentPath.string() + "/res/background/layerCity5.png", gameScreen.gRenderer, width, height);
	if( background5 == NULL ){
	  printf("Failed to load PNG image!\n");
	  success = false;
  }  
  return success;
}

/* void Background::draw(Player player){ */
void Background::draw(Player player){
  utils.render(0, 0, gameScreen.SCREEN_WIDTH, height, rect, gameScreen.gRenderer, background1);
  utils.render(0, 0, gameScreen.SCREEN_WIDTH, height, rect, gameScreen.gRenderer, background2);
  utils.render(0, 0, gameScreen.SCREEN_WIDTH, height, rect, gameScreen.gRenderer, background3);
  utils.render(0, 0, gameScreen.SCREEN_WIDTH, height, rect, gameScreen.gRenderer, background4);
  utils.render(0, 0, gameScreen.SCREEN_WIDTH, height, rect, gameScreen.gRenderer, background5);
}

void Background::update(){
  if((rect->x + gameScreen.SCREEN_WIDTH)>=width){
    rect->x=0;
  }else if(rect->x <=0){
    rect->x = gameScreen.SCREEN_WIDTH;
  }
}

void Background::reset(){
  x=0;
}

void Background::close(){
  SDL_DestroyTexture(background1);
  SDL_DestroyTexture(background2);
  SDL_DestroyTexture(background3);
  SDL_DestroyTexture(background4);
  SDL_DestroyTexture(background5);
  background1 = NULL;
  background2 = NULL;
  background3 = NULL;
  background4 = NULL;
  background5 = NULL;
  delete rect;
}

Background::~Background(){}