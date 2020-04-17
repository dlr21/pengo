#ifndef MAPA_H
#define MAPA_H
#pragma once
#include "tinyxml.h"
#include <string>
#include "SFML/Graphics.hpp"
#include "jugador.h"

using namespace std;
class Map {

public:
  Map(string s, int puntos);
  ~Map();
  void Update(sf::RenderWindow &window);
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
  void setTileMapa(int l,int y,int z,int valor){
    _tilemap[l][y][z] = valor;
  }

  sf::Sprite* gettilemapSprite(int l, int y, int x); // Get sprite de los til
   void settilemapSprite(sf::Sprite* s, int y, int x){
     _tilemapSprite[1][y][x]=s;
   } // Get sprite de los til
  sf::Sprite spawnDino(int pos_dino, int l, int y, int x);
  void anadirVector(std::vector<sf::Sprite*> &vectorS);
  void anadirParedes(std::vector<sf::Sprite*> &vectorS);
  void moveRightDino();
  void moveLeftDino();
  void moveUpDino();
  void moveDownDino();
  void Update();
  void reservarMemoria(int num);
  sf::Sprite* empujado(sf::Sprite* j,int dir);
  void deslizarbloque(sf::Sprite* s, int dir,float time);
  void borrardemapa(int i, int x, int y){
    if(_tilemap[i][y][x]==5){
              _tilemapSprite[i][y][x]=NULL;
            delete[] _tilemapSprite[i][y][x];
    }
  }
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
    float kVel=1882/10;
    float kVelx=1882/10;
    float kVely=1882/10;  
  sf::Sprite ****_tilemapSprite;


};

#endif