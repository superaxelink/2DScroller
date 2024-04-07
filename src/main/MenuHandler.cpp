#include "MenuHandler.h"

MenuHandler::MenuHandler(GameScreen* gameScreen, KeyHandler* kh) 
  : gameScreen(gameScreen), kh(kh){
  options = 0;
  titles = {"MONSTER FIGHTER", "Choose your character", "GAME OVER! Is the best you can do?", "WINNER! Aren't you great?"};
  mainMenuOptions = {"Start game", "Exit game"};
  subMenuOptions = { "Swordsman", "Archer(not implemented)", "Wizard(not implemented)", "Go Back"};
  gameOverOptions = { "Retry", "To main screen", "Quit"};

  totalOptions = mainMenuOptions.size();

  frameThreshold = 10;
  frameCounter=0;

  menuState = 0;

  std::filesystem::path currentPath = std::filesystem::current_path();
  //Loading success flag;
  bool success = true;
  //Load splash image
  width = gameScreen->SCREEN_WIDTH;
  height = gameScreen->SCREEN_HEIGHT;
  int imageWidth = 0;
  int imageHeight = 0;
  background1 = gameScreen->utils->loadTexture(currentPath.string() + "/res/background/layerCity1.png", 
    gameScreen->gRenderer, imageWidth, imageHeight);

  rect = new SDL_Rect();
  rect->x = 0;
  rect->y = 0;
  rect->w = width;
  rect->h = height;
}
MenuHandler::~MenuHandler(){}
int MenuHandler::update(bool &gameStarted){
  int returnValue = 0;
  if(std::find(kh->keys.begin(), kh->keys.end(),"up")!= kh->keys.end()){
    options-=1;
  }
  else if(std::find(kh->keys.begin(), kh->keys.end(),"down")!= kh->keys.end()){
    options+=1;
  }
  if(options<1 || options>totalOptions){
    options=1;
  }
  if(!gameStarted){
    returnValue = updateMainMenu(gameStarted);
  }else{
    returnValue = updateGameOverMenu(gameStarted);
  }
  return returnValue;
}

int MenuHandler::updateGameOverMenu(bool &gameStarted){
  if(std::find(kh->keys.begin(), kh->keys.end(),"enter")!= kh->keys.end()){
    if(options==1){
      return 1;
      //gp.resetGame();
    }
    if(options==2){
      options=0;
      menuState=0;
      gameStarted = false;
      return 1;
      //gp.resetGame();
    }
    if(options==3){
      return 2;
      //gp.stop();
    }
  }
  return 0;
}
int MenuHandler::updateMainMenu(bool &gameStarted){
  if(menuState==0){
    if(std::find(kh->keys.begin(), kh->keys.end(),"enter")!= kh->keys.end()){
      if(options==1){
        menuState+=1;
      }
      if(options==2){
        return 2;
        //gp.stop();
      }
    }
  }
  else if(menuState==1){
    if(std::find(kh->keys.begin(), kh->keys.end(),"enter")!= kh->keys.end()){
      if(options==1 || options==2 || options == 3){
        gameStarted = true;
        //gp.gameStarted=true;
      }
      if(options==totalOptions){
        menuState = 0;
      }
    }
  }
  return 0;
}
void MenuHandler::drawTitle(std::string text, int y){
  gameScreen->utils->drawText(text, gameScreen->gRenderer,gameScreen->font, gameScreen->SCREEN_WIDTH, y, true);
}
void MenuHandler::drawOptions(std::string text, int y){
  gameScreen->utils->drawText(text, gameScreen->gRenderer,gameScreen->font, gameScreen->SCREEN_WIDTH, y, true);
}
void MenuHandler::drawMenu(std::vector<std::string> menuOptions){
  totalOptions=menuOptions.size();
  for(int i=0; i<totalOptions;i++){
    std::string prefix = (i + 1 == options) ? ">" : "";
    drawOptions(prefix + menuOptions[i], height / 2 - 20 + i * 40);
  }
}
void MenuHandler::draw(){
  gameScreen->utils->render(0, 0, 0, 0, rect, gameScreen->gRenderer, background1);
  //gameScreen.utils->render(50*i + 10, 0, 0, 0, heartSprite,gameScreen.gRenderer, heart1);

  if(menuState==0){
    drawTitle(titles[0],50);
    drawMenu(mainMenuOptions);
  }else if(menuState==1){
    drawTitle(titles[1],50);
    drawMenu(subMenuOptions);
  }
}
void MenuHandler::drawGameOverMenu(){
  drawTitle(titles[2] ,100);
    
  drawMenu(gameOverOptions);
}
void MenuHandler::drawWinnerMenu(){
  drawTitle(titles[3] ,100);
    
  drawMenu(gameOverOptions);
}