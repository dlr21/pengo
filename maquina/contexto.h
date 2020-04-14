#ifndef CONTEXTO_H
#define CONTEXTO_H

#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>


class States;

class Contexto{

  private:
    // the stack of states
    std::vector<States*> states;
    bool m_running;
    static Contexto* pinstance;

  public:
    
    static Contexto* Instance();
    void Inicializar();

    void ChangeState(States* state);

    void Event(sf::Event event,sf::RenderWindow &window, float time);
    void Update(sf::RenderWindow &window, float time);
    void Draw(sf::RenderWindow &window);

    bool Running() { return m_running; }
    void Quit() { m_running = false; }

};

#endif