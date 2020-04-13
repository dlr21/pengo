#include "Tile.h"
#include <iostream>

Tile::Tile() {
Cargarecursos();
}

void Tile::Cargarecursos(){

  //Cargo la imagen donde reside la textura del sprite

  if (!texvida.loadFromFile("resources/corazon rojo.png")) {
    std::cerr << "Error cargando la imagen sprites.png";
    exit(0);
  }vida1.setTexture(texvida);vida2.setTexture(texvida);vida3.setTexture(texvida);

  if (!texletranumero.loadFromFile("resources/letrasnumeros.png")) {
    std::cerr << "Error cargando la imagen sprites.png";
    exit(0);
  }letranumero.setTexture(texletranumero);


  if (!texcontador.loadFromFile("resources/contador.png")) {
    std::cerr << "Error cargando la imagen sprites.png";
    exit(0);
  }contador.setTexture(texcontador);
     
  //Y creo el spritesheet a partir de la imagen anterior
            if (!fuente.loadFromFile("resources/arial.ttf"))
            {              
                  std::cout << "Error: Could not display font" << std::endl;
            }    
            // Damos un valor a la cadena
            cadena = "0"+std::to_string(min)+":"+std::to_string(seg);
            // Asignamos la cadena al texto
            texto.setString(cadena);
            // Asignamos la fuente que hemos cargado al texto
            texto.setFont(fuente);
            // Tamaño de la fuente
            texto.setCharacterSize(20);
            // Posición del texto
            texto.setPosition(295,20);
            texto.setColor(sf::Color::Red);
  
  //Le pongo el centroide donde corresponde
  vida1.setOrigin(16 / 2, 16 / 2);
  vida2.setOrigin(16 / 2, 16 / 2);
  vida3.setOrigin(16 / 2, 16 / 2);

   /*
    //sf::Sprite gameover(tex3);
    gameover.setOrigin(8 / 2,15 / 2);
    */
  //barra de vida
  vida1.setTextureRect(sf::IntRect( 0* 16, 3 * 16, 16, 16));
  vida2.setTextureRect(sf::IntRect( 0* 16, 3 * 16, 16, 16));
  vida3.setTextureRect(sf::IntRect( 0* 16, 3 * 16, 16, 16));

  vida2.setScale(2,2);
  vida3.setScale(2,2);
  vida1.setScale(2,2);

  // Lo dispongo en el centro de la panta

  vida1.setPosition(40, 40);
  vida2.setPosition(71, 40);
  vida3.setPosition(102, 40);
 
}
void Tile::draw(sf::RenderWindow &window){
  if(vidas==1){
    window.draw(vida1);
  }else if(vidas==2){
    window.draw(vida1);
    window.draw(vida2);
  }else if(vidas==3){
    window.draw(vida1);
    window.draw(vida2);
    window.draw(vida3);
  }else if(vidas==0)
  {
    /* GAMEOVER HABER ESTUDIAO */
  }
    window.draw(texto);
}
void Tile::Update(Jugador* j){
    vidas=j->getVidas();
    if(!terminada){
        int s2=segundero;
        segundero=temporizador.getElapsedTime().asSeconds();
        if(s2<segundero){             
            seg-=1;
                std::cout<<seg<<"\n";
                if(seg<10){
                    texto.setString("0"+std::to_string(min)+":0"+std::to_string(seg));
                }else{
                     texto.setString("0"+std::to_string(min)+":"+std::to_string(seg));
                }
            if(seg<=0){
                if(min==0){
                    terminada=true;
                }
                min--;
                seg=59;
            }
        }
    }
}