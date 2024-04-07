#include "States.h"

States::States(
  GameScreen& gameScreen, 
  KeyHandler* kh,
  Entity& entity, 
  int spriteThreshold, int totalSprites, int baseWidth, int baseHeight,
  int height, int yStartSubimage, int widthOffset, int widthHitBox,
  int offsetHitBoxRight, int offsetHitBoxLeft, int stateNumber, int speed,
  std::string type, std::string pathRight, std::string pathLeft
  ) : gameScreen(gameScreen), 
    kh(kh), 
    entity(entity),
    spriteThreshold(spriteThreshold), totalSprites(totalSprites), baseWidth(baseWidth), 
    baseHeight(baseHeight), height(height), yStartSubimage(yStartSubimage), 
    widthOffset(widthOffset), widthHitBox(widthHitBox), offsetHitBoxRight(offsetHitBoxRight), 
    offsetHitBoxLeft(offsetHitBoxLeft), stateNumber(stateNumber), type(type), speed(speed), spriteContact(0){

  initializeVariables(pathRight, pathLeft);
  
}

States::States(
    GameScreen& gameScreen, KeyHandler* kh, Entity& entity,
    int spriteThreshold, int totalSprites, int baseWidth, int baseHeight,
    int height, int yStartSubimage, int widthOffset, int widthHitBox,
    int offsetHitBoxRight, int offsetHitBoxLeft, int speed, int widthAttack, 
    int heightAttack, int xAttackHitboOffset, int yAttackHitboOffset, int spriteContact, 
    int stateNumber, int attackDamage, 
    std::string type, std::string pathRight, std::string pathLeft
  ) : gameScreen(gameScreen), 
    kh(kh), 
    entity(entity),
    spriteThreshold(spriteThreshold), totalSprites(totalSprites), baseWidth(baseWidth), baseHeight(baseHeight), 
    height(height), yStartSubimage(yStartSubimage), widthOffset(widthOffset), widthHitBox(widthHitBox), 
    offsetHitBoxRight(offsetHitBoxRight), offsetHitBoxLeft(offsetHitBoxLeft), speed(speed), widthAttack(widthAttack), 
    heightAttack(heightAttack), xAttackHitboOffset(xAttackHitboOffset), yAttackHitboOffset(yAttackHitboOffset), spriteContact(spriteContact), 
    stateNumber(stateNumber), attackDamage(attackDamage), 
    type(type){

  initializeVariables(pathRight, pathLeft);

}
void States::inputHandler(){}
void States::spriteUpdate(){} 
void States::update(){
  spriteUpdate();
}

void States::draw(int x, int y){}
void States::drawMonsterLife(int x, int y){}

void States::updateHitboxAttack(){
  if(entity.direction == "right" ){
    xStartSquare = entity.xEndSquare + xAttackHitboOffset;
    xEndSquare = xStartSquare + widthAttack;
  }else if(entity.direction == "left" ){
    xStartSquare = entity.xStartSquare-widthAttack;
    xEndSquare = xStartSquare + widthAttack;
  }
  yStartSquare = entity.y + yAttackHitboOffset;
  yEndSquare = yStartSquare + heightAttack;
}

void States::endingAttack(std::string direction, int nextAttackState, Entity* entity){
  int currentHeight = entity->onGround() ? entity->background.groundLine - entity->currentState->height : entity->y;
  double rand = gameScreen.utils->random();
  if(kh!=nullptr && std::find(kh->keys.begin(), kh->keys.end(), "attack")!= kh->keys.end()){
    entity->changeState(nextAttackState, direction, currentHeight);
  }else{
    int stateToChange = entity->AvailableStates::Idle_1;
    int falling = -1;
/*     if(rand>0.5){
      stateToChange = entity->AvailableStates::Idle_1;
    }else{
      stateToChange = nextAttackState;
    } */
    if(!entity->onGround()){
      stateToChange =entity->AvailableStates::Jump;
      falling = entity->stateList[entity->AvailableStates::Jump]->falling ;
    }
    entity->changeState(stateToChange, direction, currentHeight, falling);
  }
  spriteCounter = 0;
};

void States::initializeVariables(std::string pathRight, std::string pathLeft){
  knockBackvx = 0;
  spriteCounter = 0;
  stateCounter = 0;
  frameCounter = 0;
  path = std::filesystem::current_path().string();

  dividedWidth = baseWidth/totalSprites;
  width = dividedWidth;

  spriteSheet = gameScreen.utils->loadTexture(path + pathRight + ".png", gameScreen.gRenderer, baseWidth, baseHeight);
  spriteSheetLeft = gameScreen.utils->loadTexture(path + pathLeft + ".png", gameScreen.gRenderer, baseWidth, baseHeight);
  currentSpriteSheet = spriteSheet;

  sprite = new SDL_Rect();

  sprite->x = width*frameCounter;
  sprite->y = yStartSubimage;
  sprite->w = width;
  sprite->h = height;

/*   if (spriteSheetLeft == nullptr) {
    // Manejar el error (p. ej., lanzar una excepción, imprimir un mensaje de error, etc.)
  } */
}

void States::close(){
  SDL_DestroyTexture(spriteSheet);
  SDL_DestroyTexture(spriteSheetLeft);
  SDL_DestroyTexture(currentSpriteSheet);
  delete sprite;
  spriteSheet = nullptr;
  spriteSheetLeft = nullptr;
  currentSpriteSheet = nullptr;
  sprite = nullptr;
  kh = nullptr;
}

States::~States(){}
