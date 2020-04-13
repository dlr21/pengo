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

  _tilesettexture.loadFromFile("resources/tilebase.png");
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

      int cont=0;
      std::cout<<"gids";
      //crear matriz sprites del mapa 
      for(int l=0; l<_numlayers;l++){
              std::cout<<"guarda capas"<<endl;
        for(int y=0; y<_height;y++){
          for(int x=0; x<_width;x++){
            int gid=_tilemap [l][y][x]-1;
            if(gid>-1){
              _tilemapSprite[l][y][x]=new sf::Sprite(_tilesettexture,{0+(gid*32),0+(gid*32),32,32});
              _tilemapSprite[l][y][x]->setPosition(112+(x*_tilewidth),64+(y*_tileheigh));
              cont++;
            }
          }
        }
      }


      std::cout<< cont;
      std::cout<<"arraysprites"<<endl;
      

  }
  /*TiXmlElement *cambio(int l, TiXmlElement *layer){
      for(int i=0;i<l;i++){
        layer=layer->NextSiblingElement("layer");
      }
    return layer;
  }*/

sf::Sprite Map::gettilemapSprite(int l, int y, int x){
  return *_tilemapSprite[l][y][x];
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
       // if(_tilemapSprite[_activelayer][y][x]!=NULL){
          window.draw(*(_tilemapSprite[l][y][x]));
        //}
      }
    }
  }
  window.draw(texto);
}
void Map::setactivelayer(int layer){
  _activelayer=layer;
}
void Map::Update(sf::Event event,sf::RenderWindow &window){

  switch (event.type) {
              case sf::Event::KeyPressed:
              ///Verifico si se pulsa alguna tecla de movimiento
              switch (event.key.code) {
              //Cualquier tecla desconocida se imprime por pantalla su código

               case sf::Keyboard::Return:
                  finalizado=true;
                default:
                  std::cout <<  " code " << event.key.code << std::endl;
                break;
              }
  }

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
  _tilemapSprite=new sf::Sprite***[_numlayers];///////////////////terminate called after throwing an instance of 'std::bad_array_new_length'
  //////////////////////////////      what():  std::bad_array_new_length                            Aborted (core dumped)

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

void Map::liberar(){



}

void Map::anadirVector(std::vector<sf::Sprite*> &vectorS)
{
  for(unsigned int l=0; l<_numlayers;l++){
        for( unsigned int y=0; y<_height;y++){
          for(unsigned int x=0; x<_width;x++){
            int gid=_tilemap [l][y][x]-1;
            if(gid == 0 || gid == 2) //Si son piedras o paredes, lo metemos en el sprite de las colisiones.
            {
              vectorS.push_back(_tilemapSprite[l][y][x]);
            }
          }
        }
      }
}