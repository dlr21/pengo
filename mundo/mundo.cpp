#include "mundo.h"



Mundo* Mundo::jinstance=0;

Mundo* Mundo::Instance() {
    if(jinstance==0){
      jinstance=new Mundo;
        std::cout<<"mundooinstance"; 
    }
    return jinstance;
}

void Mundo::Inicializar() {
      std::cout<<"mundoiniciado\n";
      dif=1;
      lvls=2; //numero de niveles
      play=1;//numero de jugadores      
      //CREAR JUGADORES
      if (nueva)
      {
        jugador1=new Jugador(1);
        hud1=new Tile();
        nueva=false;
        prepuntos=0;
      }
      jugador1->setInicio();
      clock.restart();
      ia=new IA();
      bloqueadeslizar=NULL;
      pulsada=false;//event de uno en uno
      adnscreados=false;
      dinoscreados=false;
      colisiones=false;
      moverse=true;

      dirbloque=0;
      snototales=4;
      snovivos=2;
      snodurmiendo=4;
      for(int a=0;a<lvls;a++){//cargar los mapas dependiendo del nombre
        string s="resources/mapas/"+to_string(dif)+"mapa"+to_string(a)+".tmx";
        std::cout<<s<<endl;
        Map* m=new Map(s,dif+3);
        std::cout<< mapas.size()<<endl;
        mapas.push_back(m);//meter los mapas en el vector de mapas
        std::cout<< mapas.size()<<endl;
      }
}

void Mundo::crearDinos(Map* m,int tot){
  int v1=1;
  int cont=0;
  bool todos=false;
  std::cout<<m->getnumlayers()<<m->getheight()<<m->getwidth()<<endl;
    for(unsigned int l=1; l<m->getnumlayers() && !todos;l++){
        for( unsigned int y=2; y<m->getheight()-1 && !todos;y++){
          for(unsigned int x=2; x<m->getwidth()-1 && !todos;x++){
            int gid=m->gettilemap()[l][y][x]-1;
              v1 = rand() % 999;
              if(gid==-1 && v1<50){//GID = camino
              Dinosaurio *dino1 = new Dinosaurio(); // Constructor del dinosaurio
              dino1->modifyPosition(112+(x*32),64+(y*32)); // Punto de spawn. Debe estar dentro del mapa
              dinosaurios.push_back(dino1); // Guardar en el vector de dinosaurios
              
              if (cont<tot/2)
              {
                dino1->setactivo(true);
              }
              cont++;
              if (tot==cont) { todos=true; }
            }
          }
        }
     }   
}

