#ifndef DINOSAURIO_H
#define DINOSAURIO_H

class Dinosaurio 
{
    public:
      Dinosaurio(); // Constructor por defecto
      Dinosaurio(sf::Texture&); // Constructor con textura
      ~Dinosaurio(); // Destructor
      // Movimiento
      int marriba(std::vector<sf::Sprite*> &c, float time);
      int mabajo(std::vector<sf::Sprite*> &c, float time);
      int mderecha(std::vector<sf::Sprite*> &c, float time);
      int mizquierda(std::vector<sf::Sprite*> &c, float time);
  
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
      void setDireccion(int i);
      int getDireccion();
      void draw(sf::RenderWindow &window);
      bool getparado(){return parado;}
      void setparado(bool a){parado=a;}
      bool getactivo(){return activo;}
      void activar(){activo=true;}
      void animacion(int d,float time);
      void mover(std::vector<sf::Sprite*> &todoSprite,int direccion,float time);
      void setposdino(int i){_posdino=i;}
      void setactivo(bool a){activo=a;}
    private:
      float _Speed=50; // Velocidad
      int _Direccion;
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
