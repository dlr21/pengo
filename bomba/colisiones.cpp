#include "colisiones.h"
#include <iostream>

void Colisiones::crearColisiones(sf::Sprite &jugador,std::vector<sf::Sprite*> todoSprites, int direccion, int velocidad,float time, Jugador* j)
{
  bool movido=false;
      for(unsigned int i = 0;i < todoSprites.size();i++)
      {
        //Ha encontrado un objeto del vector con el que esta colisionando actualmente.
        if(jugador.getGlobalBounds().intersects(todoSprites[i]->getGlobalBounds()))
            {
              std::cout<<"colision bloque"<<std::endl;
              j->setColision(true);
              //Contrarestar velocidad en la direccion en la que esta yendo.
                          j->setkx(0);
                          j->setky(0);
                          switch (direccion)
                          {
                          //Arriba
                          case 0:
                              j->setky(j->getVelocidad());
                              movido=true;
                              break;
                          //Abajo
                          case 1:
                              j->setky(-j->getVelocidad());
                              movido=true;
                              break;
                          //Derecha
                          case 2:
                              j->setkx(-j->getVelocidad());
                              movido=true;
                              break;
                          //Izquierda
                          case 3:
                              j->setkx(j->getVelocidad());
                              movido=true;
                              break;
                          }
                          
                          jugador.move(j->getkx()*time,j->getky()*time);
                          jugador.move(0,0);
            }
      }
      if(!movido)j->setColision(false);
}

void Colisiones::update(sf::Clock &temporizador,std::vector<Dinosaurio*> &dinosaurios,Jugador &jugador,std::vector<sf::Sprite> &totalExplosiones,Map &mapa,  std::vector<sf::Sprite*> &todoSprites,std::vector<sf::Sprite*> &paredesSprites, float time)
{
  sf::Sprite**** mpSprite = mapa.gettilemapSprite();
  int*** tilemap= mapa.gettilemap();
  int lay=mapa.getnumlayers();
  int hei=mapa.getheight();
  int wid=mapa.getwidth();
    /*for(unsigned int j = 0;j < dinosaurios.size();j++)
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
            jugador.sumaPuntos();
          }
        }
      }
    }*/

      /*for(unsigned int j = 0;j < paredesSprites.size();j++){
        //JUGADOR CON PARED
        if(jugador.getSprite()->getGlobalBounds().intersects(paredesSprites[j]->getGlobalBounds()))
        {
          
        }

      }*/



      for(unsigned int j = 0;j < dinosaurios.size();j++)
    {
      //JUGADOR CON SNOBEE
      if(jugador.getSprite()->getGlobalBounds().intersects(dinosaurios[j]->getSprite()->getGlobalBounds()))
      {
        std::cout<<"colision con snobe"<<endl;
        if(jugador.getempujon()){
          dinosaurios[j]->modifyVida();
          if(dinosaurios[j]->getVida() == 0)
          {
            for(unsigned int a = 0;a < todoSprites.size();a++){
              if(todoSprites[a]==dinosaurios[j]->getSprite()){
                todoSprites.erase(todoSprites.begin() + a);
              }
            }
            dinosaurios.erase(dinosaurios.begin() + j);
            jugador.sumaPuntos();
          }
        }else if(jugador.getInvencibilidad() == -1 || temporizador.getElapsedTime().asSeconds() - jugador.getInvencibilidad() > 2)
        {
          jugador.quitarVidas();
          std::cout << jugador.getVidas() << std::endl;
          jugador.setInvencibilidad(temporizador.getElapsedTime().asSeconds());
        }
      }
    }

    /*for(unsigned int l=0; l<lay;l++){
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
      }*/
  
}
