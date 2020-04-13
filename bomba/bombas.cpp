#include "bombas.h"
#include <iostream>

//Arriba esa fiesta
//Y todo eso
Bomba::Bomba(float x, float y)
{
    coordenadaX = x;
    coordenadaY = y;
    activarColision = false;

    //Cargo la textura de las explosiones para usarlas posteriormente.
    texplosiones = new sf::Texture();

    if (!texplosiones->loadFromFile("resources/explosion.png")) {
        std::cerr << "Error cargando la imagen explosion.png";
        exit(0);
    }

    //Cargo la textura y creo el sprite de la bomba.
    tbomba = new sf::Texture();
    if (!tbomba->loadFromFile("resources/bomba.png")) {
        std::cerr << "Error cargando la imagen bomba.png";
        exit(0);
    }

    sbomba.setTexture(*tbomba);
    sbomba.setTextureRect(sf::IntRect(0, 0, 410, 370));
    sbomba.setOrigin(410/2,370/2);
    sbomba.setPosition(x,y);
    sbomba.scale(0.10,0.10);
}

std::vector<sf::Sprite> Bomba::GenerarExplosion()
{
    std::vector<sf::Sprite> sprites;
    float x = getCoordenadaX();
    float y = getCoordenadaY();
    //Escala.
    float sc = 0.035;
    //Distancia separacion entre explosiones.
    int dsExp = 32;

    //Explosion central.
    sf::Sprite explosionCen(*texplosiones);
    explosionCen.setOrigin(840/2, 840/2);
    explosionCen.setTextureRect(sf::IntRect(0, 0, 900, 900));
    explosionCen.setPosition(x,y);
    explosionCen.setScale(sc,sc);
    sprites.push_back(explosionCen);

    //Explosion izquierda.
    sf::Sprite explosionIzq(*texplosiones);
    explosionIzq.setOrigin(840/2, 840/2);
    explosionIzq.setTextureRect(sf::IntRect(0, 0, 900, 900));
    explosionIzq.setPosition(x-dsExp,y);
    explosionIzq.setScale(sc,sc);
    sprites.push_back(explosionIzq);

    //Explosion derecha.
    sf::Sprite explosionDer(*texplosiones);
    explosionDer.setOrigin(840/2, 840/2);
    explosionDer.setTextureRect(sf::IntRect(0, 0, 900, 900));
    explosionDer.setPosition(x+dsExp,y);
    explosionDer.setScale(sc,sc);
    sprites.push_back(explosionDer);

    //Explosion arriba.
    sf::Sprite explosionAr(*texplosiones);
    explosionAr.setOrigin(840/2, 840/2);
    explosionAr.setTextureRect(sf::IntRect(0, 0, 900, 900));
    explosionAr.setPosition(x,y+dsExp);
    explosionAr.setScale(sc,sc);
    sprites.push_back(explosionAr);

    //Explosion abajo.
    sf::Sprite explosionAb(*texplosiones);
    explosionAb.setOrigin(840/2, 840/2);
    explosionAb.setTextureRect(sf::IntRect(0, 0, 900, 900));
    explosionAb.setPosition(x,y-dsExp);
    explosionAb.setScale(sc,sc);
    sprites.push_back(explosionAb);

    //Rellenamos la variable explosiones.
    setExplosion(sprites);

    return sprites;
}

void Bomba::update(sf::Clock &temporizador,Jugador &jugador,std::vector<Bomba> &totalBombas,std::vector<sf::Sprite> &totalExplosiones,std::vector<float> &tiemposBomba,std::vector<float> &tiemposExplosiones)
{
    //Detectamos si ya ha pasado la cantidad de tiempo suficiente para que explote una bomba.
    if(tiemposBomba.size() > 0 && temporizador.getElapsedTime().asSeconds() - tiemposBomba[0] >= 3)
    {
      //Nos guardamos las explosiones generadas por la bomba que lleva mas tiempo puesta.
      std::vector<sf::Sprite> aux = totalBombas[0].GenerarExplosion();
      for(unsigned int i = 0;i < aux.size();i++)
      {
        totalExplosiones.push_back(aux[i]);
      }

      //Nos guardamos el tiempo en el que ha producido la explosion.
      tiemposExplosiones.push_back(temporizador.getElapsedTime().asSeconds());
      //Si la bomba que se va a borrar es del jugador actual, le habilitamos para pueda volver a poner una bomba.
      if(totalBombas[0].getPropietario() == jugador.getIdentificador())
      {
        jugador.setPuesta(false);
      }
      //Borramos la bomba que lleva mas tiempo puesta.
      totalBombas.erase(totalBombas.begin());
      //Borramos el tiempo que controla la primera bomba.
      tiemposBomba.erase(tiemposBomba.begin());
    }

    
    //Ha pasado un segundo desde que se activa la explosion.
    if(tiemposExplosiones.size() > 0 && temporizador.getElapsedTime().asSeconds() - tiemposExplosiones[0] >= 1)
    {
      //Borramos explosion mas antigua y su tiempo.
      totalExplosiones.erase(totalExplosiones.begin(),totalExplosiones.begin()+5);
      tiemposExplosiones.erase(tiemposExplosiones.begin());
    }
}

//GETTERS

sf::Sprite Bomba::getBomba()
{
    return sbomba;
}

bool Bomba::getColision()
{
  return activarColision;
}

float Bomba::getCoordenadaX()
{
    return coordenadaX;
}

float Bomba::getCoordenadaY()
{
    return coordenadaY;
}

int Bomba::getPropietario()
{
    return propietario;
}

//SETTERS

bool Bomba::setColision()
{
  return activarColision = true;
}

void Bomba::setExplosion(std::vector<sf::Sprite> exp)
{
    for(int i = 0;i < 5; i++)
    {
        explosiones.push_back(exp[i]);
    }
}

void Bomba::setPropietario(int identificador)
{
    propietario = identificador;
}

void Bomba::draw(sf::RenderWindow &window)
{
    window.draw(sbomba);
}

