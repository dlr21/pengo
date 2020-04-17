#include "Map.h"
#include <iostream>


Map::Map(string s,int puntos) {
  finalizado=false;
  puntosfin=puntos;
  //PARA EL MAPA
  std::cout << "Creando mi Map..."<< endl ;
  TiXmlDocument mapa(s);
    bool loadOkay=mapa.LoadFile();
      std::cout << "load.."<< endl ;
    if (loadOkay)
    {
      std::cout<<"cargado"<< endl;
      }
      else{std::cout<<"no cargado";
      }
  //datos
    TiXmlElement * data= mapa.FirstChildElement("map");
    data->QueryIntAttribute("width",&_width);
    std::cout<<_width<<endl;
      data->QueryIntAttribute("height",&_height);
      std::cout<<_height<<endl;
        data->QueryIntAttribute("tilewidth",&_tilewidth);
        std::cout<<_tilewidth<<endl;
          data->QueryIntAttribute("tileheight",&_tileheigh);
          std::cout<<_tileheigh<<endl;
  //nombremapa
  TiXmlElement *value=data->FirstChildElement("properties")->FirstChildElement("property");
    value->QueryStringAttribute("value",&_nombremapa);
          std::cout<<_nombremapa<<endl;

              if (!fuente.loadFromFile("resources/arial.ttf"))
              {              
                    std::cout << "Error: Could not display font" << std::endl;
              }    
              // Asignamos la cadena al texto
              texto.setString(_nombremapa);
              // Asignamos la fuente que hemos cargado al texto
              texto.setFont(fuente);
              // Tamaño de la fuente
              texto.setCharacterSize(20);
              // Posición del texto
              texto.setPosition(530,20);
              texto.setColor(sf::Color::Red);
              texto.setScale(1.5,1.5);
  //image
  std::cout<<"img"<<endl;
  TiXmlElement *img=data->FirstChildElement("tileset")->FirstChildElement("image");
  const char *filename=img->Attribute("source");
  std::cout<<filename<<endl;


  //capas
    TiXmlElement *layer = data->FirstChildElement("layer");
    _numlayers=0;
      while (layer)
      {
        _numlayers++;
        layer=layer->NextSiblingElement("layer");
          std::cout<<_numlayers<<endl;
      }


  std::cout<<"prereserva"<<endl;

  //reserva memoria
  reservarMemoria(_numlayers);
  _tilesettexture.loadFromFile("resources/bloques.png");
  std::cout<<"reservado"<<endl;
  //cargando los gids
  TiXmlElement *aux;
    for(int l=0; l<_numlayers;l++){
      aux=data->FirstChildElement("layer");
        for(int x=0; x<l;x++){
          aux=aux->NextSiblingElement("layer");
        }
        std::cout<<l<<endl;
        aux=aux->FirstChildElement("data")->FirstChildElement("tile");
        for(int y=0; y<_height;y++){
          for(int x=0; x<_width;x++){
            aux->QueryIntAttribute("gid", &_tilemap[l][y][x]);
            //siguiente tile
            aux=aux->NextSiblingElement("tile");
          }
        }
    }
      std::cout<<"gids";
      //crear matriz sprites del mapa 
      for(int l=0; l<_numlayers;l++){
              std::cout<<"guarda capas"<<endl;
        for(int y=0; y<_height;y++){
          std::cout<<std::endl;
          for(int x=0; x<_width;x++){
            int gid=_tilemap [l][y][x];
            std::cout<<gid;
            if(gid>0){
              gid--;
              _tilemapSprite[l][y][x]=new sf::Sprite(_tilesettexture,{0+(gid*32),0+(0*32),32,32});
              _tilemapSprite[l][y][x]->setOrigin(16,16);
              _tilemapSprite[l][y][x]->setPosition(112+(x*_tilewidth),64+(y*_tileheigh));
            }else{
              _tilemapSprite[l][y][x]==NULL;
            }
          }
        }
      }
      std::cout<<"arraysprites"<<endl;
  }
  /*TiXmlElement *cambio(int l, TiXmlElement *layer){
      for(int i=0;i<l;i++){
        layer=layer->NextSiblingElement("layer");
      }
    return layer;
  }*/

 sf::Sprite* Map::gettilemapSprite(int l, int y, int x){
  return _tilemapSprite[l][y][x];
}


Map::~Map(){

  std::cout<<"gids"<<endl;

  for(int l=0;l<_numlayers;l++){
    for (int y= 0; y < _height; y++){

      delete[] _tilemap[l][y];
    }
    delete[] _tilemap[l];
  }
  delete[] _tilemap;

  std::cout<<"sprites"<<endl;

    for(int i=0;i<_numlayers;i++){
      for(int y=0;y<_height;y++){
        for(int x=0;x<_width;x++){
          if(_tilemapSprite[i][y][x]!=NULL){
          _tilemapSprite[i][y][x]=NULL;
            delete[] _tilemapSprite[i][y][x];
          }
        }
        delete[] _tilemapSprite[i][y];
      }
      delete[] _tilemapSprite[i];
    }
  delete[] _tilemapSprite;


}

