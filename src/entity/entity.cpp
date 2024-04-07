#include "entity.h"
#include "../states/States.h"


Entity::Entity(GameScreen& gameScreen, Background& background) 
  : gameScreen(gameScreen), kh(nullptr), background(background), stateList(){
    knockBackvx = 0;
    angle = 0;
    xStartSquare = 0;
    xEndSquare = 0;
    yEndSquare = 0;
    heart1 = nullptr;
    heart2 = nullptr;
    heart3 = nullptr;
    heartSprite = nullptr;
  }
Entity::Entity(GameScreen& gameScreen, KeyHandler* kh, Background& background) 
  : gameScreen(gameScreen), kh(kh) ,background(background), stateList(){
    knockBackvx = 0;
    angle = 0;
    xStartSquare = 0;
    xEndSquare = 0;
    yEndSquare = 0;
    heart1 = nullptr;
    heart2 = nullptr;
    heart3 = nullptr;
    heartSprite = nullptr;
  }
Entity::~Entity(){}

void Entity::changeState(int newState, std::string direction, int verticalPosition, int currentFrame){
  currentState = stateList[newState];
  groundLine = background.groundLine - currentState->height;

  int _verticalPosition = (verticalPosition==-99999) ? groundLine : verticalPosition;
  int _currentFrame = (currentFrame==-1) ? 0 : currentFrame;
  
  currentState->frameCounter = _currentFrame; 
  currentState->stateCounter = 0; 
  currentState->spriteCounter = 0; 
  currentState->xStartSubimage = 0;
  changeDirection(direction);
  y = _verticalPosition;
  vy = (y>=groundLine) ? baseVy : vy;
}

void Entity::horizontalMovement(){
  
  if(kh!=nullptr && std::find(kh->keys.begin(), kh->keys.end(), "right") != kh->keys.end() && direction == "right"){
    vx = currentState->speed;
  }
  else if(kh!=nullptr && std::find(kh->keys.begin(), kh->keys.end(), "left") != kh->keys.end() && direction == "left"){
    vx = -currentState->speed; 
  }
  else{
    vx = 0;
  }
  vx += knockBackvx;
  background.rect->x +=  vx;
  //npc->x -= vx; 
		//Center the camera over the dot
/* 		player.currentState->sprite->x = ( player.x + player.currentState->width / 2 ) - gameScreen.SCREEN_WIDTH / 2;
		player.currentState->sprite->y = ( player.y + player.currentState->height / 2 ) - gameScreen.SCREEN_HEIGHT / 2; */

}

void Entity::npcHorizontalMovement(){
  if(type == "enemy"){
    double rand = gameScreen.utils->random();
    if(rand>0.9 && (currentState->stateNumber!=AvailableStates::Hurt || currentState->stateNumber!=AvailableStates::Dead)){
      randomDirection();
    }
    if(direction == "left"){vx=-currentState->speed;}
    else if(direction == "right"){vx=currentState->speed;}
  }
  vx += knockBackvx;
  x+=vx;
  if(currentState->stateNumber ==AvailableStates::Fly){
    int rand = (int) (20*gameScreen.utils->random()-10); 
    x += rand;
  }
}

void Entity::randomDirection(){
  double rand = gameScreen.utils->random();
  if(rand<0.2){
    if(direction=="left"){
      direction = "right";
    }else if(direction=="right"){
      direction = "left";
    }
  }
}

void Entity::knockBack(){
  if(knockBackvx>0){knockBackvx--;}
  else if(knockBackvx<0){knockBackvx++;}
}

//Update player method
void Entity::update(std::unordered_set<Entity*>& enemies){
  if(vx!=0){
    knockBack();
  }
  checkDirection();
  updateHitBox();
  currentState->inputHandler();
  currentState->update();
  horizontalMovement();
  playerEnemiesUpdate(enemies);
}

void Entity::reset(){
  if(type=="player"){
    currentLife = baseLife;
    direction = "right";
    type = "player";
    invincible = false;
    totalPoints = 0;

    currentState = stateList[AvailableStates::Idle_1];
    currentState->spriteCounter=0;
    changeDirection(direction);
    
    groundLine =  background.groundLine-currentState->height;
    x = worldX - currentState->width/2;
    y = worldY - currentState->height;
  }
}

