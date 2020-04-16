#pragma once
#include <SFML/Graphics.hpp>
#include "bombas.h"
#include "Map.h"
#include "../dinosaurio/dinosaurio.h"

class Colisiones {

public:
  Colisiones(){};
  static void crearColisiones(sf::Sprite &jugador,std::vector<sf::Sprite*> objetos,int direccion,int velocidad,float time);


  static void update(sf::Clock &temporizador,std::vector<Dinosaurio*> &dinosaurios,Jugador &jugador,std::vector<sf::Sprite> &totalExplosiones,Map &mapa, std::vector<sf::Sprite*> &todoSprites,std::vector<sf::Sprite*> &paredesSprites,float time);

};