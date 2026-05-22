#include <SFML/Graphics.hpp>

#include "Lander.h"

Lander::Lander(){
  position=0;
  angle=0;

  shape.setFillColor(sf::Color::Blue);
  shape.setSize(sf::Vector2f(size,size));
  shape.setOrigin({float(size/2),float(size/2)});
}

void Lander::climb(){
  position=position-5;
}

void Lander::drop(){
  position=position+1;
}

void Lander::estabilize(){
  shape.setRotation(0.0f);
}

void Lander::right(){
  shape.setRotation(25.0f);
}

void Lander::left(){
  shape.setRotation(-25.0f);
}

bool Lander::crash(int floor){
  return position >= floor - size;
}

sf::RectangleShape Lander::get_shape(){
  shape.setPosition(375, position);
  return shape;
}