void Map::draw(sf::RenderWindow& window){
 for(int l=0; l<_numlayers;l++){
    for(int y=0; y<_height;y++){
      for(int x=0; x<_width;x++){
        if(_tilemapSprite[l][y][x]!=NULL){
          window.draw(*(_tilemapSprite[l][y][x]));
        }
      }
    }
  }
  window.draw(texto);
}
void Map::setactivelayer(int layer){
  _activelayer=layer;
}
void Map::Update(sf::RenderWindow &window){

}
void Map::reservarMemoria(int _numlayers){
    //reservando memoria para mapa
      std::cout<<"reserva ints";

    _tilemap=new int**[_numlayers];

  for(int i=0;i<_numlayers;i++){
    _tilemap[i]=new int*[_height];
  }
  for(int l=0;l<_numlayers;l++){
    for (int y= 0; y < _height; y++){
    _tilemap[l][y]=new int[_width];
    }
  }
  std::cout<<"reserva sprites";
  //reserva memoria Sprites
  std::cout<<_numlayers<<endl;
  _tilemapSprite=new sf::Sprite***[_numlayers];

  std::cout<<"AQUI NO LLEGA";
  for(int i=0;i<_numlayers;i++){
    _tilemapSprite[i]=new sf::Sprite**[_height];
  }
  for(int i=0;i<_numlayers;i++){
    for(int y=0;y<_height;y++){
      _tilemapSprite[i][y]=new sf::Sprite*[_width];
      for(int x=0;x<_width;x++){
        _tilemapSprite[i][y][x]=new sf::Sprite();
      }
    }
  }
}

sf::Sprite* Map::empujado(sf::Sprite* j, int dir){

  //0 arriba 1 abajo 2 derecha 3 izq
  int x=(j->getPosition().x-112)/32;
  int y=(j->getPosition().y-64)/32;

  std::cout<< x<<" "<<y<<endl;

  if(dir==0){
    std::cout<< x<<" "<<y-1<<endl;
    if(y-1>-1 && (_tilemap[1][y-1][x]==5 || _tilemap[1][y-1][x]==6) ){
      std::cout<<"sigue"<<endl;
      return _tilemapSprite[1][y-1][x];

    }else{
      return NULL;
    }
  }else if(dir==1){
    std::cout<<x<<" "<<y+1<<endl;
     if( y+1<18 && (_tilemap[1][y+1][x]==5 || _tilemap[1][y+1][x]==6) ){

      return _tilemapSprite[1][y+1][x];
    }else{
      return NULL;
    }
  }else if(dir==2){
    std::cout<<x+1<<" "<<y<<endl;
    if( x+1<16 && (_tilemap[1][y][x+1]==5 || _tilemap[1][y][x+1]==6) ){

      return _tilemapSprite[1][y][x+1];
    }else{
      return NULL;
    }
  }else if(dir==3){
    std::cout<<x-1<<" "<<y<<endl;
    if( x-1>-1 && (_tilemap[1][y][x-1]==5 || _tilemap[1][y][x-1]==6) ){

      return _tilemapSprite[1][y][x-1];
    }else{
      return NULL;
    }
  }

}

void Map::anadirVector(std::vector<sf::Sprite*> &vectorS){
  for(unsigned int l=0; l<_numlayers;l++){
        for( unsigned int y=0; y<_height;y++){
          for(unsigned int x=0; x<_width;x++){
            int gid=_tilemap [l][y][x];
            if(gid == 0 || gid == 1 || gid == 2 || gid == 3 || gid == 4 || gid == 5 ||gid == 6 )
            {
              vectorS.push_back(_tilemapSprite[l][y][x]);
            }
          }
        }
      }
}
void Map::anadirParedes(std::vector<sf::Sprite*> &vectorS){
  for(unsigned int l=0; l<_numlayers;l++){
        for( unsigned int y=0; y<_height;y++){
          for(unsigned int x=0; x<_width;x++){
            int gid=_tilemap [l][y][x];
            if(gid == 0 || gid == 1 || gid == 2 || gid == 3 || gid == 4 )
            {
              vectorS.push_back(_tilemapSprite[l][y][x]);
            }
          }
        }
      }
}

void Map::deslizarbloque(sf::Sprite* s, int j, float time){

    kVelx=0;
    kVely=0;
    switch (j)
    {
    //Arriba
    case 0:
         kVely=-kVel*time;
        
        break;
    //Abajo
    case 1:
        kVely=kVel*time;
        
        break;
    //Derecha
    case 2:
        kVelx=kVel*time;
        
        break;
    //Izquierda
    case 3:
        kVelx=-kVel*time;
        
        break;
    }

    s->move(kVelx,kVely);
    s->move(0,0);
  
}