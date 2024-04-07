#include "player.h"

Player::Player(GameScreen& gameScreen, 
  KeyHandler* kh, 
  Background& background): Entity(gameScreen, kh, background){
  Idle1 = nullptr;
  width = 0;
  height = 0;
  worldX = gameScreen.SCREEN_WIDTH/2;
  worldY = background.groundLine;
  frame = 0;
  baseVx = 8;
  baseVy = 27;
  baseLife = 10;
  currentLife = baseLife;
  vx = 0;
  vy = baseVy;
  runVx = baseVx*2;
  jumpHeight = 0;
  weight = 10;
  direction = "right";
  type = "player"; 

  totalPoints = 0;

  invincible = false;
  invincibleTime = 20;
  invincibleCounter = 0;

  damage = 0;

  initStates();
  currentState = stateList[AvailableStates::Idle_1];

  groundLine = background.groundLine - currentState->height;
  x = worldX - currentState->width/2;
  y=0;
  y = groundLine;
  std::filesystem::path currentPath = std::filesystem::current_path();
  int imgSquare = 16;
  heart1 = gameScreen.utils->loadTexture(currentPath.string() + "/res/player/heart_blank.png", 
    gameScreen.gRenderer, imgSquare, imgSquare, true, 50, 50);
  heart2 = gameScreen.utils->loadTexture(currentPath.string() + "/res/player/heart_full.png", 
    gameScreen.gRenderer, imgSquare, imgSquare, true, 50, 50);
  heart3 = gameScreen.utils->loadTexture(currentPath.string() + "/res/player/heart_half.png", 
    gameScreen.gRenderer, imgSquare, imgSquare, true, 50, 50);
  heartSprite = new SDL_Rect();
  heartSprite->x = 0;
  heartSprite->y = 0;
  heartSprite->w = 50;
  heartSprite->h = 50;
  updateHitBox();
}

void Player::initStates(){
  stateList[AvailableStates::Idle_1] = new StateIdle1(gameScreen, kh, *this, 
    4, 8, 1024, 128, 
    73, 55, 0, 31, 
    12, 16, AvailableStates::Idle_1, 0,
    type, "/res/player/ChibiMale/Swordsman/Idle", "/res/player/ChibiMale/Swordsman/IdleLeft");
  stateList[AvailableStates::Idle_2] = new StateIdle2(gameScreen, kh,*this, 
    6, 3, 384, 128, 
    73, 55, 0, 31, 
    14, 18, AvailableStates::Idle_2, 0,
    type, "/res/player/ChibiMale/Swordsman/Idle_2", "/res/player/ChibiMale/Swordsman/IdleLeft_2");
  stateList[AvailableStates::Walk] = new StateWalk(gameScreen, kh, *this, 
    5, 8, 1024, 128, 
    76, 52, 0, 28, 
    20, 8, AvailableStates::Walk, baseVx,
    type, "/res/player/ChibiMale/Swordsman/Walk", "/res/player/ChibiMale/Swordsman/WalkLeft");

  stateList[AvailableStates::Jump] = new StateJump(gameScreen, kh, *this, 
    5, 8, 1024, 128, 
    73, 55, 0, 2, 
    3, 4, 5, 6, 34, 
    8, 25, AvailableStates::Jump, baseVx,
    type, "/res/player/ChibiMale/Swordsman/Jump","/res/player/ChibiMale/Swordsman/JumpLeft");

  stateList[AvailableStates::Run] = new StateRun(gameScreen, kh, *this, 
    5, 8, 1024, 128, 
    73, 55, 0, 35, 
    13, 21, AvailableStates::Run, runVx,
    type, "/res/player/ChibiMale/Swordsman/Run", "/res/player/ChibiMale/Swordsman/RunLeft");
    stateList[AvailableStates::Attack_1] = new StateAttack1(gameScreen, kh, *this, 
    6, 6, 768, 128, 
    75, 53, 0, 32, 
    22, 10, 0, 60, 
    40, 0, 20, 4, 
    AvailableStates::Attack_1, 1,
    type, "/res/player/ChibiMale/Swordsman/Attack_1", "/res/player/ChibiMale/Swordsman/AttackLeft_1");
    
    stateList[AvailableStates::Attack_2] = new StateAttack2(gameScreen, kh, *this, 
    12, 3, 384, 128, 
    75, 53, 0, 33, 
    14, 20, 0, 45, 
    40, 0, 20, 1, 
    AvailableStates::Attack_2, 2,
    type, "/res/player/ChibiMale/Swordsman/Attack_2","/res/player/ChibiMale/Swordsman/AttackLeft_2");
    
    stateList[AvailableStates::Attack_3] = new StateAttack3(gameScreen, kh, *this, 
    8, 4, 512, 128, 
    75, 53, 0, 31, 
    14, 18, 0, 45, 
    52, 0, 20, 1, 
    AvailableStates::Attack_3, 3,
    type, "/res/player/ChibiMale/Swordsman/Attack_3","/res/player/ChibiMale/Swordsman/AttackLeft_3");
    
    stateList[AvailableStates::Hurt] = new StateHurt(gameScreen, kh, *this, 
    8, 3, 384, 128, 
    73, 55, 0, 31, 
    14, AvailableStates::Hurt, 0,
    type, "/res/player/ChibiMale/Swordsman/Hurt", "/res/player/ChibiMale/Swordsman/HurtLeft");
    
    stateList[AvailableStates::Dead] = new StateDead(gameScreen, kh, *this, 
    20, 3, 384, 128, 
    73, 55, 0, 31, 
    14, AvailableStates::Dead, 0,
    type, "/res/player/ChibiMale/Swordsman/Dead", "/res/player/ChibiMale/Swordsman/DeadLeft");
}

Player::~Player(){}