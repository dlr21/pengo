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
    sprite->setScale(0.8,0.8);
    sprite->setTextureRect(sf::IntRect(0 * 32, 0 * 32, 32, 32));
    if (numero==1)
    {
            sprite->setPosition(112+48, 64+48);
    }
    puntos=0;
    invencible=false;
    identificador = numero;
    kVel = 150;
}
void Jugador::draw(sf::RenderWindow &window)
{
    window.draw(*sprite);
}
void Jugador::animacion(int dir,float deltatime){
    totaltime+=deltatime;
    std::cout<<totaltime<<"tiempo total"<<std::endl;
    if(totaltime>switchtime){
        totaltime=0;
        if(animal){
            animal=false;
            if(dir==0) {
                            sprite->setTextureRect(sf::IntRect(4 * 32, 0 * 32, 32, 32));

            }
            if(dir==1) {
                            sprite->setTextureRect(sf::IntRect(0 * 32, 0 * 32, 32, 32));

            }
            if(dir==2) {
                            sprite->setTextureRect(sf::IntRect(7 * 32, 0 * 32, 32, 32));

            }
            if(dir==3) {
                            sprite->setTextureRect(sf::IntRect(3 * 32, 0 * 32, 32, 32));

            }
        }else{
            animal=true;
            if(dir==0) {
                            sprite->setTextureRect(sf::IntRect(5 * 32, 0 * 32, 32, 32));

            }
            if(dir==1) {
                            sprite->setTextureRect(sf::IntRect(1 * 32, 0 * 32, 32, 32));

            }
            if(dir==2) {
                            sprite->setTextureRect(sf::IntRect(6 * 32, 0 * 32, 32, 32));

            }
            if(dir==3) {
                            sprite->setTextureRect(sf::IntRect(2 * 32, 0 * 32, 32, 32));

            }
        }
    } 
}
void Jugador::mover(int direccion, float time)
{
    switch (direccion)
    {

    //Arriba
    case 0:
        animacion(direccion,time);
        sprite->move(0, -kVel*time);
        break;
    //Abajo
    case 1:
        animacion(direccion,time);
        sprite->move(0, kVel*time);
        break;
    //Derecha
    case 2:
        animacion(direccion,time);
        sprite->move(kVel*time, 0);
        break;
    //Izquierda
    case 3:
        animacion(direccion,time);
        sprite->move(-kVel*time, 0);
        break;
    }

}



