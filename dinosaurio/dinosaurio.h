#ifndef DINOSAURIO_H
#define DINOSAURIO_H

class Dinosaurio 
{
    public:
      Dinosaurio(); // Constructor por defecto
      Dinosaurio(sf::Texture&); // Constructor con textura
      ~Dinosaurio(); // Destructor
      // Movimiento
      bool marriba(std::vector<sf::Sprite*> &c, float time);
      bool mabajo(std::vector<sf::Sprite*> &c, float time);
      bool mderecha(std::vector<sf::Sprite*> &c, float time);
      bool mizquierda(std::vector<sf::Sprite*> &c, float time);
  
      // Devolver sprite
      sf::Sprite* getSprite() ;
      //Otorga un segundo de invencibilidad
      void setInvencibilidad(float f){invencibilidad = f;}
      // Devolver vida
      int getVida();
      // Devolver velocidad
      int getSpeed();
      // Devolver hitbox
      sf::FloatRect getHitbox();
      //Devolver invencibilidad
      float getInvencibilidad(){return invencibilidad;}
      // Modificar vida del dinosaurio en el caso de que toque la bomba
      void modifyVida();
      // Cambiar textura
      void modifyTexture(sf::Texture&);
      // Cambiar posicion
      void modifyPosition(int x, int y);
      int generaRandom(int max);
      int movimiento();
      void sumaPasos();
      int getDireccion();
      void draw(sf::RenderWindow &window);
      bool getparado(){return parado;}
      void setparado(bool a){parado=a;}
      bool getactivo(){return activo;}
      void activar(){activo=true;}
      void animacion(int d,float time);
      void mover(int dir,float deltatime);
      void setposdino(int i){_posdino=i;}
      void setactivo(bool a){activo=a;}
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

    private:
      float kVel=1882/10;
      float kVelx=1882/10;
      float kVely=1882/10;
      sf::Sprite* _Sprite = new sf::Sprite; // Sprite
      sf::Texture* textura;
      int _posdino=1; // Posicion a la que mira el dino ==> 0:Arriba | 1:Abajo | 2:Derecha | 3:Izquierda
      int _Vida=1; // Vida del dino
      float invencibilidad = -1; 
      bool parado=false;
      bool activo=false;
      float switchtime=0.2;
      float totaltime=0;
      bool animal=true;
      //Si no existen snowbees en forma de huevo
      //Si quedan menos de 4 snowbees en pantalla
      //Si no ha perdido una vida el juegador en los últimos 2 minutos
};

#endif
