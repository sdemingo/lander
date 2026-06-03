#include <SFML/Graphics.hpp>
#include "Title.h"


Title::Title(std::string fontname){

  std::string fontpath = "assets/fonts/";
  if (!Title::font.loadFromFile(fontpath + fontname))
    {
      //std::cout << "No encuentro la fuente" << std::endl;
    }
}


sf::Text Title::make_title(std::string strtext, int x_position){

  sf::Text text(strtext, Title::font, 80);
  text.setPosition(x_position - 100, 100);
  text.setFillColor(sf::Color::White);
  
  return text;
}
