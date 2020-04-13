#include "colisiones.h"
#include <iostream>

void Colisiones::crearColisiones(sf::Sprite &jugador,std::vector<sf::Sprite*> objetos, int direccion, int velocidad)
{
      for(unsigned int i = 0;i < objetos.size();i++)
      {
        //Ha encontrado un objeto del vector con el que esta colisionando actualmente.
        if(jugador.getGlobalBounds().intersects(objetos[i]->getGlobalBounds()))
            {
              //Contrarestar velocidad en la direccion en la que esta yendo.
                switch (direccion)
                {
                  //Arriba
                  case 0:
                    jugador.move(0,velocidad);
                    break;
                  //Abajo
                  case 1:
                    jugador.move(0,-velocidad);
                    break;
                  //Derecha
                  case 2:
                    jugador.move(-velocidad, 0);
                    break;
                  //Izquierda
                  case 3:
                  jugador.move(velocidad, 0);
                    break;
                }
            }
      }
}

void Colisiones::colisionesBombas(Jugador &jugador,std::vector<Bomba> &bombas, int direccion)
{
  for(unsigned int i = 0;i < bombas.size();i++)
  {
    //Ha encontrado la bomba con la que esta colisionando.
    if(bombas[i].getBomba().getGlobalBounds().intersects(jugador.getSprite()->getGlobalBounds()))
    {
      std::cout << "He entrado 1" << std::endl;
      if(bombas[i].getColision() == true)
      {
        std::cout << "He entrado 2" << std::endl;
      switch (direccion)
              {
                //Arriba
                case 0:
                  jugador.mover(1);
                  break;
                //Abajo
                case 1:
                  jugador.mover(0);
                  break;
                //Izquierda
                case 2:
                  jugador.mover(3);
                  break;
                //Derecha
                case 3:
                  jugador.mover(2);
                  break;
              }
      }
    }
    else
    {
      //Si no colisiona con una bomba pero esa bomba es suya y aun no tiene colision, se la activamos.
      if(bombas[i].getPropietario() == 1 && bombas[i].getColision() == false)
      {
        std::cout << bombas[i].getColision() << std::endl;
        std::cout << "Acabo de activar una colision" << std::endl;
        std::cout << bombas[i].setColision() << std::endl;
      }
    }
  }
}


void Colisiones::update(sf::Clock &temporizador,std::vector<Dinosaurio*> &dinosaurios,Jugador &jugador,std::vector<sf::Sprite> &totalExplosiones,Map &mapa,  std::vector<sf::Sprite*> &todoSprites)
{
  sf::Sprite**** mpSprite = mapa.gettilemapSprite();
  int*** tilemap= mapa.gettilemap();
  int lay=mapa.getnumlayers();
  int hei=mapa.getheight();
  int wid=mapa.getwidth();

  for(unsigned int i = 0;i < totalExplosiones.size();i++)
  {
    //EXPLOSION DINOSAURIOS
    for(unsigned int j = 0;j < dinosaurios.size();j++)
    {
      if(dinosaurios[j]->getSprite()->getGlobalBounds().intersects(totalExplosiones[i].getGlobalBounds()))
      {
        if(dinosaurios[j]->getInvencibilidad() == -1 || temporizador.getElapsedTime().asSeconds() - dinosaurios[j]->getInvencibilidad() > 1)
        {
          dinosaurios[j]->setInvencibilidad(temporizador.getElapsedTime().asSeconds());
          dinosaurios[j]->modifyVida();
          if(dinosaurios[j]->getVida() == 0)
          {
            for(unsigned int a = 0;a < todoSprites.size();a++){
              if(todoSprites[a]==dinosaurios[j]->getSprite()){
                todoSprites.erase(todoSprites.begin() + a);
              }
            }
            dinosaurios.erase(dinosaurios.begin() + j);
          }
        }
      }
    }
    //EXPLOSION JUGADOR
    if(jugador.getSprite()->getGlobalBounds().intersects(totalExplosiones[i].getGlobalBounds()))
    {
      //El jugador tiene invencibilidad de un segundo cuando colisiona con una explosion.
      if(jugador.getInvencibilidad() == -1 || temporizador.getElapsedTime().asSeconds() - jugador.getInvencibilidad() > 1)
      {
        jugador.quitarVidas();
        std::cout << jugador.getVidas() << std::endl;
        jugador.setInvencibilidad(temporizador.getElapsedTime().asSeconds());
      }
    }
    //EXPLOSION CON ROCAS
    for(unsigned int l=0; l<lay;l++){
        for( unsigned int y=0; y<hei;y++){
          for(unsigned int x=0; x<wid;x++){
            int gid=tilemap [l][y][x]-1;
            if(gid==2 && mpSprite[l][y][x]->getGlobalBounds().intersects(totalExplosiones[i].getGlobalBounds())){//GID = PIEDRAS
              std::cout << "Rompo una piedra" << std::endl;
              mapa.setTileMapa(l,y,x,2);
                  for(unsigned int a = 0;a < todoSprites.size();a++){
                    if(todoSprites[a]==mpSprite[l][y][x]){
                      todoSprites.erase(todoSprites.begin()+a);
                    }
                  }
              mapa.gettilemapSprite()[l][y][x]->setTextureRect(sf::IntRect(32,32,32,32));
            }
          }
        }
      }
  }
}
