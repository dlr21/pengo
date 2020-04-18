#ifndef IA_H
#define IA_H

#include <string>
#include <iostream>
#include "states.h"
#include "Map.h"
#include "Tile.h"
#include "jugador.h"
#include "dinosaurio.h"
#include "colisiones.h"

class IA
{
    private:

    public:

        void movimientoDinos(vector<Dinosaurio*> dinosaurios, int _cont,std::vector<sf::Sprite*> &todoSprite, float time,Map* m);
        bool elegirdireccion(Dinosaurio* dinosaurio, Map* m);
};

#endif