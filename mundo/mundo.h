#ifndef MUNDO_H
#define MUNDO_H

#pragma once
#include <string>
#include <iostream>
#include "states.h"
#include "Map.h"
#include "menu.h"
#include "Tile.h"
#include "jugador.h"
#include "bombas.h"
#include "dinosaurio.h"
#include "colisiones.h"
#include "ia.h"
#include "adn.h"

using namespace std;

class Mundo : public States {

  private:    
    static Mundo* jinstance;
    int dif=0;//dificultad
    int lvls=0;//numero de niveles
    int lvlactual=0;//nivel en el que estamos
    int play=0;//numero de jugadores
    int modo=0;//modo de juego
    std::vector<Map*> mapas;//vector de mapas para jugar
    Tile* hud1;//el hud
    Tile* hud2;//el hud

    bool nueva=false;//controla la nueva partida
    bool adnscreados=false;
    bool dinoscreados=false;
    bool colisiones=false;
    std::vector<Dinosaurio*> dinosaurios;
    std::vector<Adn*> adns;//array de adns(seguramente modificcable)
    sf::Clock temporizador;
    //Jugador//
    Jugador* jugador1;
    Jugador* jugador2;
    /////Control de las bombas y explosiones/////
    std::vector<Bomba> totalBombas;
    std::vector<sf::Sprite> totalExplosiones;
    std::vector<float> tiemposBomba;
    std::vector<float> tiemposExplosiones;
    //Vector que almacena todos los sprites para comprobar las colisiones.
    std::vector<sf::Sprite*> todoSprites;

    int _cont = 0; // Contador de iteraciones del juego
  public:
    void Inicializar();
    static Mundo* Instance();
    void Event(sf::Event event,sf::RenderWindow &window);
    void Update(sf::RenderWindow &window);
    void Draw(sf::RenderWindow &window);
    void renicio();
    void finjuego();
    void crearAdns(Map* m,int tot);
    void crearDinos(Map* m,int tot);

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
    void move_dinos();



};

#endif