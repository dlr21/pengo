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
      if(play==1){
        hud1=new Tile();
        jugador1=new Jugador(1);
      }
      srand (time(NULL));   //para el rand 
      for(int a=0;a<lvls;a++){//cargar los mapas dependiendo del nombre
        int aleat=rand() % 9;
        std::cout<<aleat<<endl;
        string s="resources/mapas/"+to_string(dif)+"mapa"+to_string(aleat)+".tmx";
        std::cout<<s<<endl;
        Map* m=new Map(s,dif+3);
        std::cout<< mapas.size()<<endl;
        mapas.push_back(m);//meter los mapas en el vector de mapas
        std::cout<< mapas.size()<<endl;
      }
}
/*void Mundo::crearAdns(Map* m,int tot){
  int v1=1;
  int cont=0;
  bool todos=false;
  std::cout<<m->getnumlayers()<<m->getheight()<<m->getwidth()<<endl;
    for(unsigned int l=0; l<m->getnumlayers() && !todos;l++){
        for( unsigned int y=0; y<m->getheight() && !todos;y++){
          for(unsigned int x=0; x<m->getwidth() && !todos;x++){
            int gid=m->gettilemap()[l][y][x]-1;
              v1 = rand() % 999;
              std::cout<<m->getnumlayers()<<m->getheight()<<m->getwidth()<<" "<<v1<<endl;
            if(gid==2 && v1<190){//GID = PIEDRAS
              std::cout<<v1<<endl;
              Adn* prueba=new Adn(1,x,y);
              adns.push_back(prueba);
              cont++;
              if (tot==cont) { todos=true; } //CONTROLA QUE NO FALTEN ADNS
            }
          }
        }
     }   
}*/
void Mundo::crearDinos(Map* m,int tot){
      sf::Texture dino_abajo;
      if(!dino_abajo.loadFromFile("resources/dino_abajo.png")){
        std::cerr << "Error cargando dino_abajo.png";
        exit(0);
      }

  int v1=1;
  int cont=0;
  bool todos=false;
  std::cout<<m->getnumlayers()<<m->getheight()<<m->getwidth()<<endl;
    for(unsigned int l=1; l<m->getnumlayers() && !todos;l++){
        for( unsigned int y=2; y<m->getheight()-1 && !todos;y++){
          for(unsigned int x=2; x<m->getwidth()-1 && !todos;x++){
            int gid=m->gettilemap()[l][y][x]-1;
              v1 = rand() % 999;
              if(gid==-1 && v1<100){//GID = camino
              std::cout<<"coloca dino"<<endl;
              Dinosaurio *dino1 = new Dinosaurio(); // Constructor del dinosaurio
              dino1->modifyPosition(112+(x*32),64+(y*32)); // Punto de spawn. Debe estar dentro del mapa
              dinosaurios.push_back(dino1); // Guardar en el vector de dinosaurios
              cont++;
              if (tot==cont) { todos=true; }
            }
          }
        }
     }   
}

