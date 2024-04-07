#include <string>
#include <algorithm>
#include <cmath>
#include <cstdarg>
#include <unordered_set>
#include "../main/GameScreen.h"
#include "../background/background.h"
#include "../main/KeyHandler.h"

#ifndef ENTITY_H
#define ENTITY_H

class States;

class Entity{
public:

  GameScreen& gameScreen;
  Background& background;
  SDL_Texture* heart1;
  SDL_Texture* heart2;
  SDL_Texture* heart3;
  SDL_Rect* heartSprite;

  //Basic properties
  int width;
  int height;
  int sheetWidth;
  int sheetHeight;
  int x;
  int y;
  int baseVx;
  int baseVy;
  int runVx;
  int vx;
  int vy;
  int jumpHeight;
  int weight;
  int worldX;
  int worldY;
  int groundLine;

  double angle;

  std::string direction;
  std::string type;
  std::string name;

  int baseLife;
  int currentLife;

  int points;
  int totalPoints;

  //HITBOX
  int xStartSquare;
  int xEndSquare;
  int yEndSquare;
  bool drawHitbox;

  //Attack properties
  int damage;
  int knockBackvx;

  //INVINCIBILITY
  int invincibleTime;
  int invincibleCounter;
  bool invincible;

  //COUNTERS
  int frame;  

  //CURRENT STATE OF THE ENTITY
  States* currentState;

  //AVAILABLE STATES
  States* stateList[11];

  //Player only properties
  KeyHandler* kh;

  enum AvailableStates{
    Attack_1,
    Attack_2,
    Attack_3,
    Dead,
    Hurt,
    Idle_1,
    Idle_2,
    Jump,
    Run,
    Walk,
    Fly
  };

  //Constructors
  //For player
  Entity(GameScreen& gameScreen, KeyHandler* kh, Background& background);
  //For enemies
  Entity(GameScreen& gameScreen, Background& background);
  //Destructor
  ~Entity();

  void draw(bool drawHitboxes);
  void drawPunctuation(std::string text);
  void drawMonsterLife(SDL_Renderer* renderer, int x, int y);
  void horizontalMovement();
  void npcHorizontalMovement();
  void knockBack();
  void changeState(int newState, std::string direction, int verticalPosition=-99999, int currentFrame = -1);
  void changeDirection(std::string direction);
  void hitBoxDrawing(SDL_Renderer* renderer, int x, int y, int w, int h);
  void updateHitBox();
  void playerEnemiesUpdate(std::unordered_set<Entity*>& enemies);
  void playerAttackIndividualCollision(Entity* enemy);
  void enemyAttackCollision(Entity* attacked);
  void checkPlayerCollisions(Entity* npc);
  void individualCollisionManagement(Entity* npc);
  void randomDirection();
  void attackHitBoxDraw();
  void checkEnemyDead();
  void close();
  void reset();
  bool isDeadAnimationCompleted(Entity* enemy) const;
  bool isOutOfBounds(Entity* enemy) const;
  bool squareCollision(Entity* obj);
  bool onGround();
  virtual void update(std::unordered_set<Entity*>& enemies);
  virtual void update(Entity* attacked);
  virtual void gravity();
  virtual void checkDirection();  

private:
  bool collisionDetected(Entity* npc);
  bool parryDetected(Entity* npc);
  void handleCollision(Entity* npc);
};

#endif