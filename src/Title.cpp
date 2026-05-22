#include <SFML/Graphics.hpp>
#include "Title.h"
#include "Assets.h"


Title::Title(std::string fontname){

  std::string fontpath = loader.get_path("fonts/playfulltime.ttf");
  if (!Title::font.loadFromFile(fontpath))
    {
      //std::cout << "No encuentro la fuente" << std::endl;
    }
}


sf::Text Title::make_title(std::string strtext){

  sf::Text text(strtext, Title::font, 80);
  text.setPosition(100,100);
  text.setFillColor(sf::Color::White);
  
  return text;
}
