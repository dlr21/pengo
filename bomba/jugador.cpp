#include "jugador.h"
#include <iostream>

Jugador::Jugador(int numero)
{
    textura = new sf::Texture();
    if (!textura->loadFromFile("resources/pengos.png")) {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }

    sprite = new sf::Sprite();
    sprite->setTexture(*textura);
    sprite->setOrigin(32 / 2, 32 / 2);
    sprite->setTextureRect(sf::IntRect(0 * 32, 0 * 32, 32, 32));
    if (numero==1)
    {
            sprite->setPosition(160, 113);
    }else
    {
            sprite->setPosition(192, 177);
    }
    
    puntos=0;
    invencible=false;
    identificador = numero;
    kVel = 32;
}


void Jugador::draw(sf::RenderWindow &window)
{
    window.draw(*sprite);
}

void Jugador::mover(int direccion, float time)
{
    switch (direccion)
    {

    //Arriba
    case 0:
        sprite->setTextureRect(sf::IntRect(4 * 32, 0 * 32, 32, 32));
        sprite->move(0, -kVel*time);
        break;
    //Abajo
    case 1:
        sprite->setTextureRect(sf::IntRect(0 * 32, 0 * 32, 32, 32));
        sprite->move(0, kVel*time);
        break;
    //Derecha
    case 2:
        sprite->setTextureRect(sf::IntRect(6 * 32, 0 * 32, 32, 32));
        sprite->move(kVel*time, 0);
        break;
    //Izquierda
    case 3:
        sprite->setTextureRect(sf::IntRect(3 * 32, 0 * 32, 32, 32));
        sprite->move(-kVel*time, 0);
        break;
    }

}



