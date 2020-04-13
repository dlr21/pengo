#include <SFML/Graphics.hpp>
#include <iostream>
#include "bombas.h"
#include "colisiones.h"
#include "jugador.h"

#include "include/config.h"

#define kVel 5
#define tiempoBomba 5
#define numJugadores 1


int main() {
  //Creamos una ventana
  sf::RenderWindow window(sf::VideoMode(640, 480), "P0. Fundamentos de los Videojuegos. DCCIA");

  //Creamos un temporizador.
  sf::Clock temporizador;

  //Creamos una instancia de la clase colisiones.
  Colisiones colisiones;

  //Vectores que controlan las bombas/explosiones y sus respectivos tiempos de activacion.
  std::vector<Bomba> totalBombas;
  std::vector<sf::Sprite> totalExplosiones;
  std::vector<float> tiemposBomba;
  std::vector<float> tiemposExplosiones;

  Jugador jugador(numJugadores);
  sf::Sprite sprite = jugador.getSprite();

  //Bucle del juego
  while (window.isOpen()) {
    //Bucle de obtención de eventos
    sf::Event event;
    
    //Detectamos si ya ha pasado la cantidad de tiempo suficiente para que explote una bomba.
    if(tiemposBomba.size() > 0 && temporizador.getElapsedTime().asSeconds() - tiemposBomba[0] >= tiempoBomba)
    {
      //Nos guardamos las explosiones generadas por la bomba que lleva mas tiempo puesta.
      std::vector<sf::Sprite> aux = totalBombas[0].GenerarExplosion();
      for(unsigned int i = 0;i < aux.size();i++)
      {
        totalExplosiones.push_back(aux[i]);
      }

      //Nos guardamos el tiempo en el que ha producido la explosion.
      tiemposExplosiones.push_back(temporizador.getElapsedTime().asSeconds());

      //Borramos la bomba que lleva mas tiempo puesta.
      totalBombas.erase(totalBombas.begin());
      //Borramos el tiempo que controla la primera bomba.
      tiemposBomba.erase(tiemposBomba.begin());
    }

    
    //Ha pasado un segundo desde que se activa la explosion.
    if(tiemposExplosiones.size() > 0 && temporizador.getElapsedTime().asSeconds() - tiemposExplosiones[0] >= 1)
    {
      //Borramos explosion mas antigua y su tiempo.
      totalExplosiones.erase(totalExplosiones.begin(),totalExplosiones.begin()+5);
      tiemposExplosiones.erase(tiemposExplosiones.begin());
    }

    while (window.pollEvent(event)) {

      switch (event.type) {

      //Si se recibe el evento de cerrar la ventana la cierro
      case sf::Event::Closed:
        window.close();
        break;

      //Se pulsó una tecla, imprimo su codigo
      case sf::Event::KeyPressed:

        //Verifico si se pulsa alguna tecla de movimiento
        switch (event.key.code) {

        //Mapeo del cursor
        case sf::Keyboard::Right:
          sprite.setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
          //Escala por defecto
          sprite.setScale(0.5, 0.5);
          sprite.move(kVel, 0);
          colisiones.crearColisiones(sprite,totalExplosiones,0,kVel);
          colisiones.colisionesBombas(sprite,totalBombas,0,kVel);
          break;

        case sf::Keyboard::Left:
          sprite.setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
          //Reflejo vertical
          sprite.setScale(-0.5, 0.5);
          sprite.move(-kVel, 0);
          colisiones.crearColisiones(sprite,totalExplosiones,1,kVel);
          colisiones.colisionesBombas(sprite,totalBombas,1,kVel);
          break;

        case sf::Keyboard::Up:
          sprite.setTextureRect(sf::IntRect(0 * 75, 3 * 75, 75, 75));
          sprite.move(0, -kVel);
          colisiones.crearColisiones(sprite,totalExplosiones,2,kVel);
          colisiones.colisionesBombas(sprite,totalBombas,2,kVel);
          break;

        case sf::Keyboard::Down:
          sprite.setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75));
          sprite.move(0, kVel);
          colisiones.crearColisiones(sprite,totalExplosiones,3,kVel);
          colisiones.colisionesBombas(sprite,totalBombas,3,kVel);
          break;

        case sf::Keyboard::Space:
        {
            //Nos guardamos el segundo exacto en el que se pone la bomba.
            tiemposBomba.push_back(temporizador.getElapsedTime().asSeconds());
            //Creamos una instancia de bomba.
            Bomba bomba(sprite.getPosition().x, sprite.getPosition().y);
            bomba.setPropietario(1);
            //Lo añadimos al vector de bombas.
            totalBombas.push_back(bomba);
            
            break;
        }

        //Tecla ESC para salir
        case sf::Keyboard::Escape:
          window.close();
          break;

        //Cualquier tecla desconocida se imprime por pantalla su código
        default:
          std::cout << event.key.code << std::endl;
          break;
        }
      }
    }
    
    window.clear();
    //Mostramos todas las bombas que hay en el mapa.
    if(totalBombas.size() > 0)
    {
      for(unsigned int i = 0;i < totalBombas.size();i++)
      {
        window.draw(totalBombas[i].getBomba());
      }
    }

    //Mostramos todas las explosiones que hay en el mapa.
    if(totalExplosiones.size() > 0)
    {
      for(unsigned int i = 0;i < totalExplosiones.size();i++)
      {
        window.draw(totalExplosiones[i]);
      }
    }

    window.draw(sprite);
    window.display();
  }

  return 0;
}