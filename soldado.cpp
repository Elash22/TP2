#include "soldado.hpp"
#include "coordenada.hpp"
#include "jugador.hpp"
#include <iostream>

using namespace std;

Soldado::Soldado(Coordenada posicion, int nroSoldado){
    //¿Como hago para agarrar el error donde se le pase una posicion con alguna componente mas alta que la máxima?
    if(posicion.getAltura() < 1 || posicion.getColumna() < 1 || posicion.getFila() < 1 ){
        throw "Error al crear un soldado, la coordenada pasada debe tener componentes mayores a 0";
    }
    this->estado = Vivo;
    this->posicion = posicion;
//  this->jugador = NULL; //Dudoso
    this->nroSoldado = nroSoldado;
}
EstadoSoldado Soldado::getEstadoSoldado(){
    return this->estado;
}
Coordenada Soldado::getPosicionSoldado(){
    return this->posicion;
}
int Soldado::getNroSoldado(){
    return this->nroSoldado;
}
void Soldado::setEstadoSoldado(EstadoSoldado estado){
    if(estado != Vivo || estado != Muerto){
        throw "Error al cambiar estado del soldado, el estado del soldado pasado por parámetro debe ser 'Vivo' o 'Muerto'";
    }
    this->estado = estado;
}
void Soldado::setPosicionSoldado(Coordenada posicion){
    //¿Como hago para agarrar el error donde se le pase una posicion con alguna componente mas alta que la máxima?
    if(posicion.getAltura() < 1 || posicion.getColumna() < 1 || posicion.getFila() < 1 ){
        throw "Error al crear un soldado, la coordenada pasada debe tener componentes mayores a 0";
    }
    this->posicion = posicion;
}