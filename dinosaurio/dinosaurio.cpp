#include <SFML/Graphics.hpp>
#include <iostream>
#include "dinosaurio.h"

// Velocidades
float velocidad_normal = 0.0015;




Dinosaurio::Dinosaurio(){ // Constructor por defecto
    // Texturas de todos los movimientos del dinosaurio.
    // Se crean aqui porque asi, nada mas llamar al constructor, estan dentro de la clase 
    textura = new sf::Texture();
    if (!textura->loadFromFile("resources/pengos.png")) {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }

    _Sprite = new sf::Sprite();
    _Sprite->setTexture(*textura);
    _Sprite->setOrigin(0,0);
    _Sprite->setScale(0.8,0.8);
    _Sprite->setTextureRect(sf::IntRect(0 * 32, 0 * 32, 32, 32));   
    srand (time(NULL));    
    _posdino = rand() % 5; // Posicion inicial por defecto hacia abajo
    setSpeed(); // Poner velocidad del dinosaurio
    setVida(); // Poner vida del dinosaurio
}

Dinosaurio::~Dinosaurio(){ // Destructor
  _Sprite=NULL;
  delete _Sprite; 
}

void Dinosaurio::modifyTexture(sf::Texture& textura){ // Establecer textura del dinosaurio
    _Sprite->setTexture(textura);
    
}

void Dinosaurio::modifyVida(){ // Quitar un punto de vida si toca la bomba
    if(_Vida >= 1){
        _Vida =_Vida - 1;
    }
}

sf::Sprite* Dinosaurio::getSprite() { // Devuelve el sprite
    /* En caso de que el Sprite visible se haya perdido, se reestablece usando la posion
     * a la que mira el dinosaurio. Aunque se haya perdido, sus propiedades siguen 
     * estando ahi.
     */
    if(_posdino==0){
        _Sprite->setTextureRect(sf::IntRect(4 * 32, 9 * 32, 32, 32));
    }
    if(_posdino==1){
        _Sprite->setTextureRect(sf::IntRect(0 * 32, 9 * 32, 32, 32));
    }   
    if(_posdino==2){
        _Sprite->setTextureRect(sf::IntRect(6 * 32, 9 * 32, 32, 32));
    }
    if(_posdino==3){
        _Sprite->setTextureRect(sf::IntRect(3 * 32, 9 * 32, 32, 32));
    }
    return _Sprite;
}

void Dinosaurio::modifyPosition(int x, int y){ // Cambiar posicion del dinosaurio
    _Sprite->setPosition(x, y);
}

void Dinosaurio::setSpeed(){ // Cambiar la velocidad
        _Speed = velocidad_normal; 
}

void Dinosaurio::setVida(){ // Cambiar vida
        _Vida = 1;
}

int Dinosaurio::getVida(){ // Devolver vida
    return _Vida;
}

int Dinosaurio::getSpeed(){ // Devolver velocidad
    return _Speed;
}

sf::FloatRect Dinosaurio::getHitbox(){ // FloatRect devuelve coordenada superior izq
    return _Sprite->getGlobalBounds(); // Coordenadas de entorno de Sprite
}

// Funciones de movimiento (salto y movimientos)
int Dinosaurio::marriba(std::vector<sf::Sprite*> &todo){ // Movimiento arriba
    _Sprite->setTextureRect(sf::IntRect(4 * 32, 9 * 32, 32, 32));
    for(int i = 0; i < 160; i++){
        for(unsigned int j = 0;j < todo.size();j++)
        {
            if(_Sprite->getGlobalBounds().intersects(todo[j]->getGlobalBounds()) && _Sprite!=todo[j])
            {
                //std::cout<<"dino no mueve arriba"<<std::endl;
                _posdino = 0;
                 _Sprite->move(0, _Speed);
                return 0;
            }
        }
        _Sprite->move(0, -(_Speed));
    }
    _posdino = 0;
    return 0; // Posicion arriba
}

int Dinosaurio::mabajo(std::vector<sf::Sprite*> &todo){ // Movimiento abajo
        _Sprite->setTextureRect(sf::IntRect(0 * 32, 9 * 32, 32, 32));
    for(int i = 0; i < 160; i++){
        for(unsigned int j = 0;j < todo.size();j++)
        {
            if(_Sprite->getGlobalBounds().intersects(todo[j]->getGlobalBounds()) && _Sprite!=todo[j])
            {
                //std::cout<<"dino no mueve abajo"<<std::endl;
                _posdino = 1;
                _Sprite->move(0, -(_Speed));
                return 1;
            }
        }
        _Sprite->move(0, _Speed);
    }
    _posdino = 1;
    return 1; // Posicion abajo
}

int Dinosaurio::mderecha(std::vector<sf::Sprite*> &todo){ // Movimiento derecha
        _Sprite->setTextureRect(sf::IntRect(6 * 32, 9 * 32, 32, 32));
    for(int i = 0; i < 160; i++){
        for(unsigned int j = 0;j < todo.size();j++)
        {
            if(_Sprite->getGlobalBounds().intersects(todo[j]->getGlobalBounds()) && _Sprite!=todo[j])
            {
                //std::cout<<"dino no mueve dre"<<std::endl;
                _posdino = 2;
                    _Sprite->move(-(_Speed),0);
                return 2;
            }
        }
        _Sprite->move(_Speed, 0);
    }
    _posdino = 2;
    return 2; // Posicion derecha
}

int Dinosaurio::mizquierda(std::vector<sf::Sprite*> &todo){ // Movimiento izquierda
        _Sprite->setTextureRect(sf::IntRect(3 * 32, 9 * 32, 32, 32));
    for(int i = 0; i < 160; i++){
        for(unsigned int j = 0;j < todo.size();j++)
        {
            if(_Sprite->getGlobalBounds().intersects(todo[j]->getGlobalBounds()) && _Sprite!=todo[j])
            {
                //std::cout<<"dino no mueve izq"<<std::endl;
                _posdino = 3;
                _Sprite->move(_Speed, 0);
                return 3;
            }
        }
        _Sprite->move(-(_Speed),0);
    }
    _posdino = 3;
    return 3; // Posicion izquierda
}

void Dinosaurio::sumaPasos(){
    int pasos;
    for(int i = 0; i < 160; i++){
        pasos++;
    }
};

void Dinosaurio::setDireccion(int i){
    _Direccion = i;
}

int Dinosaurio::getDireccion(){
    return _Direccion;
}

void Dinosaurio::draw(sf::RenderWindow &window)
{
    window.draw(*_Sprite);
}




