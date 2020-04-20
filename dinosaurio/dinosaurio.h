#ifndef DINOSAURIO_H
#define DINOSAURIO_H

class Dinosaurio 
{
    public:
      Dinosaurio(); // Constructor por defecto
      ~Dinosaurio(); // Destructor

      int marriba(std::vector<sf::Sprite*> &c, float time);
      int mabajo(std::vector<sf::Sprite*> &c, float time);
      int mderecha(std::vector<sf::Sprite*> &c, float time);
      int mizquierda(std::vector<sf::Sprite*> &c, float time);

      sf::Sprite* getSprite() ;

      void setInvencibilidad(float f){invencibilidad = f;}

      int getVida();

      int getSpeed();


      float getInvencibilidad(){return invencibilidad;}

      int getposimapax(){
       int x=_Sprite->getPosition().x-112;
       if(x%32<=16)return x/32;
       if(x%32>16)return (x/32)+1;
      }
      int getposimapay(){
       int y=_Sprite->getPosition().y-64;
       if(y%32<=16)return y/32;
       if(y%32>16)return (y/32)+1;
      }
      float getcambiodir(){return cambiodir;}
      float gettotalcambio(){return totalcambio;}
      int getDireccion(){return _posdino;}
      bool getactivo(){return activo;}
      void modifyVida();
      void modifyPosition(int x, int y);
      int generaRandom(int max);
      int movimiento();
      void sumaPasos();
    
      void draw(sf::RenderWindow &window);
      bool getparado(){return parado;}
      void setparado(bool a){parado=a;}

      void activar(){activo=true;}
      void animacion(int d,float time);
      void mover(int dir,float deltatime);
      void setposdino(int i){_posdino=i;}
      void setactivo(bool a){activo=a;}

      void settotalcambio(float a){totalcambio=a;}

      void setaturdido(bool a){aturdido=a;}
      bool getaturdido(){return aturdido;}

    private:
      float kVel=1500/10;
      float kVelx=1500/10;
      float kVely=1500/10;
      sf::Sprite* _Sprite = new sf::Sprite; // Sprite
      sf::Texture* textura;
      int _posdino=1; // Posicion a la que mira el dino ==> 0:Arriba | 1:Abajo | 2:Derecha | 3:Izquierda
      int _Vida=1; 
      float invencibilidad = -1; 
      bool parado=false;
      bool activo=false;
      float switchtime=0.15;
        float cambiodir=1;
      float totaltime=0;
        float totalcambio=0;
      bool animal=true;
      bool aturdido=false;

};

#endif
