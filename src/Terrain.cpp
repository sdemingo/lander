
#include "Terrain.h"
#include "Lander.h"

Terrain::Terrain(sf::RenderWindow &v, sf::View &c) : ventana(&v), camara(&c) {

}

void Terrain::generate(){

  for (int i = 0; i < MAP_WIDTH; ) {
    if (rand() % 10 < 2 && i < MAP_WIDTH - 5) { 
        // 20% de probabilidad de generar una zona de aterrizaje de 5 tiles de ancho
        for (int j = 0; j < 5; ++j) {
            mundo[i + j] = TileType::Aterrizaje;
        }
        i += 5;
    } else {
        // El resto es roca normal
        mundo[i] = TileType::Roca;
        i++;
    }
  }
}

bool Terrain::is_green_zone(){
  // Detecta si en la zona central de la pantalla hay zona verde para poder aterrizar
  // Suficientemente ancha como para que la nave entre

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
  /*
    Calculamos los límites visibles del mapa en formato Tile
  */
  float izquierda_pantalla = camara->getCenter().x - (ventana->getSize().x/2);
  float derecha_pantalla = camara->getCenter().x + (ventana->getSize().x/2);      

  int tile_inicial = static_cast<int>(izquierda_pantalla) / TILE_SIZE;
  int tile_final = static_cast<int>(derecha_pantalla) / TILE_SIZE;

  if (tile_inicial < 0) 
    tile_inicial = 0;
  if (tile_final >= MAP_WIDTH) 
    tile_final = MAP_WIDTH - 1;

  /*
    Dibujado de los tiles visibles mas un gran tile con el suelo profundo
    bajo la capa superficial de tiles
  */
  float suelo_y = FLOOR_HEIGHT;  // lugar donde ponemos la referencia del suelo 
  sf::RectangleShape tileShape(sf::Vector2f(16.f, 16.f));

  sf::RectangleShape tierraProfunda(sf::Vector2f(800.f, 200.f));
  tierraProfunda.setFillColor(sf::Color(128, 128, 128));
  tierraProfunda.setPosition(izquierda_pantalla, suelo_y + 16.f);
      
  ventana->draw(tierraProfunda);

  /* 
     Dibujado el del escenario en base al mapa plano generado antes
  */
  for (int i = tile_inicial; i <= tile_final; ++i) {
    // Posicionamos el tile en su lugar correspondiente del mundo real
    tileShape.setPosition(i * TILE_SIZE, suelo_y);
        
    if (mundo[i] == TileType::Roca) {
      tileShape.setFillColor(sf::Color(128, 128, 128)); // Gris para la roca
      ventana->draw(tileShape);
    } 
    else if (mundo[i] == TileType::Aterrizaje) {
      tileShape.setFillColor(sf::Color::Green); // Verde para las zonas de aterrizaje
      ventana->draw(tileShape);
    }
  }
}


