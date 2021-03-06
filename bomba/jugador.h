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
        void setPuntos(int a){ puntos=a;}
    void sumaPuntos(){puntos+=100;}
    void maspuntos(int a){puntos+=(60-a)*10;};
    void setPuesta(bool estado){bomba = estado;}
    void setVelocidad(int velocidad){kVel = velocidad;}
    void setVidas(int v){vidas = v;}
    void setInvencibilidad(float f){invencibilidad = f;}
    void changeInvencile(){
       if(!invencible){
            invencible=true;
          }else{
            invencible=false;
          } 
      }
    void empujando(float time);
    void setInicio(){  
         sprite->setPosition(112+32, 64+32);
         empuja=false;
         normal=true;
         colision=false;
         animal=true;
         movido=false;
         tecla=false;
         moviendo=false;
         matando=false;
         colocado=true;
         mir=1;
    }
    void setkx(float a){kVelx=a;}
    void setky(float a){kVely=a;}
    float getkx(){return kVelx;}
    float getky(){return kVely;}
    int getposimapax(){
       int x=sprite->getPosition().x-112;
       if(x%32<=16)return x/32;
       if(x%32>16)return (x/32)+1;
    }
    int getposimapay(){
       int y=sprite->getPosition().y-64;
       if(y%32<=16)return y/32;
       if(y%32>16)return (y/32)+1;
    }
    bool getColision(){return colision;}
    bool getmovido(){return movido;}
     bool getmoviendo(){return moviendo;}
    
   
   void setmovido(bool a){movido=a;}
    void setmoviendo(bool a){moviendo=a;}
     void settecla(bool a){tecla=a;}
       bool gettecla(){return tecla;}


       void setmatando(bool a){matando=a;}
       bool getmatando(){return matando;}
     
           
    void quitarVidas(){if(vidas > 0 && !invencible)vidas--;}
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
    bool setcolocado(bool a){
       colocado=a;
    }
    bool getcolocado(){
      return colocado;
    }


 private:
    sf::Texture* textura;
    sf::Sprite* sprite;
    sf::Sprite* sprite2;
    int identificador;
    bool bomba;
    float kVel=225;
    float kVelx=kVel;
    float kVely=kVel;
    int vidas = 3;
    
    
    int puntos=0;;
    int mir;
    float switchtime=0.1;
    float totaltime=0;
    float timeempujar=0;
    float invencibilidad = -1;
    
    bool invencible=false;
    bool empuja;
    bool normal;
    bool colision;
    bool animal;
    bool movido;
    bool tecla;
    bool moviendo;
    bool matando;
    bool colocado;
};
