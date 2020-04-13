#ifndef MAPA_H
#define MAPA_H
#pragma once
#include "tinyxml.h"
#include <string>
#include "SFML/Graphics.hpp"

using namespace std;
class Map {

public:
  Map(string s, int puntos);
  ~Map();
  void Update(sf::Event event,sf::RenderWindow &window);
  void draw(sf::RenderWindow &window);
  void setactivelayer(int layer);
  TiXmlElement* cambio(int l, TiXmlElement &d);
  bool fin(){
    return finalizado;
  };
  void terminar(){
     std::cout<<"terminado";
     finalizado=true;
  };
  int getpuntos(){
    return puntosfin;
  };
  int*** gettilemap(){
    return _tilemap;
  };
  sf::Sprite**** gettilemapSprite(){
    return _tilemapSprite;
  };
  int getnumlayers(){
    return _numlayers;
  };
  int getheight(){
    return _height;
  };
  int getwidth(){
    return _width;
  };
  void setTileMapa(int l,int y,int z,int valor)
  {
    _tilemap[l][y][z] = valor;
  }

  sf::Sprite gettilemapSprite(int l, int y, int x); // Get sprite de los til
  sf::Sprite spawnDino(int pos_dino, int l, int y, int x);
  void anadirVector(std::vector<sf::Sprite*> &vectorS);
  void moveRightDino();
  void moveLeftDino();
  void moveUpDino();
  void moveDownDino();
  void Update();
  void reservarMemoria(int num);
  void liberar();

private:
  int puntosfin;
  bool finalizado;
  int _width;
  int _height;
  int _tilewidth;
  int _tileheigh;
  int _numlayers;
  int ***_tilemap;
  int _activelayer;
  string _nombremapa;
  sf::Font fuente;
  sf::Text texto;
  sf::VertexArray m_vertices;
  sf::Texture _tilesettexture;
  
  sf::Sprite ****_tilemapSprite;


};

#endif