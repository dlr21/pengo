#include "contexto.h"
#include "states.h"


	Contexto* Contexto::pinstance=0;

  	Contexto* Contexto::Instance() {
		if(pinstance==0){
		pinstance=new Contexto;
		}
		return pinstance;
  	}
	void Contexto::Inicializar(){
		this->m_running=true;
		
		    std::cout<<"contextoinicia";
	}
	void Contexto::ChangeState(States* s){ //guarda en nuevo estado

		// store and init the new state
		std::cout<<this->states.size();	
		this->states.push_back(s);
		std::cout<<"changestate";
		this->states.back()->Inicializar();
		std::cout<<this->states.size()<<"\n";

	}
	void Contexto::Event(sf::Event event, sf::RenderWindow &window){
			this->states.back()->Event(event, window);
	}
	void Contexto::Update(sf::RenderWindow &window){
		// let the state update the game
      this->states.back()->Update(window);
	}
	void Contexto::Draw(sf::RenderWindow &window){
		// let the state draw the screen
		window.clear();
		states.back()->Draw(window);
		window.display();
	}
