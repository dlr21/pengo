#pragma once
#include <SFML/Graphics.hpp>
#include "jugador.h"

class Tile{

   
    public:
    Tile();
    void Cargarecursos();
    void Update(Jugador* j);
    void draw(sf::RenderWindow &window);
    void reiniciocrono(){min=5;seg=59;terminada=false;}
    bool getTerminada(){return terminada;}
private:

    sf::Sprite vida1;
    sf::Sprite vida2;
    sf::Sprite vida3;
    sf::Texture texvida;
    sf::Sprite letranumero;
    sf::Texture texletranumero;
    sf::Sprite contador;
    sf::Texture texcontador;
    sf::Clock temporizador;
    int segundero;
    std::vector<sf::Sprite> sprites;


    sf::Font fuente;
    sf::String cadena;
    sf::Text texto;
    int vidas=3;
    bool terminada=false;
    int min=2;
    int seg=12;



};