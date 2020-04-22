#ifndef MUNDO_H
#define MUNDO_H

#pragma once
#include <string>
#include <iostream>
#include "states.h"
#include "Map.h"
#include "Tile.h"
#include "jugador.h"
#include "dinosaurio.h"
#include "colisiones.h"
#include "ia.h"
#include "adn.h"

using namespace std;

class Mundo : public States {
  private:    
    static Mundo* jinstance;

    int vidas=3;
    int dif;//dificultad
    int lvls;//numero de niveles
    int lvlactual=0;//nivel en el que estamos
    int play;//numero de jugadores
    int snototales;
    int snovivos;
    int snodurmiendo;
    int dirbloque;
    int prepuntos;
    std::vector<Map*> mapas;//vector de mapas para jugar
    Tile* hud1;//el hud
    Tile* hud2;//el hud
    bool pulsada;//event de uno en uno
    bool nueva=true;//controla la nueva partida
    bool adnscreados;
    bool dinoscreados;
    bool colisiones;
    bool moverse;
    bool aturdidos=false;
    bool diamant=false;
    std::vector<Dinosaurio*> dinosaurios;
    std::vector<Adn*> adns;//array de adns(seguramente modificcable)
    sf::Clock temporizador;
    //Jugador//
    Jugador* jugador1;
    Jugador* jugador2;
    std::vector<sf::Sprite> totalExplosiones;
    std::vector<float> tiemposBomba;
    std::vector<float> tiemposExplosiones;
    //Vector que almacena todos los sprites para comprobar las colisiones.
    std::vector<sf::Sprite*> todoSprites;
    std::vector<sf::Sprite*> paredesSprites;
    int _cont = 0; // Contador de iteraciones del juego
    sf::Sprite* bloqueadeslizar;
    sf::Clock clock;
    IA* ia;
    float waiteo=3;
    float control=0;


  public:
    void Inicializar();
    static Mundo* Instance();
    void Event(sf::Event event,sf::RenderWindow &window, float time);
    void Update(sf::RenderWindow &window, float time);
    void Draw(sf::RenderWindow &window);
    void renicio();
    void finjuego();
    void crearAdns(Map* m,int tot);
    void crearDinos(Map* m,int tot);
    void reinicionivel();
    void setcontrol(float a){control=a;}
    int getActivos(){
      int cont=0;
          for(unsigned int i=0;i<dinosaurios.size();i++){
            if(dinosaurios[i]->getactivo())cont++;
          }
      return cont;
    }
    void borraradns(){
        for(unsigned int i=0;i<adns.size();i++){
          std::cout<<"adn delete"<<endl;
          delete adns[i];
          adns[i]=NULL;
        }
        adns.clear();
    }
    void borrardinos(){
        for(unsigned int i=0;i<dinosaurios.size();i++){
          std::cout<<"dino delete"<<endl;
          delete dinosaurios[i];
          dinosaurios[i]=NULL;
        }
        dinosaurios.clear();
    }
    void borrarcolisiones(){
        for(unsigned int i=0;i<todoSprites.size();i++){
          std::cout<<"colisiones delete"<<endl;
          delete todoSprites[i];
          todoSprites[i]=NULL;
        }
        todoSprites.clear();
    }
    void borrarmapas(){
      for(unsigned int i=0;i<mapas.size();i++){
        delete mapas[i];
        mapas[i]=NULL;
      }
      mapas.clear();
    }
    void todosno(float times){
      int activados=0;
      control+=times;
      for (unsigned int i = 0; i < dinosaurios.size(); i++)
      {
          if(activados<2 && control>=waiteo && !dinosaurios[i]->getactivo()){
            dinosaurios[i]->setactivo(true);
            control=0;
          }
          if(dinosaurios[i]->getactivo())activados++;

          if(activados==2){
            jugador1->setmatando(false);
            control=0;
          }
      } 
      
      if(dinosaurios.size()<=0){
        mapas[lvlactual]->terminar();
        std::cout<<"GANASMAPA"<<endl;
      }
    }
    void borradetodoSprites(sf::Sprite* s){
      std::cout<<"borrado?"<<std::endl;
              for(unsigned int a = 0;a < todoSprites.size();a++){
                if(todoSprites[a]==s){
                  todoSprites.erase(todoSprites.begin() + a);
                }
              }
    }
    void aSprites(sf::Sprite* d){
      todoSprites.push_back(d);
    }
    void aturdir(){
      for(unsigned a=0;a<dinosaurios.size();a++){
        std::cout<<dinosaurios[a]->getposimapax()<<" "<<dinosaurios[a]->getposimapay()<<std::endl;
        if (dinosaurios[a]->getactivo() && !dinosaurios[a]->getaturdido() && ((dinosaurios[a]->getposimapax()==1) || (dinosaurios[a]->getposimapax()==13) || (dinosaurios[a]->getposimapay()==1) || (dinosaurios[a]->getposimapay()==15)))
        {
          dinosaurios[a]->setaturdido(true);
          std::cout<<"aturdido"<<std::endl;
         }          
        }
    }
    void diamantitos(){
      if(!diamant){
        if(mapas[lvlactual]->tresenralla()){
          jugador1->maspuntos(30);//DA AL JUGADOR 300PUNTOS
          aturdir();
          diamant=true;
        }
      }
    }

};

#endif