#ifndef LANDER_H
#define LANDER_H


class Lander{

public:
  static const int size = 64;

private:
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
  bool land(int floor);
  sf::RectangleShape get_shape(int x_position);
  
};




#endif
