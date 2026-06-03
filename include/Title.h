#ifndef TITLE_H
#define TITLE_H

class Title{

private:
  sf::Font font;


public:
  Title(std::string fontname);
  sf::Text make_title(std::string text, int x_position);

};




#endif