void Entity::playerEnemiesUpdate(std::unordered_set<Entity*>& enemies){
  auto it = enemies.begin();
  //for(auto it = enemies.begin(); it != enemies.end(); ){
  while(it!=enemies.end()){
    Entity* enemy = *it; // Obtener el puntero al enemigo actual
    enemy->x -= vx; //**MEJOR FORMA DE ESCRIBIR ESTO????
    checkPlayerCollisions(enemy);
    if(currentState->stateNumber==AvailableStates::Attack_1 || 
    currentState->stateNumber==AvailableStates::Attack_2 ||
    currentState->stateNumber==AvailableStates::Attack_3){
      playerAttackIndividualCollision(enemy);
    }
    if(isOutOfBounds(enemy)){
      enemy->close();
      it = enemies.erase(it);
      delete enemy;
    }
    else if(isDeadAnimationCompleted(enemy)){
      totalPoints += enemy->points;
      enemy->close();
      it = enemies.erase(it);
      delete enemy; 
    }else{
      ++it;
    }
  }
}

bool Entity::isOutOfBounds(Entity* enemy) const{
  return ((enemy->x>x + gameScreen.SCREEN_WIDTH/2 + 3*enemy->currentState->width) ||
  (enemy->x<x - gameScreen.SCREEN_WIDTH/2 - 3*enemy->currentState->width));
}

bool Entity::isDeadAnimationCompleted(Entity* enemy) const{
  return enemy->currentState->stateNumber == AvailableStates::Dead &&
  enemy->currentState->frameCounter >= (enemy->currentState->totalSprites - 1);
}

//Update npc method
void Entity::update(Entity* attacked){
  if(vx!=0){
    knockBack();
  }
  npcHorizontalMovement();
  checkDirection();
  updateHitBox();
  enemyAttackCollision(attacked);
  currentState->inputHandler();
  currentState->update();
  checkEnemyDead();
}

void Entity::checkEnemyDead(){
  if(type == "enemy" && currentLife<=0 && currentState->stateNumber!=AvailableStates::Dead){
    currentState->frameCounter = 0;
    currentState->stateCounter++;
    changeState(AvailableStates::Dead, direction);
  }
}

void Entity::draw(bool drawHitboxes){
  if(type=="player"){
    drawPunctuation("Your score is: " + std::to_string(totalPoints));
    for(int i=0; i<baseLife/2;i++){
      gameScreen.utils->render(50*i + 10, 0, 0, 0, heartSprite,gameScreen.gRenderer, heart1);
    }
    for(int i=0; i<currentLife;i++){
      if(i%2==0){
        gameScreen.utils->render(50*(i/2) + 10, 0, 0, 0, heartSprite,gameScreen.gRenderer, heart3);
      }else{
        gameScreen.utils->render(50*(i/2) + 10, 0, 0, 0, heartSprite,gameScreen.gRenderer, heart2);
      }
    }
  }
  changeDirection(direction);
  gameScreen.utils->render(x, y, 0, 0, currentState->sprite,gameScreen.gRenderer, currentState->currentSpriteSheet);
  if(drawHitboxes){
    hitBoxDrawing(gameScreen.gRenderer, xStartSquare, y, currentState->widthHitBox, currentState->height);
    attackHitBoxDraw();
  }
  drawMonsterLife(gameScreen.gRenderer, x, y);
}

void Entity::drawPunctuation(std::string text){
  gameScreen.utils->drawText(text, gameScreen.gRenderer, gameScreen.font, gameScreen.SCREEN_WIDTH-200, 15);
}

void Entity::drawMonsterLife(SDL_Renderer* renderer, int x, int y){
  if(this->type!="player" 
    && this->currentLife<this->baseLife
    && this->currentState->stateNumber!=AvailableStates::Dead){
    // Definir rectángulo base
    SDL_Rect baseRect;
    baseRect.x = x + currentState->width/2-25;
    baseRect.y = y-10;
    baseRect.w = 50;
    baseRect.h = 5;
    SDL_Color color;
    color = {0, 0, 0, 255};

    // Draw black rectangle for whole life bar
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a); //Choose color and transparency
    //Enable the renderer's alpha channel to allow transparency
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    //Fill rectangle
    SDL_RenderFillRect(renderer, &baseRect);

    if(this->currentLife>0){
      // Definir rectangulo de vida actual
      SDL_Rect currentLifeRect;
      currentLifeRect.x = x + currentState->width/2-25;
      currentLifeRect.y = y-10;
      currentLifeRect.w = (int) 50*this->currentLife/this->baseLife;
      currentLifeRect.h = 5;
      SDL_Color colorLife;
      colorLife = {255, 0, 0, 255};

      // Draw red rectangle for current life bar
      SDL_SetRenderDrawColor(renderer, colorLife.r, colorLife.g, colorLife.b, colorLife.a); //Choose color and transparency
      //Enable the renderer's alpha channel to allow transparency
      SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
      //Fill rectangle
      SDL_RenderFillRect(renderer, &currentLifeRect);
    }
  }
}

