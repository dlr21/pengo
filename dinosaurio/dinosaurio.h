#ifndef DINOSAURIO_H
#define DINOSAURIO_H

class Dinosaurio 
{
    public:
      Dinosaurio(); // Constructor por defecto
      Dinosaurio(sf::Texture&); // Constructor con textura
      ~Dinosaurio(); // Destructor

      // Movimiento
      int marriba(std::vector<sf::Sprite*> &c);
      int mabajo(std::vector<sf::Sprite*> &c);
      int mderecha(std::vector<sf::Sprite*> &c);
      int mizquierda(std::vector<sf::Sprite*> &c);


      // Cambiar velocidad
      void setSpeed();

      // Devolver sprite
      sf::Sprite* getSprite() ;

      // Cambiar vida
      void setVida();

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
    private:
      float _Speed=100; // Velocidad
      int _Direccion;
      sf::Sprite* _Sprite = new sf::Sprite; // Sprite
      sf::Texture* textura;
      int _posdino=1; // Posicion a la que mira el dino ==> 0:Arriba | 1:Abajo | 2:Derecha | 3:Izquierda
      int _Vida=1; // Vida del dino
      float invencibilidad = -1; 
      bool parado=true;
      bool activo=true;
      int mir=0;
      float switchtime=0.1;
      float totaltime=0;
      bool animal=true;
};

#endif
