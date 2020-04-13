#ifndef ADN_H
#define ADN_H
#pragma once
#include "tinyxml.h"
#include <string>
#include "SFML/Graphics.hpp"

using namespace std;
class Adn {

public:
  Adn(int puntos,int x, int y);
  ~Adn();
  void Update(sf::Event event,sf::RenderWindow &window);
  void draw(sf::RenderWindow &window);
  void Update();
  int getpuntos(){return puntos;}
  bool getvisible(){return visible;}
  void hacervisible(){visible=true;}

private:
  int puntos;
  int posx;
  int posy;
  sf::Texture adntext;
  sf::Sprite *adnsprite;
  bool visible;
};

#endif