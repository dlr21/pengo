#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Jugador{
    
 public:
    Jugador(int num);
    sf::Sprite* getSprite(){return sprite;};
    int getIdentificador(){return identificador;};
    bool getempujon(){return empuja;}
    int getmir(){return mir;}
    bool getPuesta(){return bomba;};
    int getVelocidad(){return kVel;}
    int getVidas(){return vidas;}
    float getInvencibilidad(){return invencibilidad;}
    bool getInvencible(){return invencible;}
    int getPuntos(){return puntos;}
    void sumaPuntos(){puntos+=100;}
    void setPuesta(bool estado){bomba = estado;}
    void setVelocidad(int velocidad){kVel = velocidad;}
    void setVidas(int v){vidas = v;}
    void setInvencibilidad(float f){invencibilidad = f;}
    void changeInvencile(){
       if(!invencible){
          invencible=true;
          }else
          {
             invencible=false;
          } 
      }
    void empujando(float time);
    void setInicio(){    sprite->setPosition(112+32, 64+32); }//DEPENDE DEL MAPA
    void setkx(float a){kVelx=a;}
    void setky(float a){kVely=a;}
    float getkx(){return kVelx;}
    float getky(){return kVely;}
    
    void quitarVidas(){if(vidas > 0)vidas--;}
    void setmir(int i){mir=i;}
    void setempujon(bool i){
       animal=true;
       timeempujar=0;
       empuja=i;
      }
    void draw(sf::RenderWindow &window);
    void animacion(int d,float time);
    void setColision(bool f){colision=f;}
    void mover(int direccion,float time);
    void Update(float time );
    void posredondeada(float time);
    //bool frentevacio(Map* m);
 private:
    sf::Texture* textura;
    sf::Sprite* sprite;
    sf::Sprite* sprite2;
    int identificador;
    bool bomba;
    float kVel=1882/10;
    float kVelx=1882/10;
    float kVely=1882/10;
    int vidas = 3;
    
    
    int puntos;
    int mir=1;
    float switchtime=0.1;
    float totaltime=0;
    float timeempujar=0;
    float invencibilidad = -1;
    
    bool invencible;
    bool empuja=false;
    bool normal=true;
    bool colision=false;
    bool animal=true;
};
