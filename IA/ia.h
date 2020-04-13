#ifndef IA_H
#define IA_H

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

class IA
{
    private:
    public:
        void arriba(Dinosaurio *dino, int max);
        void abajo(Dinosaurio *dino, int max);
        void derecha(Dinosaurio *dino, int max);
        void izquierda(Dinosaurio *dino, int max);
        void quieto(Dinosaurio *dino, int max);
        void anda(Dinosaurio *dino);
        void movimientoDinos(vector<Dinosaurio*> dinosaurios, int _cont,std::vector<sf::Sprite*> &todoSprite);
};

#endif