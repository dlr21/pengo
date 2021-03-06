#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "jugador.h"
#include "dinosaurio.h"

class Colisiones {

public:
  Colisiones(){};
  static void crearColisiones(sf::Sprite &jugador,std::vector<sf::Sprite*> objetos,int direccion,int velocidad,float time, Jugador* j);
  static void update(sf::Clock &temporizador,sf::Sprite* deslizado,std::vector<Dinosaurio*> &dinosaurios,Jugador &jugador,std::vector<sf::Sprite> &totalExplosiones,Map &mapa, std::vector<sf::Sprite*> &todoSprites,std::vector<sf::Sprite*> &paredesSprites,float time);
};