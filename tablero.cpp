#include "tablero.hpp"
#include "coordenada.hpp"
#include <iostream>
using namespace std;

Tablero::Tablero(int largo, int ancho, int alto, int nroMapa){
    this->largo = largo;
    this->ancho = ancho;
    this->alto = alto;
  
    this->tablero = new Lista<Lista<Lista<Casillero*>*>*>();
    for(int x=1; x<=largo; x++){
        this->tablero->add(new Lista<Lista<Casillero*>*>(), x);
	    for(int y=1; y<=ancho; y++){
		    this->tablero->get(x)->add(new Lista<Casillero*>(), y);
		    for(int z=1; z<=alto; z++){
          if(nroMapa ==1){
            if(x<largo/2 && y<ancho/2 && z==1){
              this->tablero->get(x)->get(y)->add(new Casillero(x,y,z, agua), z);
            }else if(z==1){
              this->tablero->get(x)->get(y)->add(new Casillero(x,y,z, tierra), z);
            }else{
              this->tablero->get(x)->get(y)->add(new Casillero(x,y,z, aire), z);
            }
          }
		    }
	    }
    }
}

int Tablero::getLargo(){
  return this->largo;
}

int Tablero::getAncho(){
  return this->ancho;
}

int Tablero::getAlto(){
  return this->alto;
}

Casillero* Tablero::getCasillero(int largo, int ancho, int alto){
    if(largo<1|| ancho<1 || alto<1 || 
    largo>this->getLargo() || ancho>this->getAncho() || alto>this->getAlto() ){
	    throw "El casillero solicitado se va del rango.";
    }
    return this->tablero->get(largo)->get(ancho)->get(alto);
}
