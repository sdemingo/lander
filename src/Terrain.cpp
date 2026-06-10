#include <SFML/Graphics.hpp>
#include <iostream>

#include "Terrain.h"
#include "Lander.h"

Terrain::Terrain(sf::RenderWindow &v, sf::View &c) : ventana(&v), camara(&c) {

  if (!rock_texture.loadFromFile("assets/sprites/rock.png")) {
    std::cout << "Error: No se pudo encontrar assets/sprites/rock.png" << std::endl;
  }else{
    rock_sprite.setTexture(rock_texture);
  }
}

/*
  Generamos el terreno. Solo la capa superficial donde el 20% de
  probabilidad es para generar un tile de aterrizaje y el resto para
  generar un tile de roca.
*/
void Terrain::generate(){

  for (int i = 0; i < MAP_WIDTH; ) {
    if (rand() % 10 < 2 && i < MAP_WIDTH - 5) { 
        for (int j = 0; j < 5; ++j) {
            mundo[i + j] = TileType::Aterrizaje;
        }
        i += 5;
    } else {
        mundo[i] = TileType::Roca;
        i++;
    }
  }
}



/*
  Detecta si en la zona central de la pantalla hay zona verde para poder aterrizar
  Suficientemente ancha como para que la nave entre
*/
bool Terrain::is_green_zone(){

  float lim_izq = camara->getCenter().x - (Lander::size/2);
  float lim_dera = camara->getCenter().x + (Lander::size/2);      

  int tile_inicial = static_cast<int>(lim_izq) / TILE_SIZE;
  int tile_final = static_cast<int>(lim_dera) / TILE_SIZE;
  
  int green_tiles=0;

  for (int i = tile_inicial; i <= tile_final; ++i) {
    if (mundo[i] == TileType::Aterrizaje)
      green_tiles++;
  }

  return (green_tiles >= Lander::size / TILE_SIZE);
}


void Terrain::draw(){
  
  //Calculamos los límites visibles del mapa en formato Tile
  float izquierda_pantalla = camara->getCenter().x - (ventana->getSize().x/2);
  float derecha_pantalla = camara->getCenter().x + (ventana->getSize().x/2);      

  int tile_inicial = static_cast<int>(izquierda_pantalla) / TILE_SIZE;
  int tile_final = static_cast<int>(derecha_pantalla) / TILE_SIZE;

  if (tile_inicial < 0) 
    tile_inicial = 0;
  if (tile_final >= MAP_WIDTH) 
    tile_final = MAP_WIDTH - 1;

  
  // Dibujado de los tiles visibles mas un gran tile con el suelo profundo
  // bajo la capa superficial de tiles
  float suelo_y = FLOOR_HEIGHT;  // Referencia del suelo 
  sf::RectangleShape tileShape(sf::Vector2f(16.f, 16.f));

  // Dibujado de la tierra profunda con sprite teselado
  int filas_profundidad = 13; // Cuántas filas hacia abajo quieres cubrir
  for (int fila = 0; fila < filas_profundidad; ++fila) {
    float y = suelo_y + 16.f + (fila * TILE_SIZE);
    for (int i = tile_inicial; i <= tile_final; ++i) {
      float x = i * TILE_SIZE;
      rock_sprite.setPosition(x, y);
      ventana->draw(rock_sprite);
    }
  }

  //Dibujado el del escenario en base al mapa plano generado antes
  for (int i = tile_inicial; i <= tile_final; ++i) {
    tileShape.setPosition(i * TILE_SIZE, suelo_y);
    if (mundo[i] == TileType::Roca) {
      rock_sprite.setPosition(i * TILE_SIZE, suelo_y);
      ventana->draw(rock_sprite);
    } 
    else if (mundo[i] == TileType::Aterrizaje) {
      tileShape.setFillColor(sf::Color(128, 128, 128));
      ventana->draw(tileShape);
    }
  }
}


