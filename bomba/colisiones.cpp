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
                          //std::cout<<j->getSprite()->getPosition().x+112<<" "<<j->getSprite()->getPosition().y+64<<std::endl;
                          jugador.setPosition(j->getposimapax()*32+112,j->getposimapay()*32+64);
                          //std::cout<<j->getposimapax()*32+112<<" "<<j->getposimapay()*32+64<<std::endl;
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
        if(dinosaurios[j]->getSprite()->getGlobalBounds().intersects(deslizado->getGlobalBounds()))
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
      }
      for(unsigned int j = 0;j < todoSprites.size();j++)
      {
        if(todoSprites[j]->getGlobalBounds().intersects(deslizado->getGlobalBounds()) && deslizado!=todoSprites[j]){
          mapa.settilemapSprite(deslizado,(deslizado->getPosition().x-112)/32,(deslizado->getPosition().y-64)/32);
          jugador.setmoviendo(false);
        }
      }
    }
      
      for(unsigned int j = 0;j < dinosaurios.size();j++)
    {
      //JUGADOR CON SNOBEE
      if(jugador.getSprite()->getGlobalBounds().intersects(dinosaurios[j]->getSprite()->getGlobalBounds()) && dinosaurios[j]->getactivo())
      {
        std::cout<<"colision con snobe"<<endl;
        if(jugador.getInvencibilidad() == -1 || temporizador.getElapsedTime().asSeconds() - jugador.getInvencibilidad() > 2)
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
