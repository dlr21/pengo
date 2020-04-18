#include "jugador.h"
#include <iostream>

Jugador::Jugador(int numero){
    textura = new sf::Texture();
    if (!textura->loadFromFile("resources/pengos.png")) {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    sprite = new sf::Sprite();
    sprite->setTexture(*textura);
    sprite->setOrigin(16, 16);
    sprite->setScale(0.9,0.9);
    sprite->setTextureRect(sf::IntRect(0 * 32, 0 * 32, 32, 32));
    if (numero==1)
    {
            setInicio();
    }

    identificador = numero;
}
void Jugador::draw(sf::RenderWindow &window){
    window.draw(*sprite);
}
void Jugador::empujando(float time){
    if(animal){animal=false;
        timeempujar=0;
        normal=false;
                if(mir==0) {
                                sprite->setTextureRect(sf::IntRect(4 * 32, 1 * 32, 32, 32));
                                
                }
                if(mir==1) {
                                sprite->setTextureRect(sf::IntRect(0 * 32, 1 * 32, 32, 32));
                }
                if(mir==2) {
                                sprite->setTextureRect(sf::IntRect(6 * 32, 1 * 32, 32, 32));
                }
                if(mir==3) {
                                sprite->setTextureRect(sf::IntRect(2 * 32, 1 * 32, 32, 32));
                }
                //empuja=false;
                
    }else{
    timeempujar+=time;
        if(timeempujar>switchtime){
            if(!normal){
                        if(mir==0) {
                                        sprite->setTextureRect(sf::IntRect(5 * 32, 1 * 32, 32, 32));

                        }
                        if(mir==1) {
                                        sprite->setTextureRect(sf::IntRect(1 * 32, 1 * 32, 32, 32));

                        }
                        if(mir==2) {
                                        sprite->setTextureRect(sf::IntRect(7 * 32, 1 * 32, 32, 32));

                        }
                        if(mir==3) {
                                        sprite->setTextureRect(sf::IntRect(3 * 32, 1 * 32, 32, 32));

                        }
                        timeempujar=0;
                        normal=true;
            }else{
                        if(mir==0) {
                            sprite->setTextureRect(sf::IntRect(4 * 32, 0 * 32, 32, 32));
                        }
                        if(mir==1) {
                            sprite->setTextureRect(sf::IntRect(0 * 32, 0 * 32, 32, 32));
                        }
                        if(mir==2) {
                            sprite->setTextureRect(sf::IntRect(7 * 32, 0 * 32, 32, 32));
                        }
                        if(mir==3) {
                            sprite->setTextureRect(sf::IntRect(3 * 32, 0 * 32, 32, 32));
                        }
                    empuja=false; 
                    animal=true;
            }
        }
    } 
}
void Jugador::animacion(int dir,float deltatime){
    if(mir!=dir){
        mir=dir;
            std::cout<<"normalidad"<<std::endl;
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
    }
    totaltime+=deltatime;
    if(totaltime>=switchtime){
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
            totaltime=0;
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
                animal=true;
            }
    }
}
void Jugador::mover(int direccion, float time){
    animacion(direccion,time);
    kVelx=0;
    kVely=0;
    switch (direccion)
    {
    //Arriba
    case 0:
         kVely=-kVel*time;
        
        break;
    //Abajo
    case 1:
        kVely=kVel*time;
        
        break;
    //Derecha
    case 2:
        kVelx=kVel*time;
        
        break;
    //Izquierda
    case 3:
        kVelx=-kVel*time;
        
        break;
    }

    sprite->move(kVelx,kVely);
}
void Jugador::Update(float time ){
    
    if(getInvencible()){
        setVidas(3);
    }
    if(getempujon()){
        empujando(time);
    }        
    if(!colision && !movido && !tecla){
            posredondeada(time);
    }
    settecla(false);
}

void Jugador::posredondeada(float time){

    int x=getSprite()->getPosition().x+16;
    

    if((x%32)>1){
        mover(getmir(),time);
    }

    int y=getSprite()->getPosition().y;
    
    if((y%32)>1){
        mover(getmir(),time);
    }
    
}



