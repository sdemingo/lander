#include <SFML/Graphics.hpp>
#include <iostream>

#include "Lander.h"

Lander::Lander(sf::RenderWindow &v, sf::View &c) : ventana(&v), camara(&c) {
  position=0;
  angle=0;



  if (!textura.loadFromFile("assets/sprites/lem.png")) {
    std::cout << "Error: No se pudo encontrar assets/sprites/lem.png" << std::endl;
  }else{
    sprite.setTexture(textura);
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    sprite.setPosition(camara->getCenter().x, position);
  }

/*  shape.setFillColor(sf::Color::Blue);
  shape.setSize(sf::Vector2f(size,size));
  shape.setOrigin({float(size/2),float(size/2)});
*/
}

void Lander::climb(){
  position=position-5;
}

void Lander::drop(){
  position=position+1;
}

void Lander::estabilize(){
  //shape.setRotation(0.0f);
}

void Lander::right(){
  //shape.setRotation(25.0f);
}

void Lander::left(){
  //shape.setRotation(-25.0f);
}

bool Lander::land(int floor){
  return position >= floor - size;
}

void Lander::draw(){
  sprite.setPosition(camara->getCenter().x, position);
  ventana->draw(sprite);
}

/*sf::RectangleShape Lander::get_shape(int x_position){
  shape.setPosition(x_position, position);
  return shape;
}*/