void Entity::attackHitBoxDraw(){
  if(currentState->stateNumber==AvailableStates::Attack_1 ||
  currentState->stateNumber==AvailableStates::Attack_2 ||
  currentState->stateNumber==AvailableStates::Attack_3){
    // spriteContact it's the sprite in which (or from which) the attack will be making contact with the enemy
    if(currentState->frameCounter>=currentState->spriteContact){
      hitBoxDrawing(gameScreen.gRenderer, currentState->xStartSquare,currentState->yStartSquare,
      currentState->widthAttack, currentState->heightAttack);
    }
  }
}

void Entity::updateHitBox(){
  if(direction == "right"){
    xStartSquare = x+currentState->width/2-currentState->offsetHitBoxRight;
  }else if(direction == "left"){
    xStartSquare = x+currentState->width/2-currentState->offsetHitBoxLeft;
  }
  xEndSquare = xStartSquare + currentState->widthHitBox;
  yEndSquare = y + currentState->height;

    if(invincible){
      invincibleCounter++;
      if(invincibleCounter>invincibleTime){
        invincible = false;
        invincibleCounter=0;
      }
    }
}

void Entity::changeDirection(std::string direction){
  if(direction=="right"){
    currentState->sprite->x = currentState->width*currentState->frameCounter + currentState->widthOffset;
    currentState->currentSpriteSheet = currentState->spriteSheet;
  }else if(direction=="left" ){
    currentState->sprite->x = currentState->baseWidth - currentState->width*(currentState->frameCounter+1) + currentState->widthOffset;
    currentState->currentSpriteSheet = currentState->spriteSheetLeft;
  }
}

void Entity::playerAttackIndividualCollision(Entity* enemy){
  if(currentState->frameCounter>= currentState->spriteContact ){
    //Parry
    if( (enemy->currentState->stateNumber==this->AvailableStates::Attack_1||
    enemy->currentState->stateNumber==this->AvailableStates::Attack_2 ||
    enemy->currentState->stateNumber==this->AvailableStates::Attack_3) 
    &&  enemy->currentState->frameCounter>=enemy->currentState->spriteContact ){
      if(parryDetected(enemy)){
        enemy->changeState(this->AvailableStates::Idle_1, enemy->direction);
      }
    }
    //Damage done by the player
    if(!enemy->invincible && enemy->currentState->stateNumber!=this->AvailableStates::Dead){
      if(collisionDetected(enemy)){
        handleCollision(enemy);
        if(direction == "left"){
          enemy->direction = "right";
        }else if(direction=="right"){
          enemy->direction="left";
        }
        if(enemy->stateList[AvailableStates::Hurt]!=nullptr){
          enemy->changeState(AvailableStates::Hurt, enemy->direction);
        }
      }
    }
  }
}

void Entity::enemyAttackCollision(Entity* attacked){
  //face the oponent to attack
  if(currentState->stateNumber==AvailableStates::Attack_1 ||
    currentState->stateNumber==AvailableStates::Attack_2 ||
    currentState->stateNumber==AvailableStates::Attack_3
  ){
    //check if the player(attacked) is to the left of the monster
    if(this->x < attacked->x){
      this->direction = "right";
    }else{
      this->direction = "left";
    }
  }
  //check collision between the enemy attack and hitbox of the player 
  //check collision between attack square and attacked character
  if(!attacked->invincible && attacked->currentState->stateNumber!=this->AvailableStates::Dead && collisionDetected(attacked)){
    if(this->direction=="right"){
      attacked->knockBackvx=currentState->knockBackvx;
      attacked->direction = "left";
    }else if(this->direction=="left"){
      attacked->knockBackvx=-currentState->knockBackvx;
      attacked->direction = "right";
    }
    attacked->currentLife -= this->currentState->attackDamage;
    attacked->changeState(this->AvailableStates::Hurt, attacked->direction);
  }
}

