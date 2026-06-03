#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Title.h"
#include "Lander.h"

const int HEIGHT=600;
const int WIDTH=800;

/*
  Creamos el terreno
*/

enum TileType {
    Aire = 0,
    Roca = 1,
    Aterrizaje = 2
};

const int TILE_SIZE = 16; // Cada tile mide 16x16 píxeles
const int MAP_WIDTH = 1000; // El mundo entero tendrá 1000 tiles de ancho
TileType mundo[MAP_WIDTH];
const int FLOOR_HEIGHT=500;


void generate_map(TileType (&mundo)[MAP_WIDTH]){

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








int main(void) {

  std::srand(std::time({}));
  sf::Clock reloj;

  sf::Texture terrainTexture;  // Sprite del terreno

  sf::RenderWindow ventana(sf::VideoMode(WIDTH, HEIGHT), "Lander 0.1");
  ventana.setFramerateLimit(60);  // 60 FPS

  bool game_over = false;
  Lander lander;

  generate_map(mundo);

  // Creamos una vista del mismo tamaño que tu ventana (ej: 800x600)
  sf::View camara(sf::FloatRect(0.f, 0.f, WIDTH, HEIGHT));
  float velocidad_camara = 300.f; // Píxeles por segundo

  while (ventana.isOpen()) {
      sf::Event evento;

      float dt = reloj.restart().asSeconds();

      while (ventana.pollEvent(evento)) {
          if (evento.type == sf::Event::Closed)
              ventana.close();
      }

      // --- SECCIÓN DE ACTUALIZACIÓN ---

      lander.estabilize();
      lander.drop();

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
          lander.climb();
        }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
          camara.move(-velocidad_camara * dt, 0.f); // Mueve la cámara a la izquierda
          lander.left();
        }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
          camara.move(velocidad_camara * dt, 0.f);  // Mueve la cámara a la derecha
          lander.right();
        }

      // Evitamos que la cámara se salga de los límites del mapa (0 por la izquierda)
      if (camara.getCenter().x - (WIDTH/2) < 0.f) {
        camara.setCenter((WIDTH/2), camara.getCenter().y);
      }


      if (lander.crash(FLOOR_HEIGHT))
        game_over=true;

      // --- SECCIÓN DE RENDERIZADO (Pintar) ---

      if (game_over){
        ventana.clear(sf::Color::Black);
        Title titulo_final("playfulltime.ttf");
        ventana.draw(titulo_final.make_title("Perdiste!!", camara.getCenter().x));
        
      }else{
        ventana.clear(sf::Color(10, 15, 30));
        ventana.setView(camara);
      
        /*
          Calculamos los límites visibles del mapa en formato Tile
        */
        float izquierda_pantalla = camara.getCenter().x - (WIDTH/2);
        float derecha_pantalla = camara.getCenter().x + (WIDTH/2);      
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
      
        ventana.draw(tierraProfunda);

        /* 
           Dibujado el del escenario en base al mapa plano generado antes
        */
        for (int i = tile_inicial; i <= tile_final; ++i) {
          // Posicionamos el tile en su lugar correspondiente del mundo real
          tileShape.setPosition(i * TILE_SIZE, suelo_y);
        
          if (mundo[i] == TileType::Roca) {
            tileShape.setFillColor(sf::Color(128, 128, 128)); // Gris para la roca
            ventana.draw(tileShape);
          } 
          else if (mundo[i] == TileType::Aterrizaje) {
            tileShape.setFillColor(sf::Color::Green); // Verde para las zonas de aterrizaje
            ventana.draw(tileShape);
          }
        }

        ventana.draw(lander.get_shape(camara.getCenter().x));
      }
      ventana.display();
  }


  return 0;
}
