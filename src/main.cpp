#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Title.h"
#include "Lander.h"
#include "Terrain.h"

const int HEIGHT=600;
const int WIDTH=800;


int main(void) {

  std::srand(std::time({}));
  sf::Clock reloj;

  sf::RenderWindow ventana(sf::VideoMode(WIDTH, HEIGHT), "Lander 0.1");
  ventana.setFramerateLimit(60);  // 60 FPS

  bool endgame = false;
  std::string endTitle = "";
  
  Lander lander;

  sf::View camara(sf::FloatRect(0.f, 0.f, WIDTH, HEIGHT));
  float velocidad_camara = 300.f; // Píxeles por segundo


  Terrain mundo(ventana,camara);
  mundo.generate();



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

      if (lander.land(Terrain::FLOOR_HEIGHT)){ 
        endgame=true;          
        if (mundo.is_green_zone()){
          endTitle="Bien :)";
        }else{
          endTitle="Perdiste!!";
        }
      }



      // --- SECCIÓN DE RENDERIZADO (Pintar) ---

      if (endgame){
        ventana.clear(sf::Color::Black);
        Title titulo_final("playfulltime.ttf");
        ventana.draw(titulo_final.make_title(endTitle, camara.getCenter().x));
        
      }else{
        ventana.clear(sf::Color(10, 15, 30));
        ventana.setView(camara);

        mundo.draw();
        ventana.draw(lander.get_shape(camara.getCenter().x));
      }
      ventana.display();
  }


  return 0;
}
