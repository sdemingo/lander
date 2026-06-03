#ifndef LANDER_H
#define LANDER_H

//#include "Assets.h"

class Lander{

private:
  const int size = 50;
  int position;
  int angle;
  sf::RectangleShape shape;

public:
  Lander();
  void climb();
  void drop();
  void estabilize();
  void left();
  void right();
  bool crash(int floor);
  sf::RectangleShape get_shape(int x_position);
  
};




#endif
