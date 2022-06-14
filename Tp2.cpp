#include <iostream>
#include "carta.hpp"
#include "coordenada.hpp"
#include "jugador.hpp"
#include "tablero.hpp"
#include "partida.hpp"

using namespace std;

int main(){
    try{
        Partida* partida = new Partida();

        partida->inicializarPartida();

        while(!partida->haTerminado()){
            partida->siguienteTurno();
        }

        partida->declararJugadorGanador();

        delete partida;
    }catch(const char* e){
        cout << endl << e << endl ;
    }
    return 0;
}