void Mundo::Event(sf::Event event,sf::RenderWindow &window, float time){ //COSAS DEL MUNDO CUANDO PULSAS ALGO

      switch (event.type) {
        case sf::Event::Closed:
          Contexto::Instance()->Quit();
          window.close();
        break;
        //case sf::Event::MouseButtonPressed:
        case sf::Event::KeyPressed:
              ///Verifico si se pulsa alguna tecla de movimiento
          switch (event.key.code) {  
            std::cout<<"pulsa"<<std::endl;
            case 57: //EMPUJAR
            {
              if(!jugador1->getempujon() && !jugador1->getmoviendo()) {
                std::cout<<"empujar?"<<std::endl;
                jugador1->setempujon(true);//PENDIENTE
                dirbloque=jugador1->getmir();

                if(mapas[lvlactual]->muroempujon(jugador1->getSprite(),dirbloque) == NULL){//SI NO EMPUJAMURO ENTRA, SI EMPUJA ATURDE

                  if(mapas[lvlactual]->empujado(jugador1->getSprite(),dirbloque) != NULL){ //SI EL MUERO QUE EMPUJA TIENE GID 5 O 6
                    std::cout<<"SI EMPUJA"<<std::endl;
                    bloqueadeslizar=(mapas[lvlactual]->empujado(jugador1->getSprite(),dirbloque));//GUARDO SPRITE DEL BLOQUE A MOVER
                    //BORRAR BLOQUE O MOVER
                    if(mapas[lvlactual]->empujado(bloqueadeslizar,dirbloque)){//BORAR BLOQUE 
                      if(mapas[lvlactual]->borrardemapa((bloqueadeslizar->getPosition().x-112)/32,(bloqueadeslizar->getPosition().y-64)/32)){
                        mapas[lvlactual]->settilemap0((bloqueadeslizar->getPosition().x-112)/32,(bloqueadeslizar->getPosition().y-64)/32);//CONTROLAR ID DE LA MATRIZ DEL MAPA
                        borradetodoSprites(bloqueadeslizar);
                        bloqueadeslizar->setPosition(-50,-50);
                        bloqueadeslizar=NULL;//LIMPIAR SPRITE AUXILIAR
                      }
                    }else{//MOVER BLOQUE
                      jugador1->setmoviendo(true);
                      std::cout<<"moviendo"<<endl;
                      mapas[lvlactual]->settilemap0((bloqueadeslizar->getPosition().x-112)/32,(bloqueadeslizar->getPosition().y-64)/32);
                    }
                  }
                  
                }else{
                    aturdir();
                  }
              }else{
                std::cout<<"ya estaba empujando"<<endl;
                }
              break;
            }
            case -1://ñ 
              mapas[lvlactual]->tresenralla();
            break;
            case 59: //delete reinicio nivel 59
                this->reinicionivel();
              break;
            case 13: //n siguiente nivel 13
              if(lvlactual<mapas.size()){
                  mapas[lvlactual]->terminar();
              }
              break;
            case 6://g modo dios inmortal 6
              jugador1->changeInvencile();
            break;

            case 23://x muerte 23
              jugador1->setVidas(3);
              this->reinicionivel();
            break;
            case 36://esc salir 31
              Contexto::Instance()->Quit();
              window.close();
            break;
            case 15://matar sno
                if(dinosaurios.size()>0){
                    dinosaurios[0]->modifyVida();
                    if(dinosaurios[0]->getVida() == 0){
                      for(unsigned int a = 0;a < todoSprites.size();a++){
                        if(todoSprites[a]==dinosaurios[0]->getSprite()){
                          todoSprites.erase(todoSprites.begin() + a);
                        }
                      }
                    dinosaurios.erase(dinosaurios.begin() + 0);
                    jugador1->sumaPuntos();
                    jugador1->setmatando(true);
                    }
                }
            break;
            //Arriba
             case 73:
              if(!jugador1->getColision() && jugador1->getcolocado()){ 
                jugador1->mover(0,time);
                Colisiones::crearColisiones(*jugador1->getSprite(),todoSprites,0,jugador1->getVelocidad(), time, jugador1);
                jugador1->setcolocado(false);
              }
            break;
            //Abajos
            case 74:
                if(!jugador1->getColision() && jugador1->getcolocado()){
                  jugador1->mover(1,time);
                  Colisiones::crearColisiones(*jugador1->getSprite(),todoSprites,1,jugador1->getVelocidad(), time, jugador1);
                  jugador1->setcolocado(false);
                }
            break;
            //Derecha
            case 72:
                if(!jugador1->getColision() &&  jugador1->getcolocado()){
                  jugador1->mover(2,time);
                  Colisiones::crearColisiones(*jugador1->getSprite(),todoSprites,2,jugador1->getVelocidad(), time, jugador1);
                  jugador1->setcolocado(false);
                }
            break;
            //Izquierda
            case 71:
                if(!jugador1->getColision() && jugador1->getcolocado()){
                  jugador1->mover(3,time);
                  Colisiones::crearColisiones(*jugador1->getSprite(),todoSprites,3,jugador1->getVelocidad(), time, jugador1);
                  jugador1->setcolocado(false);
                }
            break;    
          //Cualquier tecla desconocida se imprime por pantalla su código
          default:
            std::cout << " code " << event.key.code << std::endl;
          break;
        }
      }

}
void Mundo::Update(sf::RenderWindow &window, float time) {//COSAS DEL MUNDO QUE SE ACTUALIZAN SIEMPRE
  if(hud1->getTerminada()){
    std::cout<<"terminado el tiempo"<<endl;//HAS PERDIDO
  }
      if (mapas[lvlactual]->fin()){
            std::cout<<"cambiar mapa\n";
            int i=clock.getElapsedTime().asSeconds();
            if(i<60){jugador1->maspuntos(i);}
            prepuntos=jugador1->getPuntos();
            dinoscreados=false;
            colisiones=false;
            diamant=false;
            borrarcolisiones();
            borrardinos();
            lvlactual++;
            //Reiniciar contador
            hud1->reiniciocrono();
      }
      if(!(lvlactual<mapas.size())){//TERMINAR Y VOLVER A MENU FIN DEL JUEGO   
          finjuego();
        }else{
          if(!dinoscreados){//CREAR DINOS ESTO PUEDE DAR LAS PROBLEMAS
            crearDinos(mapas[lvlactual],snototales);
            dinoscreados=true;
          }
          if(!colisiones){
            mapas[lvlactual]->anadirVector(todoSprites);
            colisiones=true;
            jugador1->setInicio();
          }
        }
      Colisiones::crearColisiones(*jugador1->getSprite(),todoSprites,3,jugador1->getVelocidad(), time, jugador1);
      // UN JUGADOR O DOS JUGADORES UPDATEAN ELLOS Y SUS HUDS
        if (jugador1->getmatando())
        {
          todosno(time);
        }
        hud1->Update(jugador1);
        jugador1->Update(time);
        if(jugador1->getVidas()!=vidas){
          reinicionivel();
          std::cout<<"PIERDES"<<endl;
        }
        if(jugador1->getVidas()==0){
          finjuego();
          std::cout<<"PIERDES"<<endl;
        }
        if(bloqueadeslizar!=NULL && jugador1->getmoviendo()){
            mapas[lvlactual]->deslizarbloque(bloqueadeslizar,dirbloque,time);//MUEVE EL BLOQUE EMPUJADO
        }
        Colisiones::crearColisiones(*jugador1->getSprite(),todoSprites,3,jugador1->getVelocidad(), time, jugador1);
        Colisiones::update(temporizador,bloqueadeslizar,dinosaurios,*jugador1,totalExplosiones,*mapas[lvlactual],todoSprites,paredesSprites,time); 
        diamantitos();//COMPRUEBA LA POSICION DE LOS DIAMANTES
    // Mover los dinosaurios con la IA
    ia->movimientoDinos(dinosaurios, _cont,todoSprites, time, mapas[lvlactual]); // Permite mover a los dinosaurios
    _cont++; 
}

