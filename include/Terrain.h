#ifndef TERRAIN_H
#define TERRAIN_H

#include <SFML/Graphics.hpp>


class Terrain{

public:
  enum TileType {
    Aire = 0,
    Roca = 1,
    Aterrizaje = 2
  };
  
  const int TILE_SIZE = 16; // Cada tile mide 16x16 píxeles
  static const int MAP_WIDTH = 1000; // El mundo entero tendrá 1000 tiles de ancho
  static const int FLOOR_HEIGHT=500;

private:
  TileType mundo[MAP_WIDTH];
  sf::RenderWindow *ventana;
  sf::View *camara;

  sf::Texture rock_texture;
  sf::Sprite rock_sprite;

public:
  Terrain(sf::RenderWindow &v, sf::View &c);
  void generate();
  bool is_green_zone();
  void draw();
};






#endif
