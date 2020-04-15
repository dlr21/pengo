#include <iostream>
#include "ia.h"

/* Genera numeros aleatorios entre el 0 y el 4 para ver en que direccion se mueve.
 * Usa un contador de iteraciones del programa para que no dependa del tiempo
 */

void IA::movimientoDinos(vector<Dinosaurio*> dinosaurios, int _cont,std::vector<sf::Sprite*> &todoSprite,float times){
    
    int tam_dinos = dinosaurios.size();
        for(int i=0; i < tam_dinos; i++){
            if(dinosaurios[i]->getactivo()){
                if(dinosaurios[i]->getparado()==true){
                    srand (time(NULL));
                    int num1 = dinosaurios[i]->getDireccion();
                    int num2 = rand() % 4;
                    int dir = abs(num1 - num2);
                    dinosaurios[i]->setDireccion(dir);
                    dinosaurios[i]->setparado(false);
                    dinosaurios[i]->animacion(dir,times);
                    dinosaurios[i]->mover(todoSprite,dir,times);
                }
            }
        }

}