void Mundo::finjuego(){
        std::cout<<"fin"<<endl;
        //RENICIAR MUNDO
        this->renicio();
        this->Inicializar();
}

void Mundo::renicio(){ //reiniciar el mundo
      std::cout<<"reinicio"<<dif<<lvls<<lvlactual<<"\n";
      nueva=true;
      dif=0;
      lvls=0;
      lvlactual=0;
      play=0;
      std::cout<< mapas.size()<<endl;
      dinoscreados=false;
      colisiones=false;
      diamant=false;
      borrarcolisiones();
      borrardinos();
      borrarmapas();
      std::cout<<"reiniciofin"<<dif<<lvls<<lvlactual<<"\n";
}

void Mundo::Draw(sf::RenderWindow &window){//dibujar mapa y hud
  if(lvlactual<mapas.size()){
      mapas[lvlactual]->draw(window);
      //DIBUJAR DINOSAURIOS
      for(unsigned int i=0; i < dinosaurios.size(); i++)
      {
        dinosaurios[i]->draw(window);
      }
       if(play==1){
        hud1->draw(window);
        jugador1->draw(window);  
      }
  }
}

void Mundo::reinicionivel(){//reiniciar el nivel
      std::cout<<"reinicionivel"<<dif<<lvls<<lvlactual<<"\n";
      jugador1->setPuntos(prepuntos);
      nueva=false;
      dif=0;
      lvls=0;
      play=0;
      dinoscreados=false;
      colisiones=false;
      diamant=false;
      vidas=jugador1->getVidas();
      borrarcolisiones();
      borrardinos();
      borrarmapas();
      std::cout<<"reinicionivelfin"<<dif<<lvls<<lvlactual<<"\n";
      this->Inicializar();
}
