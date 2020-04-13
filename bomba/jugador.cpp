#include "jugador.h"
#include <iostream>

Jugador::Jugador(int numero)
{
    textura = new sf::Texture();
    if (!textura->loadFromFile("resources/sprites.png")) {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }

    sprite = new sf::Sprite();
    sprite->setTexture(*textura);
    sprite->setOrigin(75 / 2, 75 / 2);
    sprite->setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75));
    sprite->setScale(0.35,0.35);
    if (numero==1)
    {
            sprite->setPosition(160, 113);
    }else
    {
            sprite->setPosition(192, 177);
    }
    
    
    invencible=false;
    identificador = numero;
    kVel = 2;
}


void Jugador::draw(sf::RenderWindow &window)
{
    window.draw(*sprite);
}

void Jugador::mover(int direccion)
{
    switch (direccion)
    {

    //Arriba
    case 0:
        sprite->setTextureRect(sf::IntRect(0 * 75, 3 * 75, 75, 75));
        sprite->move(0, -kVel);
        break;
    //Abajo
    case 1:
        sprite->setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75));
        sprite->move(0, kVel);
        break;
    //Derecha
    case 2:
        sprite->setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
        //Escala por defecto
        sprite->setScale(0.35,0.35);
        sprite->move(kVel, 0);
        break;
    //Izquierda
    case 3:
        sprite->setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
        //Reflejo vertical
        sprite->setScale(-0.35, 0.35);
        sprite->move(-kVel, 0);
        break;
    }

}



