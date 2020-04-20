#include <iostream>
#include "ia.h"

void IA::movimientoDinos(vector<Dinosaurio*> dinosaurios, int _cont,std::vector<sf::Sprite*> &todoSprite, float times, Map* m){
        for(int i=0; i < dinosaurios.size(); i++){
            if(dinosaurios[i]->getactivo()){
                if (dinosaurios[i]->getaturdido())
                {
                    dinosaurios[i]->animacion(dinosaurios[i]->getDireccion() , times);
                }else{
                
                    dinosaurios[i]->settotalcambio(dinosaurios[i]->gettotalcambio()+times);
                    if(dinosaurios[i]->gettotalcambio() >=dinosaurios[i]->getcambiodir() || dinosaurios[i]->getparado()){
                        dinosaurios[i]->settotalcambio(0);
                        srand (time(NULL));
                        int num1 = dinosaurios[i]->getDireccion();
                        int num2 = (i+rand()) % 4;
                        int dir = abs(num1 - num2);
                        if(dir!=dinosaurios[i]->getDireccion()){
                            dinosaurios[i]->setposdino(dir);
                            dinosaurios[i]->setparado(false);
                        }
                    }
                    if(dinosaurios[i]->getDireccion() == 0 && !dinosaurios[i]->getparado() && elegirdireccion(dinosaurios[i],m)){ 
                        dinosaurios[i]->marriba(todoSprite,times);
                    }
                    if(dinosaurios[i]->getDireccion() == 1 &&  !dinosaurios[i]->getparado() && elegirdireccion(dinosaurios[i],m)){
                        dinosaurios[i]->mabajo(todoSprite,times);
                    }
                    if(dinosaurios[i]->getDireccion() == 2 &&  !dinosaurios[i]->getparado() && elegirdireccion(dinosaurios[i],m)){
                        dinosaurios[i]->mderecha(todoSprite,times);          
                    }
                    if(dinosaurios[i]->getDireccion() == 3 &&  !dinosaurios[i]->getparado() && elegirdireccion(dinosaurios[i],m)){
                    dinosaurios[i]->mizquierda(todoSprite,times);
                    }
                }
            }
        }      
}


bool IA::elegirdireccion(Dinosaurio* dinosaurio, Map* m){
        if(m->dinomira(dinosaurio->getSprite(),dinosaurio->getDireccion()) == NULL){
            return true;
        }    
    return false;
}