void Mundo::Event(sf::Event event,sf::RenderWindow &window, float time){ //COSAS DEL MUNDO CUANDO PULSAS ALGO
    std::cout<<"event"<<std::endl;
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
                std::cout<<"empujar?";
                jugador1->setempujon(true);//PENDIENTE
                dirbloque=jugador1->getmir();
                if(mapas[lvlactual]->empujado(jugador1->getSprite(),dirbloque)){
                  std::cout<<"SI EMPUJA"<<std::endl;
                  bloqueadeslizar=(mapas[lvlactual]->empujado(jugador1->getSprite(),dirbloque));
                  if(mapas[lvlactual]->empujado(bloqueadeslizar,dirbloque)){
                    //BORAR BLOQUE
                    mapas[lvlactual]->borrardemapa(1,(bloqueadeslizar->getPosition().x-112)/32,(bloqueadeslizar->getPosition().y-64)/32);
                    borradetodoSprites(bloqueadeslizar);
                              bloqueadeslizar=NULL;
                              delete[] bloqueadeslizar;
                  }else{
                    jugador1->setmoviendo(true);
                    std::cout<<"moviendo"<<endl;
                  }
                }
              }else{std::cout<<"ya estaba empujando"<<endl;}
              break;
            }
            case 16: //n siguiente nivel 13
              if(lvlactual<mapas.size()){
                  mapas[lvlactual]->terminar();
              }
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
              jugador1->setVidas(0);
            break;
            case 36://esc salir 31
              Contexto::Instance()->Quit();
              window.close();
            break;
            case 15://matar sno
                if(dinosaurios.size()>0){
                    dinosaurios[0]->modifyVida();
                    if(dinosaurios[0]->getVida() == 0)
                {
                  for(unsigned int a = 0;a < todoSprites.size();a++){
                    if(todoSprites[a]==dinosaurios[0]->getSprite()){
                      todoSprites.erase(todoSprites.begin() + a);
                    }
                  }
                  dinosaurios.erase(dinosaurios.begin() + 0);
                  jugador1->sumaPuntos();
                }
              }
            break;

            //Arriba
             case 73:
                     if(!jugador1->getColision() && !jugador1->gettecla()){ 
            jugador1->animacion(0,time);
            jugador1->mover(0,time);
              Colisiones::crearColisiones(*jugador1->getSprite(),todoSprites,0,jugador1->getVelocidad(), time, jugador1);
              jugador1->settecla(true);
                     }
            break;
            //Abajos
            case 74:
                    if(!jugador1->getColision() && !jugador1->gettecla()){
            jugador1->animacion(1,time);
            jugador1->mover(1,time);
              Colisiones::crearColisiones(*jugador1->getSprite(),todoSprites,1,jugador1->getVelocidad(), time, jugador1);
              jugador1->settecla(true);
                    }
            break;
            //Derecha
            case 72:
                    if(!jugador1->getColision() && !jugador1->gettecla()){
            jugador1->animacion(2,time);
            jugador1->mover(2,time);
              Colisiones::crearColisiones(*jugador1->getSprite(),todoSprites,2,jugador1->getVelocidad(), time, jugador1);
              jugador1->settecla(true);
                    }
            break;
            //Izquierda
            case 71:
                    if(!jugador1->getColision() && !jugador1->gettecla()){
            jugador1->animacion(3,time);
            jugador1->mover(3,time);
              Colisiones::crearColisiones(*jugador1->getSprite(),todoSprites,3,jugador1->getVelocidad(), time, jugador1);
              jugador1->settecla(true);
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
            dinoscreados=false;
            colisiones=false;
            borrarcolisiones();
            //borraradns();
            borrardinos();
            lvlactual++;
            //Reiniciar contador
            hud1->reiniciocrono();
            if(play==1){
              jugador1->setInicio();
            }     
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
          }
        }
    if(play==1){// UN JUGADOR O DOS JUGADORES UPDATEAN ELLOS Y SUS HUDS
      Colisiones::crearColisiones(*jugador1->getSprite(),todoSprites,3,jugador1->getVelocidad(), time, jugador1);
      todosno();
      hud1->Update(jugador1);
      jugador1->Update(time);
      if(jugador1->getVidas()==0){
         finjuego();
        std::cout<<"PIERDES"<<endl;
      }
      if(bloqueadeslizar!=NULL && jugador1->getmoviendo()){
          mapas[lvlactual]->deslizarbloque(bloqueadeslizar,dirbloque,time);
      }
      Colisiones::crearColisiones(*jugador1->getSprite(),todoSprites,3,jugador1->getVelocidad(), time, jugador1);
      Colisiones::update(temporizador,bloqueadeslizar,dinosaurios,*jugador1,totalExplosiones,*mapas[lvlactual],todoSprites,paredesSprites,time); 
      
    }
    // Mover los dinosaurios con la IA
    IA ia; // Genera una ia con cada iteracion
    ia.movimientoDinos(dinosaurios, _cont,todoSprites, time); // Permite mover a los dinosaurios
    _cont++; // Contador de iteraciones del programa
    //Detecta si le tiene que quitar vida a jugadores y dinosaurios si colisionan con una explosion.
}

void Mundo::finjuego(){
        std::cout<<"fin"<<endl;
        //RENICIAR MUNDO
        this->renicio();
        this->Inicializar();
       /*//MENU INICIAL
        Menu::Instance()->reinicio();
        ChangeState(Contexto::Instance(),Menu::Instance());*/
}

void Mundo::renicio(){ //reiniciar el mundo
      std::cout<<"reinicio"<<dif<<lvls<<lvlactual<<"\n";
      nueva=false;
      dif=0;
      lvls=0;
      lvlactual=0;
      play=0;
      std::cout<< mapas.size()<<endl;
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

