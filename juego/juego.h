#ifndef JUEGO_H
#define JUEGO_H

#pragma once
#include <string>
#include <iostream>
#include "states.h"
#include "mundo.h"

using namespace std;

class Juego : public States {
  private:    
    static Juego* jinstance;
    Mundo* m;
  public:
    void Inicializar();
    static Juego* Instance();
    void Event(sf::Event event,sf::RenderWindow &window);
    void Update(sf::RenderWindow &window);
    void Draw(sf::RenderWindow &window);
  protected:
    void Cargarecursos();


};

#endif