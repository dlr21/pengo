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

   
      void recolocar(std::vector<sf::Sprite*> &todo, int i){

        for(unsigned int j = 0;j < todo.size();j++)
        {
            if(_Sprite->getGlobalBounds().intersects(todo[j]->getGlobalBounds()) && _Sprite!=todo[j])
            {
               _Sprite->setPosition(getposimapax()*32+112-(32*(i+1)),getposimapay()*32+64-(32*(i+1)));
                if(_Sprite->getGlobalBounds().intersects(todo[j]->getGlobalBounds()) && _Sprite!=todo[j])
                {
                    recolocar(todo,i+1);
                }

            }
        }

      }
    
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
      void controlaturido(float times){
        switchaturdido+=times;
        if(switchaturdido>=aturdidostime){
          switchaturdido=0;
          aturdido=false;
        }
      }
    private:
      float kVel=150;
      float kVelx=kVel;
      float kVely=kVel;
      sf::Sprite* _Sprite = new sf::Sprite; 
      sf::Texture* textura;
      int _posdino=1; // donde orienta la mirada
      int _Vida=1; 
      float invencibilidad = -1; 
      bool parado=false;
      bool activo=false;
      float switchtime=0.10;
        float cambiodir=1;
      float totaltime=0;
        float totalcambio=0;
      float aturdidostime=5;
        float switchaturdido=0;
      bool animal=true;
      bool aturdido=false;

};

#endif
