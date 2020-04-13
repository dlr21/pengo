// SFML libraries
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <sstream>
#include <chrono>
#include <cstdio>
#include <ctime>
#include "dinosaurio.h"


using namespace std;

// Posicion donde esta mirando el dinosaurio.
int pos_mirando = -1; // 0: Arriba | 1: Abajo | 2: Derecha | 3: Izquierda

// Contador para tener tiempo de invulnerabilidad cuando explote la bomba
std::clock_t inicio_contador;

// Programa mapa
int main(){
  sf::RenderWindow window(sf::VideoMode(640, 480), "Mapa prueba");

  // Cargar fuente
  sf::Font font;
  if (!font.loadFromFile("resources/OpenSans-Regular.ttf")){
    std::cerr << "Error cargando la fuente" << std::endl;
    exit(0);
  }

  // Cargo la imagen de la texturatura del dinosaurio
  sf::Texture dinosaurio_texture;
  if (!dinosaurio_texture.loadFromFile("resources/sprites.png")) {
    std::cerr << "Error cargando la imagen sprites.png";
    exit(0);
  }

  // Textura boom
  sf::Texture bomba_texture;
  if (!bomba_texture.loadFromFile("resources/boom.png")) {
    std::cerr << "Error cargando la imagen boom.png";
    exit(0);
  }

	// Creamos un objeto texto para mostrar la vida
	sf::Text vida_text;

	// Asignamos la fuente que hemos cargado al texto
	vida_text.setFont(font);

	// Tamaño de la fuente
	vida_text.setCharacterSize(20);

	// Posición del texto
	vida_text.setPosition(150, 100);

  // Tipo de dinosaurio
  int tipodino = 0; // 0: T-Rex | 1: Velociraptor | 2: Pterodactilo | 3: Triceratops

  // Crear dino clase de dinosaurio
  Dinosaurio dinosaurio(dinosaurio_texture);

  // Establecer caracteristicas del dinosaurio
  dinosaurio.setTipodino(tipodino); // Tipo de dinosaurio

  // Configuracion para la bomba  
  sf::Sprite boom(bomba_texture);
  boom.setTexture(bomba_texture);
  boom.setScale(sf::Vector2f(0.2,0.2));
  boom.setPosition(150, 200);
  sf::Vector2f posBoom = boom.getPosition(); // Posicion de la bomba
  sf::FloatRect tamanio = boom.getGlobalBounds(); // Entorno de la bomba

  // Bucle de todo el juego
  bool centinela_salto = false;
  while(window.isOpen()){
    sf::Event event;
    while(window.pollEvent(event)){
      // Si se cierra la ventana se cierra el juego
      if(event.type == sf::Event::Closed){
        window.close();
      }
    }
    
    window.clear();
    
    // COLISIONES
    sf::FloatRect dino_rect = dinosaurio.getHitbox(); // Entorno del dinosaurio
    
    // Ver si la hitbox del dinosaurio colisiona con la hitbox de la bomba
    if(boom.getGlobalBounds().intersects(dino_rect)){ 
      if(dinosaurio.getTipodino() == 3){ // Si es triceratops, puede mover la bomba
        if(pos_mirando == 0){ // Hacia arriba
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            posBoom.y = posBoom.y - 1; 
            boom.setPosition(posBoom.x, posBoom.y);
          }
        }
        if(pos_mirando==1){ // Hacia abajo
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            posBoom.y = posBoom.y + 1; 
            boom.setPosition(posBoom.x, posBoom.y);
          }
        }
        if(pos_mirando==2){ // Hacia la derecha
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            posBoom.x = posBoom.x + 1;
            boom.setPosition(posBoom.x, posBoom.y);
          }
        }
        if(pos_mirando==3){ // Hacia la izquierda
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            posBoom.x = posBoom.x - 1;
            boom.setPosition(posBoom.x, posBoom.y);
          }
        }
      }
      else{ // Si los demas dinosaurios tocan la bomba, se elimina una vida
        // Comprobar tiempo desde que ha tocado la bomba la primera vez. Se resta el tiempo desde que la toca por primera vez y justo en el momento de esta operacion.
        // std::clock() indica el momento de tiempo justo en el momento de la operacion. Se resta para comprobar si han pasado o no 1 segundo
        double duration = ( std::clock() - inicio_contador ) / (double) CLOCKS_PER_SEC; 
                                                                              
        if(duration >= 1){ // Si han pasado mas de 1 segundo desde que ha tocado la bomba y esta sobre ella, quita otro punto de vida
          inicio_contador = std::clock(); // Inicia el contador de tiempo para comprobar si han pasado mas de 1 segundo
          dinosaurio.modifyVida();
        }
      }
    }

    // Movimiento del dinosaurio
    // Centinela para que el jugador no mantenga pulsado el boton de salto
    // Si el jugador no pulsa el boton de espacio, el centinela se desactiva y permite la pulsacion
    // del espacio de nuevo
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) == false){
      centinela_salto = false;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
      pos_mirando = dinosaurio.marriba();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
      pos_mirando = dinosaurio.mabajo();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
      pos_mirando = dinosaurio.mderecha();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
      pos_mirando = dinosaurio.mizquierda();
    }
    // Escape para salir del juego
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
      window.clear();
      window.close();
      dinosaurio.~Dinosaurio();
    }
    // SALTO. Solo puede el pterodactilo
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (centinela_salto == false) && (dinosaurio.getTipodino() == 2)){
      dinosaurio.salto(pos_mirando);
      centinela_salto = true; // Activa el centinela para evitar la pulsacion prolongada de la tecla
    }
    
    // Dibujar en pantalla sprites y texto de vida
    // Transformar vida (tipo int) a tipo string para mostrarlo

    std::string string_vida = std::to_string(dinosaurio.getVida()); 
    string_vida = "Vida: " + string_vida + " puntos";
    vida_text.setString(string_vida);

    window.draw(vida_text);

    // Sprites
    window.draw(boom);
  
    if(dinosaurio.getVida() != 0){ // Mostrar sprite del dinosaurio si tiene vida
      window.draw(dinosaurio.getSprite());
    }
    
    window.display();

  }

}
