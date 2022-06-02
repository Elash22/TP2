#include <iostream>
#include "jugador.hpp"
#include "unidad.hpp"

Jugador::Jugador(unsigned int numeroJugador){
    this->nroJugador = numeroJugador;
    this->unidades = new Lista<Unidad*>;
    this->cantidadSoldados = 0;
    this->cantidadAviones = 0;
    this->cantidadBarcos = 0;

    this->cantidadDisparosDisponibles = 0;
    this->cantidadMisilesDisponibles = 0;
    this->misilAdicionalEnProximoTurno = false;

    this->cantidadTurnosInhabilitado = 0;
    this->gano = false;
}

void Jugador::asignarUnidad(Unidad* unidadDeBatalla){
    this->unidades->add(unidadDeBatalla);

    if(unidadDeBatalla->getTipoDeUnidad() == soldado){
        this->cantidadSoldados++;
    }else if(unidadDeBatalla->getTipoDeUnidad() == avion){
        this->cantidadAviones++;
    }else{
        this->cantidadBarcos++;
    }
}

Unidad* Jugador::buscarUnidad(unsigned int numeroDeUnidad){
    Unidad* aux;

    this->unidades->reiniciarCursor();
    while(this->unidades->avanzarCursor()!= false){
        aux = this->unidades->getCursor();
        if(aux->getNroUnidad() == numeroDeUnidad){
            return aux;
        }
    }
    return NULL;    
}

void Jugador::removerUnidad(Unidad unidad){
    Unidad* aux;
    unsigned int posicionUnidad = 1;

    this->unidades->reiniciarCursor();
    while(this->unidades->avanzarCursor()!= false){
        aux = this->unidades->getCursor();
        if(aux->getNroUnidad() == unidad.getNroUnidad() && aux->getTipoDeUnidad() == unidad.getTipoDeUnidad()){
            this->unidades->remover(posicionUnidad);
            if(unidad.getTipoDeUnidad() == soldado){
                this->cantidadSoldados--;
            }else if(unidad.getTipoDeUnidad() == avion){
                this->cantidadAviones--;
            }else{
                this->cantidadBarcos--;
            }
            return;
        }
        posicionUnidad++;
    }
    throw "LA UNIDAD NO HA SIDO ENCONTRADA EN LA LISTA DE UNIDADES DEL JUGADOR";
    return;
}

unsigned int Jugador::getCantidadDisparosDisponibles(){
    this->cantidadDisparosDisponibles = this->cantidadSoldados + this->cantidadAviones * 2;
    return this->cantidadDisparosDisponibles;
}

unsigned int Jugador::getCantidadMisilesDisponibles(){
    unsigned int misilAdicional = 0;
    if(this->misilAdicionalEnProximoTurno == true){
        misilAdicional = 1;
    }
    this->misilAdicionalEnProximoTurno = false;

    this->cantidadMisilesDisponibles = this->cantidadBarcos + misilAdicional;
    return this->cantidadMisilesDisponibles;
}

void Jugador::agregarMisilProximoTurno(){
    this->misilAdicionalEnProximoTurno = true;
    return;
}

void Jugador::inhabilitarPorUnTurno(){
    this->cantidadTurnosInhabilitado++;
    return;
}

bool Jugador::estaHabilitado(){
    if(this->cantidadTurnosInhabilitado > 0){
        this->cantidadTurnosInhabilitado--;
        return false;
    }else{
        return true;
    }
}

bool Jugador::poseeSoldados(){
    if(this->cantidadSoldados > 0){
        return true;
    }else{
        return false;
    }
}

Jugador::~Jugador(){
    delete unidades;
}