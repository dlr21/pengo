#include "colisiones.h"
#include <iostream>

void Colisiones::crearColisiones(sf::Sprite &jugador,std::vector<sf::Sprite*> todoSprites, int direccion, int velocidad,float time, Jugador* j){
   j->setmovido(false);
      for(unsigned int i = 0;i < todoSprites.size();i++)
      {
        //Ha encontrado un objeto del vector con el que esta colisionando actualmente.
        if(jugador.getGlobalBounds().intersects(todoSprites[i]->getGlobalBounds())){
              std::cout<<"colision bloque"<<std::endl;
                          j->setColision(true);
                          jugador.setPosition(j->getposimapax()*32+112,j->getposimapay()*32+64);
                            if(jugador.getGlobalBounds().intersects(todoSprites[i]->getGlobalBounds())){
                              jugador.setPosition(112+32, 64+32);
                            }
                          j->setmovido(true);
            }
      }
      if(!j->getmovido())j->setColision(false);
}

void Colisiones::update(sf::Clock &temporizador,sf::Sprite* deslizado,std::vector<Dinosaurio*> &dinosaurios,Jugador &jugador,std::vector<sf::Sprite> &totalExplosiones,Map &mapa,  std::vector<sf::Sprite*> &todoSprites,std::vector<sf::Sprite*> &paredesSprites, float time){
  sf::Sprite**** mpSprite = mapa.gettilemapSprite();
  int*** tilemap= mapa.gettilemap();
  int lay=mapa.getnumlayers();
  int hei=mapa.getheight();
  int wid=mapa.getwidth();

    //SNOBEE CON BLOQUEDESLIZADO
    if(deslizado!=NULL && jugador.getmoviendo()==true){
      for(unsigned int j = 0;j < dinosaurios.size();j++)
      {
        if(dinosaurios[j]->getSprite()->getGlobalBounds().intersects(deslizado->getGlobalBounds()) && dinosaurios[j]->getactivo())
        {
          if(dinosaurios[j]->getInvencibilidad() == -1 || temporizador.getElapsedTime().asSeconds() - dinosaurios[j]->getInvencibilidad() > 1)
          {
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
              jugador.setmatando(true);
            }
          }
        }
      }
      for(unsigned int j = 0;j < todoSprites.size();j++)//BLOQUE MOVIDO CON BLOQUE PARADO
      {
        if(todoSprites[j]->getGlobalBounds().intersects(deslizado->getGlobalBounds()) && deslizado!=todoSprites[j]){
          int x=deslizado->getPosition().x-112;
          if(x%32<=16)x=x/32;
          if(x%32>16)x=(x/32)+1;
          int y=deslizado->getPosition().y-64;
          if(y%32<=16)y=y/32;
          if(y%32>16)y=(y/32)+1;
          std::cout<<x<<" "<<y<<endl;
          deslizado->setPosition(x*32+112,y*32+64);
          std::cout<<mapa.getid()<<"presetid"<<std::endl;
          mapa.setid(x,y);
          mapa.settilemapSprite(deslizado,x,y);
          jugador.setmoviendo(false);
        }
      }
    }
      
      for(unsigned int j = 0;j < dinosaurios.size();j++)
    {
      //JUGADOR CON SNOBEE
      if(jugador.getSprite()->getGlobalBounds().intersects(dinosaurios[j]->getSprite()->getGlobalBounds()) && dinosaurios[j]->getactivo())
      {
        if(!dinosaurios[j]->getaturdido()){
        std::cout<<"colision con snobe"<<endl;
          if(jugador.getInvencibilidad() == -1 || temporizador.getElapsedTime().asSeconds() - jugador.getInvencibilidad() > 2)
          {
            jugador.quitarVidas();
            jugador.setInvencibilidad(temporizador.getElapsedTime().asSeconds());
          }
        }else{
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
              jugador.setmatando(true);
            }
        }
      }
    }
}
