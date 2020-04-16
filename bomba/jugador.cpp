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
            sprite->setPosition(112+32, 64+32);
    }
    puntos=0;
    invencible=false;
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
                std::cout<<"empuja primer anim"<<std::endl;
                //empuja=false;
                
    }else{
    timeempujar+=time;
        if(timeempujar>switchtime){
            std::cout<<"cambiatime"<<std::endl;
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
                    std::cout<<"normalidad time"<<std::endl;
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
        if(!colision){
        posredondeada(time);
        }
}
/*bool Jugador::frentevacio(Map* m){
    int x=(getSprite()->getPosition().x-112)/32;
    int y=(getSprite()->getPosition().y-64)/32;

    if(x==0)x=1;
    std::cout<<x<<y<<" mir"<<mir<<std::endl;

    if(mir==0){
        if(y==0)return false;
        if(m->gettilemap()[0][x][y-1]>0 || m->gettilemap()[1][x][y-1]>0){ //ARRIBA
            return false;
        }
    }else if(mir==1)
    {
        if(y==17)return false;
        if(m->gettilemap()[0][x][y+1]>0 || m->gettilemap()[1][x][y+1]>0){ //ABAJO
        std::cout<<m->gettilemap()[0][x][y+1]<<m->gettilemap()[1][x][y+1]<<" mir"<<mir<<std::endl;
            return false;
        }
    }else if(mir==2)
    {
        if(x==15)return false;
                if(m->gettilemap()[0][x+1][y]>0 || m->gettilemap()[1][x+1][y]>0){ //DRE

 std::cout<<m->gettilemap()[0][x+1][y]<<m->gettilemap()[1][x+1][y]<<" mir"<<mir<<std::endl;
 return false;

        }
    }else if(mir==3)
    {
        if(x==0)return false;
        std::cout<<x<<y<<std::endl;
                if(m->gettilemap()[0][x-1][y]>0 || m->gettilemap()[1][x-1][y]>0){ //IZQ

 return false;


        }
    }
    
    return true;

}*/
void Jugador::posredondeada(float time){

    int x=getSprite()->getPosition().x+16;
    int y=getSprite()->getPosition().y;

    if((x%32)>0.1){
        mover(getmir(),time);
        animacion(getmir(),time);
    }
    if((y%32)>0.1){
        mover(getmir(),time);
        animacion(getmir(),time);
    }
}

