#pragma once
#include <SFML/Graphics.hpp>

class Jugador{
    
 public:
    Jugador(int num);
    sf::Sprite* getSprite(){return sprite;};
    int getIdentificador(){return identificador;};
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
    void setInicio(){    sprite->setPosition(112+48, 64+48); }//DEPENDE DEL MAPA
    void mover(int direccion,float time);
    void quitarVidas(){if(vidas > 0)vidas--;}

    void draw(sf::RenderWindow &window);
    void animacion(int d,float time);
 private:
    sf::Texture* textura;
    sf::Sprite* sprite;
    sf::Sprite* sprite2;
    int identificador;
    bool bomba;
    int kVel;
    int vidas = 3;
    float invencibilidad = -1;
    bool invencible;
    int puntos;
    float switchtime=0.1;
    float totaltime=0;
    bool animal=true;
};
