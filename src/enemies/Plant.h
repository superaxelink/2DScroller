#include "../states/StateIdle1.h"
#include "../states/StateDead.h"

#include "../entity/entity.h"

#ifndef PLANT_H
#define PLANT_H

class Plant : public Entity{

public:

  SDL_Texture* Idle1;
  Plant(GameScreen& gameScreen, Background& background, int reference);
  ~Plant();

  void initStates(std::string color);
  void close();

};

#endif