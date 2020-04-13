#include <SFML/Graphics.hpp>
#include <iostream>
#include "dinosaurio.h"

// Velocidades
float velocidad_normal = 0.0015;
float velocidad_trex = 0.00075;
float velocidad_velociraptor = 0.00225;



Dinosaurio::Dinosaurio(){ // Constructor por defecto
    // Texturas de todos los movimientos del dinosaurio.
    // Se crean aqui porque asi, nada mas llamar al constructor, estan dentro de la clase 
    sf::Texture dino_abajo, dino_derecha, dino_izquierda, dino_arriba;
    _Sprite->setScale(0.5,0.5);
    
    if(!dino_abajo.loadFromFile("resources/dino_abajo.png")){
        std::cerr << "Error cargando dino_abajo.png";
        exit(0);
    }
    if(!dino_derecha.loadFromFile("resources/dino_derecha.png")){
        std::cerr << "Error cargando dino_derecha.png";
        exit(0);
    }
    if(!dino_izquierda.loadFromFile("resources/dino_izquierda.png")){
        std::cerr << "Error cargando dino_izquierda.png";
        exit(0);
    }     
    if(!dino_arriba.loadFromFile("resources/dino_arriba.png")){
        std::cerr << "Error cargando dino_arriba.png";
        exit(0);
    }        

    _dino_texture_abajo=dino_abajo;
    _dino_texture_arriba=dino_arriba;
    _dino_texture_derecha=dino_derecha;
    _dino_texture_izquierda=dino_izquierda;     
    srand (time(NULL));    
    _posdino = rand() % 5; // Posicion inicial por defecto hacia abajo
    _Direccion = _Tipodino;
}

Dinosaurio::~Dinosaurio(){ // Destructor
  _Sprite=NULL;
  delete _Sprite; 
}

Dinosaurio::Dinosaurio(sf::Texture& textura_dino){ // Constructor con textura (no se usa)
    _Sprite->setTexture(textura_dino);
    _Sprite->setScale(0.5,0.5);
    _Sprite->setPosition(320, 320);
}

void Dinosaurio::setTipodino(int tipodino){ // Tipo dinosaurio
    _Tipodino = tipodino; // 0: T-Rex | 1: Velociraptor | 2: Pterodactilo | 3: Triceratops
    _Direccion = _Tipodino; 

    setSpeed(); // Poner velocidad del dinosaurio
    setVida(); // Poner vida del dinosaurio
}

void Dinosaurio::modifyTexture(sf::Texture& textura){ // Establecer textura del dinosaurio
    _Sprite->setTexture(textura);
    
}

void Dinosaurio::modifyVida(){ // Quitar un punto de vida si toca la bomba
    if(_Vida >= 1){
        _Vida =_Vida - 1;
    }
}

int Dinosaurio::getTipodino(){ // Devuelve tipo de dinosaurio
    return _Tipodino;
}

sf::Sprite* Dinosaurio::getSprite() { // Devuelve el sprite
    /* En caso de que el Sprite visible se haya perdido, se reestablece usando la posion
     * a la que mira el dinosaurio. Aunque se haya perdido, sus propiedades siguen 
     * estando ahi.
     */
    if(_posdino==0){
        _Sprite->setTexture(_dino_texture_arriba);
    }
    if(_posdino==1){
        _Sprite->setTexture(_dino_texture_abajo);
    }   
    if(_posdino==2){
        _Sprite->setTexture(_dino_texture_derecha);
    }
    if(_posdino==3){
        _Sprite->setTexture(_dino_texture_izquierda);
    }
    return _Sprite;
}

void Dinosaurio::modifyPosition(int x, int y){ // Cambiar posicion del dinosaurio
    _Sprite->setPosition(x, y);
}

void Dinosaurio::setSpeed(){ // Cambiar la velocidad
    if(_Tipodino == 0){ // T-rex
        _Speed = velocidad_trex;
    }
    if(_Tipodino == 1){ // Velociraptor
        _Speed = velocidad_velociraptor; 
    }
    if(_Tipodino == 2 || _Tipodino == 3){ // Resto de dinosaurios
        _Speed = velocidad_normal; 
    }
}

void Dinosaurio::setVida(){ // Cambiar vida
    if(_Tipodino == 0){ // T-rex tiene 2 de vida
        _Vida = 2; 
    }
    else{ // El resto de dinosaurios tiene 1 de vida
        _Vida = 1;
    }
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
    _Sprite->setTexture(_dino_texture_arriba);
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
    _Sprite->setTexture(_dino_texture_abajo);
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
    //_Sprite.setTextureRect(sf::IntRect(1 * 75, 2 * 75, 75, 75));
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

// Hacer que el dinosaurio salte
void Dinosaurio::salto(int pos_mirando){
    if(_Tipodino == 2){ // Solo puede saltar el pterodactilo
        switch (pos_mirando){
        case 0: // Mirando arriba
            _Sprite->move(0, -(_Speed)*800);
            break;
        case 1: // Mirando abajo
            _Sprite->move(0, (_Speed)*800);
            break;
        case 2: // Mirando derecha
            _Sprite->move((_Speed)*800,0);
            break;
        case 3: // Mirando izquierda
            _Sprite->move((-_Speed)*800,0);
        default:
            break;
        }
    }
}



