#include <iostream>
#include "ia.h"

/* Genera numeros aleatorios entre el 0 y el 4 para ver en que direccion se mueve.
 * Usa un contador de iteraciones del programa para que no dependa del tiempo
 */

void IA::movimientoDinos(vector<Dinosaurio*> dinosaurios, int _cont,std::vector<sf::Sprite*> &todoSprite, float times){
totaltime+=times;
if(totaltime>=switchtime){
        for(int i=0; i < dinosaurios.size(); i++){
            if(dinosaurios[i]->getactivo()){
                int cosas [5] = { 0, 1, 2, 3, 4 };
                int meh = cosas[i];
                
                srand (time(NULL));
                int num1 = dinosaurios[i]->getDireccion();
                int num2 = rand() % 5;
                int dir = abs(num1 - num2);
                dinosaurios[i]->setposdino(dir);
                if(dir == 0){ 
                    dinosaurios[i]->marriba(todoSprite,times);
                }
                if(dir == 1){
                    dinosaurios[i]->mabajo(todoSprite,times);   
                }
                if(dir == 2){
                    dinosaurios[i]->mderecha(todoSprite,times);               
                }
                if(dir == 3){   
                    dinosaurios[i]->mizquierda(todoSprite,times);
                }
                else{
                    dinosaurios[i]->sumaPasos();
                }
            }
        }
}else{
            for(int i=0; i < dinosaurios.size(); i++){
                if(dinosaurios[i]->getactivo() && !dinosaurios[i]->getparado()){
                    dinosaurios[i]->mover(dinosaurios[i]->getDireccion(),times); 
                }
            }
}

}