#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/config.h"
#include "ej_modulos/Tile.h"
#include "mapa/Map.h"
//#include "menu/menu.h"
#include "mundo/mundo.h"
#include "bomba/bombas.h"
#include "bomba/colisiones.h"
#include "maquina/contexto.h"
#include "SFML/Graphics.hpp"
#include <time.h>

int main() {


  sf::RenderWindow window(sf::VideoMode(640, 480),"P0. Fundamentos de los Videojuegos. DCCIA");
  window.setFramerateLimit(60);
  //Creamos una ventana
    Contexto* game=Contexto::Instance();
    game->Inicializar();
    game->ChangeState(Mundo::Instance());   

    sf::Clock clock;
    sf::Time timeStartUpdate=clock.getElapsedTime();

     
    //Bucle del juego
      while (window.isOpen()) {
          while (game->Running()){
                      sf::Event event;
                        while(window.pollEvent(event)){
                          game->Event(event,window);
                        }
                      game->Update(window);  
                      game->Draw(window);              
            if(!window.isOpen())game->Quit();
            }
          
      }
    return 0;
}