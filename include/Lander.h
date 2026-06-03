#ifndef LANDER_H
#define LANDER_H


class Lander{

public:
  static const int size = 64;

private:
  int position;
  int angle;
  sf::RenderWindow *ventana;
  sf::View *camara;

  sf::Texture textura;
  sf::Sprite sprite;

public:
  Lander(sf::RenderWindow &v, sf::View &c);
  void climb();
  void drop();
  void estabilize();
  void left();
  void right();
  bool land(int floor);
  void draw();

};




#endif
