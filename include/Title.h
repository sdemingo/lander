#ifndef TITLE_H
#define TITLE_H

#include "Assets.h"

class Title{

private:
  sf::Font font;
  Assets loader;

public:
  Title(std::string fontname);
  sf::Text make_title(std::string text);

};




#endif
