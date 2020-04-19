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
    int dif;//dificultad
    int lvls;//numero de niveles
    int lvlactual=0;//nivel en el que estamos
    int play;//numero de jugadores
    int snototales;
    int snovivos;
    int snodurmiendo;
    int dirbloque;
    std::vector<Map*> mapas;//vector de mapas para jugar
    Tile* hud1;//el hud
    Tile* hud2;//el hud
    bool pulsada;//event de uno en uno
    bool nueva;//controla la nueva partida
    bool adnscreados;
    bool dinoscreados;
    bool colisiones;
    bool moverse;
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
    void todosno(){
      int activados=0;
      for (unsigned int i = 0; i < dinosaurios.size(); i++)
      {
        if (activados<2){
            dinosaurios[i]->setactivo(true);
            activados++;
        } 
      }
      if(dinosaurios.size()<=0){
        mapas[lvlactual]->terminar();
        std::cout<<"ganasmapa"<<endl;
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
};

#endif