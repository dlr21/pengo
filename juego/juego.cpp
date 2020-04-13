#include "juego.h"


Juego* Juego::jinstance=0;

  Juego* Juego::Instance() {
    if(jinstance==0){
      jinstance=new Juego;
        std::cout<<"juegoinstance"; 
    }
    return jinstance;
  }

void Juego::Inicializar() {
  std::cout<<"juegoiniciado\n";
  //crear mundo
  m=Mundo::Instance();
  m->Inicializar();
}

void Juego::Event(sf::Event event,sf::RenderWindow &window){

m->Event(event,window);

}

void Juego::Update(sf::RenderWindow &window) {

        m->Update(window);
}
 void Juego::Draw(sf::RenderWindow &window){

    m->Draw(window);

 }