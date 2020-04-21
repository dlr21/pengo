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

   
  void settilemap0(int x,int y){
     _tilemap[1][y][x]=0;
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
  bool tresenralla();
  sf::Sprite* gettilemapSprite(int l, int y, int x); // Get sprite de los til
  void settilemapSprite(sf::Sprite* s, int x, int y){
     _tilemapSprite[1][y][x]=s;
  } // Get sprite de los til
  void setid(int x, int y){
     _tilemap[1][y][x]=idmovido;
      std::cout<<_tilemap[1][y][x]<<"SET id"<<std::endl;
      idmovido=0;
  };
  sf::Sprite spawnDino(int pos_dino, int l, int y, int x);
  void anadirVector(std::vector<sf::Sprite*> &vectorS);
  void Update();
  void reservarMemoria(int num);
  sf::Sprite* empujado(sf::Sprite* j,int dir);
  sf::Sprite* dinomira(sf::Sprite* j, int dir);
  sf::Sprite* muroempujon(sf::Sprite* j, int dir);
  void deslizarbloque(sf::Sprite* s, int dir,float time);
  bool borrardemapa(int x, int y){
    if(_tilemap[1][y][x]==5){
        _tilemap[1][y][x]=0;
        _tilemapSprite[1][y][x]=NULL;
        std::cout<<"borrado SPRITE de mapa"<<std::endl;
        return true;
    }else{
      std::cout<<"borrado SPRITE de mapa mal"<<std::endl;
      return false;
    }
  }
  int getid(){return idmovido;}
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
  int idmovido=0;
  

};

#endif