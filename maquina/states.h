#ifndef STATES_H
#define STATES_H

#pragma once
#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"
#include "contexto.h"


class States {
public:
	 virtual void Inicializar()=0;
	 virtual void Event(sf::Event event,sf::RenderWindow &window)=0 ;
	 virtual void Update(sf::RenderWindow &window)=0 ;
	 virtual void Draw(sf::RenderWindow &window)=0;
	void ChangeState(Contexto* game, States* state) {
		game->ChangeState(state);
	}
};

#endif