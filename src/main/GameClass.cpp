#include "GameClass.h"

GameClass::GameClass(): gameScreen(), 
  keyHandler(), 
  kh(&keyHandler){
  if(!gameScreen.init()){
		printf( "Failed to initialize!\n" );
    gameScreen.close();
    exit(EXIT_FAILURE);
  }
  menuHandler = new MenuHandler(&gameScreen, kh); 
  background = new Background(gameScreen);
  player = new Player(gameScreen, kh, *background);
  enemies.insert(new Slime(gameScreen, *background, player->x));
  enemies.insert(new Plant(gameScreen, *background, player->x));
  enemies.insert(new Fly(gameScreen, *background, player->x));
  
  gameStarted = false;
  gameOver = false;
  drawHitboxes = false;
  pointsToWin = 200;
}

GameClass::~GameClass(){
  delete menuHandler;
  delete background;
  delete player;
  //free resources for enemies
  for (auto enemy : enemies) {
    delete enemy;
  }
  enemies.clear(); //free enemy set
  if(kh!=nullptr){
    kh=nullptr;
  }
}

void GameClass::updateGame(bool &quit){
  int gameControlValue = 0;
  //Handle events on queue
  kh->runEventLoop(quit);
  if(std::find(kh->keys.begin(), kh->keys.end(), "delete")!= kh->keys.end()){
    drawHitboxes=!drawHitboxes;
  }
	//Clear screen
	SDL_RenderClear( gameScreen.gRenderer );
  if(gameStarted && player->totalPoints<pointsToWin){
    //Add enemies
    double rand = Utils::randomness();
    if(rand<0.1 & enemies.size()<10){
      enemies.insert(new Slime(gameScreen, *background, player->x));
    }
    else if(0.5<rand & rand<0.6 & enemies.size()<10){
      enemies.insert(new Fly(gameScreen, *background, player->x));
    }
    else if(0.9<rand & rand<1.0 & enemies.size()<10){
      enemies.insert(new Plant(gameScreen, *background, player->x));
    }

    background->update();
    player->update(enemies);
    if(!enemies.empty()){
      for(Entity* enemy : enemies){
        enemy->update(player);
      }
    }
    if(player->currentState->stateNumber==player->AvailableStates::Dead){
      gameControlValue = menuHandler->update(gameStarted);
      if(gameControlValue==1){
        resetGame();
      }else if(gameControlValue ==2){
        stopGame(quit);
      }
    }
  }else{
    gameControlValue = menuHandler->update(gameStarted);
    if(gameControlValue==1){
        resetGame();
    }else if(gameControlValue ==2){
      stopGame(quit);
    } 
  }
}

void GameClass::drawGame(){
  if(gameStarted){
    background->draw(*player);
    if(!enemies.empty()){
      for(Entity* enemy : enemies){
        enemy->draw(drawHitboxes);
      }
    }
    player->draw(drawHitboxes);
    if(player->totalPoints>=pointsToWin){
      menuHandler->drawWinnerMenu();
    }
    if(player->currentState->stateNumber==player->AvailableStates::Dead){
      menuHandler->drawGameOverMenu();
    }
    if(player->currentLife>0 &&  player->totalPoints<=0){
      menuHandler->drawTitle("Beat the monsters!", 70);
      menuHandler->drawTitle("Get " + std::to_string(pointsToWin) + " points!", 120);
    }
  }else{
    menuHandler->draw();
  }
  SDL_RenderPresent(gameScreen.gRenderer);
}
void GameClass::resetGame(){
  background->reset();
  for (auto it = enemies.begin(); it != enemies.end(); ++it) {
    delete *it; // Eliminar el objeto Entity apuntado por el puntero
  }
  enemies.clear();
  player->reset();
}
void GameClass::stopGame(bool &quit){
  quit = true;  
}

void GameClass::close(){
  //Free resources background
  background->close();
  player->close();
  for (auto enemy : enemies) {
    enemy->close();
  }
  //Free resources and close SDL
  gameScreen.close();
}