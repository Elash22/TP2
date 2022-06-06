#include <iostream>
#include "carta.hpp"
#include "coordenada.hpp"
#include "jugador.hpp"
#include "tablero.hpp"
#include "partida.hpp"

using namespace std;

const int EN_JUEGO = 1;
const int FINALIZADO = -1;

int main(){
    try{
        Partida* partida = new Partida();
        // INGRESO DE DATOS
        partida->inicializarPartida();

        while(!partida->haTerminado()){
            partida->siguienteTurno();
        }

        /*
        // EXPORTAR TABLERO PARA TODOS LOS JUGADORES, de forma tal que el jugador pueda ver el terreno antes de colocar sus soldados

        // MIENTRAS EL JUEGO NO TERMINA, ALTERNAR JUGADORES, realizar checkeo si el juego finalizo
        // ¿esto no deberia ser un metodo de partida?
        while(partida.getEstado() == EN_JUEGO){

            // EXPORTAR TABLERO PARA EL JUGADOR EN TURNO

            // REALIZAR DISPARO(S), checkear si el juego finalizo

            // ELEGIR Y MOVER UNA UNIDAD, checkear si el juego finalizo

            // LEVANTAR Y JUGAR CARTA INMEDIATAMENTE, unidades solo se agregan, pueden disparar en el proximo turno. checkear si el juego finalizo

            cambiarTurno();
        }

        // OBTENER GANADOR DEL JUEGO, si no hay ganador el juego termino en empate
        if(partida.getEstado() == FINALIZADO){
            cout << "Juego finalizado, gana el jugador: " << jugadorActual.getNroJugador();
        }
        */
    }catch(const char* e){
        cout << endl << e << endl ;
    }
    return 0;
}