void Entity::checkPlayerCollisions(Entity* npc){
  if(type == "player" && invincible){
    //std::cout<<invincibleCounter<<"\n";
    invincibleCounter++;
    if(invincibleCounter>invincibleTime){
      invincible = false;
      invincibleCounter=0;
    }
  }
  else if(type=="player" && !invincible && currentState->stateNumber!=AvailableStates::Dead){
    individualCollisionManagement(npc);
  }
}

//Collision between an entity and an enemy 
void Entity::individualCollisionManagement(Entity* npc){
  if(!invincible){
    if(squareCollision(npc) && type == "player"){
      invincible = true;
      invincibleCounter = 0;
      currentLife -= npc->damage;
      changeState(AvailableStates::Hurt,direction);
    }
  }
}

bool Entity::squareCollision(Entity* obj2){
  if(obj2->yEndSquare <= this->y ){return false;} //bottom1 above top2
  if(this->yEndSquare <= obj2->y ){return false;} //top1 below bottom2
  if(this->xEndSquare <= obj2->xStartSquare){return false;} //right1 before left2
  if( obj2->xEndSquare <= this->xStartSquare  ){return false;} //left1 past right2
  //If none of the sides from A are outside B
  return true;
}

bool Entity::collisionDetected(Entity* npc){
  return !npc->invincible && gameScreen.utils->squareCollision(
      currentState->xStartSquare, currentState->xEndSquare, currentState->yStartSquare, currentState->yEndSquare,
      npc->xStartSquare, npc->xEndSquare, npc->y, npc->yEndSquare
  );
}

bool Entity::parryDetected(Entity* npc){
  return gameScreen.utils->squareCollision(currentState->xStartSquare, currentState->xEndSquare, currentState->yStartSquare, currentState->yEndSquare, 
  npc->currentState->xStartSquare, npc->currentState->xEndSquare, npc->currentState->yStartSquare, npc->currentState->yEndSquare);
}

void Entity::handleCollision(Entity* npc){
  if (this->direction == "right" ) {
    npc->knockBackvx = currentState->knockBackvx;
  } else if (this->direction == "left") {
    npc->knockBackvx = -currentState->knockBackvx;
  }
  npc->currentLife -= this->currentState->attackDamage;
  npc->invincible = true;
}

void Entity::checkDirection(){
  if(type=="player" && currentState->stateNumber==AvailableStates::Dead){
    return;
  }
  if(kh!=nullptr && std::find(kh->keys.begin(), kh->keys.end(), "left")!= kh->keys.end()){
    direction = "left";
  }
  else if(kh!=nullptr && std::find(kh->keys.begin(), kh->keys.end(), "right")!= kh->keys.end()){
    direction = "right";
  }
}

void Entity::gravity(){
  if(y<groundLine){
    y+=weight;
  }else if(y>=groundLine){
    y = groundLine;
  }
}

void Entity::hitBoxDrawing(SDL_Renderer* renderer, int x, int y, int w, int h){
  // Definir rectángulo
  SDL_Rect rect;
  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;

  SDL_Color color;
  if(type=="player"){
    color = {0, 0, 255, 125};
  }else if (type=="enemy"){
    color = {255, 0, 0, 125};
  }else{
    color = {0, 0, 0, 125};
  }
    /* code */
  

  // Dibujar rectángulo
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a); //Choose color and transparency
  //Enable the renderer's alpha channel to allow transparency
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  //Fill rectangle
  SDL_RenderFillRect(renderer, &rect);
}

bool Entity::onGround(){
  return y>=groundLine;
}

void Entity::close(){
  for (States*& state : stateList) { // Usar referencia a puntero para cambiar el valor en el array
    if (state != nullptr) {
      state->close();
      delete state;
      state = nullptr;
    }
  }
  if(currentState != nullptr){
    currentState = nullptr;
  }
  if(kh!=nullptr){
    kh = nullptr;
  }
  if(heart1!=nullptr){
    SDL_DestroyTexture(heart1);
  }
  if(heart2!=nullptr){
    SDL_DestroyTexture(heart2);
  }
  if(heart3!=nullptr){
    SDL_DestroyTexture(heart3);
  }
  if(heartSprite!=nullptr){
    delete heartSprite;
    heartSprite = nullptr;
  }
}