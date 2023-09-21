#include <string>

class Entity{
public:

  int width;
  int height;
  int sheetWidth;
  int sheetHeight;
  int x;
  int y;
  int vx;
  int vy;
  int jumpHeight;
  int weight;
  std::string direction;

  //COUNTERS
  int frame;  

  //Constructor
  Entity();
  //Destructor
  ~Entity();

};