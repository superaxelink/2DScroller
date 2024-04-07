#include "../entity/entity.h"
#include "../states/StateFly.h"
#include "../states/StateDead.h"


#ifndef FLY_H
#define FLY_H

class Fly : public Entity{

public:
  int desiredBaseWidth;
  int desiredBaseHeight; 
  int desiredHeight;

  Fly(GameScreen& gameScreen, Background& background, int reference);
  ~Fly();

  void initStates(std::string color);
  void initStates2(std::string color);
  void verticalMovement();
  void update(Entity* attacked) override;
  void close();
};

#endif