#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Title.h"
#include "Lander.h"

const int HEIGHT=600;
const int WIDTH=800;



/*
  Creamos el terreno

//tipo_de_dato nombre_matriz[filas][columnas]; 
*/

const int COLUMNS=800;
const int MAX_TERRAIN_HEIGHT=100;



int next_height(int cur_height){


  if ((std::rand() % 10) > 7){
    return cur_height;
  }

    // Cambiamos la altura de la columna actual un poco respecto a la anterior
    // (rand() % 3 - 1) da como resultado -1, 0 o 1

  int variacion = 1; // Cuanto mayor sea, más escarpadas serán las montañas
  cur_height += (std::rand() % 3 - 1) * variacion;
  
  // Controlamos que no se salga de los límites de la pantalla (cielo y suelo)
  if (cur_height < 50) 
    cur_height = 50; // Límite para el cielo
  if (cur_height > MAX_TERRAIN_HEIGHT - 10) 
    cur_height = MAX_TERRAIN_HEIGHT - 10;

  return cur_height;

}




sf::Sprite generate_terrain(sf::Texture& texture){
  char terrain[MAX_TERRAIN_HEIGHT][COLUMNS];


  sf::Image terrainImage;
  terrainImage.create(COLUMNS, MAX_TERRAIN_HEIGHT, sf::Color::Black);

  int altura_actual = MAX_TERRAIN_HEIGHT / 2; // Empezamos a mitad de pantalla
  
  for (int col = 0; col < COLUMNS; ++col) {
    
    altura_actual = next_height(altura_actual);

    // Ahora rellenamos la matriz columna a columna
    for (int row = 0; row < MAX_TERRAIN_HEIGHT; ++row) {
        if (row >= altura_actual) {
            terrain[row][col] = 1; // 1 = Tierra (Recuerda: mayor row significa más abajo)
        } else {
            terrain[row][col] = 0; // 0 = Aire / Cielo
        }
    }
  }

  for (int col = 0; col < COLUMNS; ++col) {
    for (int row = 0; row < MAX_TERRAIN_HEIGHT; ++row) {
      int valor=terrain[row][col];    
      // Aquí ejecutasvalores de la matriz a píxeles en una sf::Image:
      sf::Color color = (valor > 0) ? sf::Color::Black : sf::Color::Green;
      terrainImage.setPixel(col, row, color);
    }
  }
  
  texture.loadFromImage(terrainImage);
  sf::Sprite terrainSprite(texture);
  return terrainSprite;
}

















int main(void) {

  std::srand(std::time({}));

  sf::Texture terrainTexture;  // Sprite del terreno

  sf::RenderWindow ventana(sf::VideoMode(WIDTH, HEIGHT), "Lander 0.1");
  ventana.setFramerateLimit(60);  // 60 FPS

  bool game_over = false;
  Lander lander;



  sf::Sprite sprite=generate_terrain(std::ref(terrainTexture));
  sprite.setPosition(0,HEIGHT - MAX_TERRAIN_HEIGHT);
  

  while (ventana.isOpen()) {
      sf::Event evento;

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
          lander.left();
        }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
          lander.right();
        }


      if (lander.crash(HEIGHT))
        game_over=true;
      

      // --- SECCIÓN DE RENDERIZADO (Pintar) ---

      if (!game_over){
        ventana.clear(sf::Color::Red);
        ventana.draw(sprite);
        ventana.draw(lander.get_shape());

  
      }else{
        ventana.clear(sf::Color::Black);

        Title titulo_final("fonts/playfulltime.ttf");
        ventana.draw(titulo_final.make_title("Perdiste!!"));
      }


      ventana.display(); // Mostramos el resultado en la pantalla

  }


  return 0;
}
