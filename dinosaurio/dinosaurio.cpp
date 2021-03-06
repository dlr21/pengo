#include <SFML/Graphics.hpp>
#include <iostream>
#include "dinosaurio.h"


Dinosaurio::Dinosaurio(){ 

    textura = new sf::Texture();
    if (!textura->loadFromFile("resources/pengos.png")) {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }

    _Sprite = new sf::Sprite();
    _Sprite->setTexture(*textura);
    _Sprite->setOrigin(16,16);
    _Sprite->setScale(0.9,0.9);
    _Sprite->setTextureRect(sf::IntRect(0 * 32, 9 * 32, 32, 32));   

}

Dinosaurio::~Dinosaurio(){ // Destructor
  _Sprite=NULL;
  delete _Sprite; 
}



void Dinosaurio::modifyVida(){
    if(_Vida >= 1){
        _Vida =_Vida - 1;
    }
}

sf::Sprite* Dinosaurio::getSprite() { // Devuelve el sprite
    return _Sprite;
}

void Dinosaurio::modifyPosition(int x, int y){ // Cambiar posicion 
    _Sprite->setPosition(x, y);
}



int Dinosaurio::getVida(){ // Devolver vida
    return _Vida;
}

int Dinosaurio::getSpeed(){ // Devolver velocidad
    return kVel;
}


int Dinosaurio::marriba(std::vector<sf::Sprite*> &todo, float time){ // Movimiento arriba
    
    
        for(unsigned int j = 0;j < todo.size();j++)
        {
            if(_Sprite->getGlobalBounds().intersects(todo[j]->getGlobalBounds()) && _Sprite!=todo[j])
            {

                _Sprite->setPosition(getposimapax()*32+112,getposimapay()*32+64);
                                if(_Sprite->getGlobalBounds().intersects(todo[j]->getGlobalBounds()) && _Sprite!=todo[j])
                {
                    recolocar(todo,0);
                }
                setparado(true);
                return 0;
            }
        }
         mover(0,time);    
  
    return 0; 
}
int Dinosaurio::mabajo(std::vector<sf::Sprite*> &todo, float time){ // Movimiento abajo
        
    
        for(unsigned int j = 0;j < todo.size();j++)
        {
            if(_Sprite->getGlobalBounds().intersects(todo[j]->getGlobalBounds()) && _Sprite!=todo[j])
            {

                
                _Sprite->setPosition(getposimapax()*32+112,getposimapay()*32+64);
                if(_Sprite->getGlobalBounds().intersects(todo[j]->getGlobalBounds()) && _Sprite!=todo[j])
                {
                    recolocar(todo,0);
                }
                setparado(true);
                return 1;
            }
        }
         mover(1,time);    
    
    
    return 1; 
}
int Dinosaurio::mderecha(std::vector<sf::Sprite*> &todo, float time){ // Movimiento derecha
        
   
        for(unsigned int j = 0;j < todo.size();j++)
        {
            if(_Sprite->getGlobalBounds().intersects(todo[j]->getGlobalBounds()) && _Sprite!=todo[j])
            {
 
                _Sprite->setPosition(getposimapax()*32+112,getposimapay()*32+64);
                if(_Sprite->getGlobalBounds().intersects(todo[j]->getGlobalBounds()) && _Sprite!=todo[j])
                {
                    recolocar(todo,0);
                }
                setparado(true);
                return 2;
            }
        }
         mover(2,time);    
    
    return 2; 
}
int Dinosaurio::mizquierda(std::vector<sf::Sprite*> &todo, float time){ // Movimiento izquierda
        
    
        for(unsigned int j = 0;j < todo.size();j++)
        {
            if(_Sprite->getGlobalBounds().intersects(todo[j]->getGlobalBounds()) && _Sprite!=todo[j])
            {

                _Sprite->setPosition(getposimapax()*32+112,getposimapay()*32+64);
                                if(_Sprite->getGlobalBounds().intersects(todo[j]->getGlobalBounds()) && _Sprite!=todo[j])
                {
                    recolocar(todo,0);
                }
                setparado(true);
                return 3;
            }
        }
        mover(3,time);    
        return 3; 
}



void Dinosaurio::draw(sf::RenderWindow &window){
    if(activo)window.draw(*_Sprite);
}


void Dinosaurio::animacion(int dir,float deltatime){
    if(!aturdido){
        if(_posdino!=dir){
            _posdino=dir;
                if(dir==0) {
                                _Sprite->setTextureRect(sf::IntRect(4 * 32, 9 * 32, 32, 32));

                }
                if(dir==1) {
                                _Sprite->setTextureRect(sf::IntRect(0 * 32, 9 * 32, 32, 32));

                }
                if(dir==2) {
                                _Sprite->setTextureRect(sf::IntRect(7 * 32, 9 * 32, 32, 32));

                }
                if(dir==3) {
                                _Sprite->setTextureRect(sf::IntRect(3 * 32, 9 * 32, 32, 32));

                }
        }
        totaltime+=deltatime;
        if(totaltime>switchtime){
            totaltime=0;
            if(animal){
                animal=false;
                if(dir==0) {
                                _Sprite->setTextureRect(sf::IntRect(4 * 32, 9 * 32, 32, 32));

                }
                if(dir==1) {
                                _Sprite->setTextureRect(sf::IntRect(0 * 32, 9 * 32, 32, 32));

                }
                if(dir==2) {
                                _Sprite->setTextureRect(sf::IntRect(7 * 32, 9 * 32, 32, 32));

                }
                if(dir==3) {
                                _Sprite->setTextureRect(sf::IntRect(3 * 32, 9 * 32, 32, 32));

                }
            }else{
                animal=true;
                if(dir==0) {
                                _Sprite->setTextureRect(sf::IntRect(5 * 32, 9 * 32, 32, 32));

                }
                if(dir==1) {
                                _Sprite->setTextureRect(sf::IntRect(1 * 32, 9 * 32, 32, 32));

                }
                if(dir==2) {
                                _Sprite->setTextureRect(sf::IntRect(6 * 32, 9 * 32, 32, 32));

                }
                if(dir==3) {
                                _Sprite->setTextureRect(sf::IntRect(2 * 32, 9 * 32, 32, 32));

                }
            }
        } 
    }else
    {
        totaltime+=deltatime;
        if(totaltime>switchtime){
            totaltime=0;
            if(animal){
                animal=false;
                _Sprite->setTextureRect(sf::IntRect(6 * 32, 8 * 32, 32, 32));
            }else{
                animal=true;
                _Sprite->setTextureRect(sf::IntRect(7 * 32, 8 * 32, 32, 32));
            }
        }
    }
}

void Dinosaurio::mover(int dir,float deltatime){
    if(!parado){
        kVelx=0;
        kVely=0;
        switch (dir)
        {
        //Arriba
        case 0:
            kVely=-kVel*deltatime;
            
            break;
        //Abajo
        case 1:
            kVely=kVel*deltatime;
            
            break;
        //Derecha
        case 2:
            kVelx=kVel*deltatime;
            
            break;
        //Izquierda
        case 3:
            kVelx=-kVel*deltatime;
            
            break;
        }

        _Sprite->move(kVelx,kVely);
    }

}
